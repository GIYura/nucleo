#include "gpio.h"

volatile static uint32_t m_ticks = 0;

static Gpio_t m_led;

void SysTick_Handler(void)
{
    m_ticks++;
}

static void DelayMs(uint32_t ms)
{
    uint32_t start = m_ticks;

    while ((m_ticks - start) < ms);
}

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000);

    GpioInit(&m_led, PA_5, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    while (1)
    {
        GpioToogle(&m_led);
        DelayMs(200);
    }

    return 0;
}
