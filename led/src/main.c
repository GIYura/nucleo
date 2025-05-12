#include <assert.h>
#include "board.h"
#include "led.h"

static void Delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm__("nop");
    }
}

static Led_t* m_leds;

int main(void)
{
    m_leds = BoardLedConfig_Get();

    assert(m_leds);

    for (uint8_t i = 0; i < LED_MAX; i++)
    {
        Led_Init(&m_leds[i]);
    }

    while (1)
    {
        for (uint8_t i = 0; i < LED_MAX; i++)
        {
            Led_Toggle(&m_leds[i]);
        }

        Delay(500000);
    }

    return 0;
}
