#include <assert.h>

#include "board.h"
#include "led.h"

static Led_t* m_leds;

int main(void)
{
    /* setup SysTick 1ms */
    SysTick_Config(SystemCoreClock / 1000);

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

        DelayMs(200);
    }

    return 0;
}
