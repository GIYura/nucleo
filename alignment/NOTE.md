# Анализ поведения memcpy() и структуры с __attribute__((packed)) на STM32

## Введение

Этот документ исследует, как влияет атрибут `__attribute__((packed))` и установка бита `UNALIGN_TRP` на корректность доступа к полям структуры в STM32 (на примере STM32F411), особенно при использовании `memcpy()` и других форм копирования.

## Структура данных

```c
typedef struct __attribute__((packed)) {
    uint8_t opCode;
    uint16_t param1;
    uint32_t param2;
} Packet_t;
```

или

```c
typedef struct {
    uint8_t opCode;
    uint16_t param1;
    uint32_t param2;
} Packet_t;
```

## Бит UNALIGN_TRP

**Регистр:** `SCB->CCR`  
**Бит:** `UNALIGN_TRP` (bit 3)  
**Значение:**
- `0`: Разрешены невыровненные доступы (по умолчанию на большинстве STM32)
- `1`: Невыровненные доступы (например, `LDRH`, `STR`) приводят к HardFault

## Тест кейсы

### Test Case 1: По байтовое копирование через `for`
**Условия:**
- `packed`
- `UNALIGN_TRP = 1`

✅ Работает. `dst[i] = m_buffer[i];` — всегда по байту

---

**Условия:**
- `not packed`
- `UNALIGN_TRP = 1`

❌ Поля `param1` и `param2` искажены — padding смещает смещения в памяти

---

### Test Case 2: `memcpy()` с локальными переменными

**Условия:**
- `packed`
- `UNALIGN_TRP = 1`

❌ `HardFault` — `memcpy()` может использовать `STRH`, `STR` → требует выровненных адресов

---

**Условия:**
- `not packed`
- `UNALIGN_TRP = 1`

✅ Работает — структура выровнена

---

### Test Case 3: Запись в поля напрямую

**Условия:**
- `packed`
- `UNALIGN_TRP = 1`

❌ `HardFault` — поле `param1` лежит на нечетном адресе

---

**Условия:**
- `not packed`
- `UNALIGN_TRP = 1`

✅ Работает — поля по выровненным адресам

---

### Test Case 4: `memcpy()` из `m_buffer` в поля структуры

**Условия:**
- `packed`
- `UNALIGN_TRP = 1`

❌ `HardFault` — `memcpy` может генерировать `LDRH`

---

**Условия:**
- `not packed`
- `UNALIGN_TRP = 1`

❌ `HardFault` — источник (`m_buffer[1]`) может быть не выровнен

## Общие выводы

- `packed` может привести к невыровненным полям → доступ к ним потенциально опасен
- `UNALIGN_TRP = 1` — строгий режим, полезен для диагностики, но может вызвать HardFault при обычных операциях
- `memcpy()` — может не быть безопасным даже при `-O0`
- Лучший способ при `packed` + `UNALIGN_TRP = 1` — по-байтовое копирование вручную

## Рекомендации

- Для передачи бинарных протоколов использовать `packed`, но аккуратно
- При чтении/записи в такие структуры:
  - либо использовать по байтные циклы
  - либо отключать `UNALIGN_TRP`, если уверены в поведении
  
/**/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f411xe.h"

static uint8_t m_buffer[] = {
        0xaa,
        0xbb, 0xcc,
        0x12, 0x34, 0x56, 0x78
};

/*
NOTE:
Структура Packet_t упакована, то есть все поля лежат в памяти подряд.
При этом, размер ее = 7 байт
*/
#if 0
typedef struct __attribute__((packed))
{
    uint8_t opCode;
    uint16_t param1;
    uint32_t param2;
} Packet_t;
#else
/*
NOTE:
Структура Packet_t выровнянна, то есть компилятор добавит padding byte(s).
При этом, размер ее = 8 байт то есть, после поля opCode будет вставлен 1 байт.
*/
typedef struct
{
    uint8_t opCode;
    uint16_t param1;
    uint32_t param2;
} Packet_t;
#endif

/*
NOTE:
Переменная packet начинается с адреса:
20000008 l     O .data  00000007 packet

Поле        Адрес       Значение
opCode      20000008    0x11
param1[0]   20000009    0x33
param1[1]   2000000A    0x22
param2[0]   2000000B    0x78
param2[1]   2000000C    0x56
param2[2]   2000000D    0x34
param2[3]   2000000E    0x12

NOTE: поле param1 занимает адреса 20000009 и 2000000A, так как поле 16 бит, то адрес должен быть кратен 2,
но адрес 20000009 не кратен 2.
Это требование архитектуры ARM при включенном UNALIGN_TRP, а не ограничение C.
*/
static Packet_t packet = { .opCode = 0x11, .param1 = 0x2233, .param2 = 0x12345678 };

#if 0
ID021621 B3.2.8 Configuration and Control Register, CCR
UNALIGN_TRP, bit[3]
Controls the trapping of unaligned word or halfword accesses:
- 0 Trapping disabled.
- 1 Trapping enabled.
Unaligned load-store multiples and word or halfword exclusive accesses always fault.
#endif
static void UnalignTrapConfig(bool enable)
{
    if (enable)
    {
        SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    }
    else
    {
        SCB->CCR &= ~SCB_CCR_UNALIGN_TRP_Msk;
    }

    __DSB();
    __ISB();
}

int main(void)
{
/*
NOTE:
Включен запрет на доступ к невыровнянным данным. Это значит что любая попытка доступа к
не выровнянным данным приведет к hard fault
*/
#if 0
    UnalignTrapConfig(true);
#else
/*
NOTE:
Включен запрет на доступ к невыровнянным данным.
*/
    UnalignTrapConfig(false);
#endif

    memset(&packet, 0, sizeof(Packet_t));

/*
1. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(true);

Вывод: нет hard fault.
Это по байтное копирование. Работает корректно.

2. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(true);

Вывод: значения в полях структуры некорректные.
Это происходит из-за того что, в структуре есть padding байт.
При наличии padding, поля param1 и param2 оказываются смещены, и значения интерпретируются некорректно. Корректное копирование
в выровненную структуру требует учета padding (например, заполнять поля вручную).

3. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(false);

Вывод: работает аналогично тесту 1.

4. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(false);

Вывод: работает аналогично тесту 2.
*/
#if 0
    uint8_t size = sizeof(Packet_t);

    uint8_t* dst = (uint8_t*)&packet;
    for (uint8_t i = 0; i < size; i++)
    {
        dst[i] = m_buffer[i];
    }
#endif

/*
1. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(true);

Вывод: hard fault.
Здесь param1 размером 2 байта, требует адрес кратный 2. memcpy пытается записать 2 байта по не выровнянному адресу,
как следствие hard fault.

2. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(true);

Вывод: работает корректно, потому, что при struct + padding переменные лежат по выровненным адресам, и param1, param2
теперь размещены корректно (например, param1 — на 0x2000000A, кратно 2)..

3. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(false);

Вывод: работает корректно.

4. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(false);

Вывод: работает корректно.
*/
#if 0
    uint8_t opCode = m_buffer[0];
    uint16_t param1 = (m_buffer[2] << 8) | (m_buffer[1] << 0);
    uint32_t param2 = (m_buffer[6] << 24) | (m_buffer[5] << 16) | (m_buffer[4] << 8) | (m_buffer[3] << 0);

    memcpy(&packet.opCode, &opCode, sizeof(uint8_t));
    memcpy(&packet.param1, &param1, sizeof(uint16_t));
    memcpy(&packet.param2, &param2, sizeof(uint32_t));

#endif

/*
1. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(true);

Вывод: hard fault.
Здесь param1 собирается как 2 байта, требует адрес кратный 2. При этом packet.param1 лежит по не выровнянному адресу,
как следствие hard fault.

2. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(true);

Вывод: работает корректно, при непосредственном доступе к полям структуры.

3. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(false);

Вывод: работает корректно.

4. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(false);

Вывод: работает корректно.
*/
#if 0
    packet.opCode = (uint8_t)m_buffer[0];

    packet.param1 = ((uint16_t)m_buffer[2] << 8) |
                    (uint16_t)m_buffer[1];

    packet.param2 = ((uint32_t)m_buffer[6] << 24) |
                    ((uint32_t)m_buffer[5] << 16) |
                    ((uint32_t)m_buffer[4] << 8) |
                    (uint32_t)m_buffer[3];
#endif

/*
1. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(true);

Вывод: hard fault.
Здесь источник (m_buffer) и приемник (packet) находятся по не выровнянным адресам, казалось бы memcpy делает
по байтное копирование и может работать корректно с не выровнянными данными, но ВАЖНО, нет гарантии что
компилятор сгенерирует команды LDRB, STRB даже при уровне оптимизации -O0 так тип данных требует операции LDR для 16 бит.
Скорее всего компилятор сгенерирует команды STRH, LDRH, что приведет к hard fault.

2. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(true);

Вывод: hard fault.
Это происходит из-за того что источник данных (m_buffer[1]) имеет размер 16 бит, но при этом его адрес не кратен 2, как
того требует memcpy().

3. Условия теста:
- typedef struct __attribute__((packed))
- UnalignTrapConfig(false);

Вывод: работает корректно.

4. Условия теста:
- typedef struct + padding
- UnalignTrapConfig(false);

Вывод: работает корректно.
*/
#if 0
    memcpy(&packet.opCode, &m_buffer[0], sizeof(packet.opCode));
    memcpy(&packet.param1, &m_buffer[1], sizeof(packet.param1));
    memcpy(&packet.param2, &m_buffer[3], sizeof(packet.param2));
#endif

    while (1);

    return 0;
}

/*
Вывод (test case 1):
Root cause: поле param1 и param2 в packed-структуре оказываются не выровнены в памяти,
и любой доступ к ним через LDRH, STRH, LDR, STR приводит к HardFault, если установлен SCB->CCR.UNALIGN_TRP.
Единствонно правильный доступ - это по байтовое копирование, без memcpy() и прямого доступа к полям структуры param1, param2.

Вывод (test case 2):
- по байтное копирование не приводит к hard fault, но значения в полях некорректрые
- если чисто memcpy(), то hard fault, так как, адрес источника размером 16 бит не кратен 2.

Вывод (test case 3):
При отключенном бите SCB_CCR_UNALIGN_TRP_Msk все варианты работают корректно.

Вывод (test case 4):
По байтовое копирование не работает корректно. Все остальные варианты работают корректно.

Общие замечания:
ВАЖНО: даже memcpy() может генерировать halfword доступ (например, LDRH),
- если тип и выравнивание позволяют, и компилятор решит использовать оптимизированную инструкцию.
Это поведение не определяется стандартом C и зависит от конкретной реализации (например, GCC + опции).

В некоторых случаях (особенно на -O1 и выше), компилятор вообще заменяет memcpy() на прямую запись STRH, STR, если уверен в размере и типе.
*/

