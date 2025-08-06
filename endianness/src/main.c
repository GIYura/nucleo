#include <stdint.h>

#include "stm32f411xe.h"

#include "helper.h"

typedef enum
{
    LITTLE = 0,
    BIG,
    NONE
} ENDIANNESS;

static ENDIANNESS m_endianness = NONE;

int main(void)
{
#if 0
#if 0
This demo code shows how memory is aligned and packed.
Variables a and b declared as uint16_t and defined in dedicated file to force compiler actually read the memory.
Since these variable are const, compiler might inject const values directly into x, y.
Variables a and b located into .rodata section b/c they are const. Since they are 16 bits long, the compiled packed
them together into single 32 bit memory cell.

Then, we read them into 32 bits x, y. To do this, the compiler generates assembly intructions LDRH (load half word).
Since z is purposefully casted to uint32_t, to read it, the compiler generates other instruction LDR (load word).
So, by default, two variables stored at the same start address (2 bytes apart).
Example:
a address = 080002c4
b address = 080002c6

If a and b aligned by 4 like this:
const uint16_t a __attribute__((aligned(4))) = 0xAAAA;
this force compiler to locate a and b in separate addresses (4 bytes apart).
Example:
a address = 080002c4
b address = 080002c8
#endif
    uint32_t x = a1;
    uint32_t y = b1;
    uint32_t z = *((uint32_t*)&a1);
#endif

#if 0
How-to-define-endianness?

1. Read .elf file. To do this, run command: arm-none-eabi-readelf -h
2. Check bit 15 in register AIRCR (ID021621 B3.2.6 Application Interrupt and Reset Control Register, AIRCR)
- bit is set - big endian
- bit is clear - little endian
NOTE: see code in example 2.
3. See code in the example 3.
#endif

/* Example 2 */
#if 0
    if (SCB->AIRCR & SCB_AIRCR_ENDIANESS_Msk)
    {
        m_endianness = BIG;
    }
    else
    {
        m_endianness = LITTLE;
    }
#endif

/* Example 3 */
#if 0
    uint16_t value = 0x0001;
    uint8_t* p = (uint8_t*)&value;

    if (*p)
    {
        m_endianness = LITTLE;
    }
    else
    {
        m_endianness = BIG;
    }
#endif

    return 0;
}

