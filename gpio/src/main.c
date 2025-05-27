#include "gpio.h"

typedef enum
{
    GREEN_INT = 0,
    GREEN_EXT,
    YELLOW,
    WHITE,
    LED_NUMBER
} LED_COLORS;

volatile static uint32_t m_ticks = 0;

static Gpio_t m_leds[LED_NUMBER];
static Gpio_t m_button;
static uint32_t m_buttonState;

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

    GpioInit(&m_leds[GREEN_INT], PA_5, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_HIGH);
    GpioInit(&m_leds[GREEN_EXT], PA_0, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_HIGH);
    GpioInit(&m_leds[YELLOW], PC_3, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_HIGH);
    GpioInit(&m_leds[WHITE], PB_13, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_HIGH);

    GpioInit(&m_button, PA_1, PIN_MODE_INPUT, PIN_TYPE_PULL_UP, PIN_SPEED_HIGH, PIN_CONFIG_PUSH_PULL, 0);

    while (1)
    {
        for (uint8_t i = 0; i < LED_NUMBER; i++)
        {
            GpioToogle(&m_leds[i]);
        }

        m_buttonState = GpioRead(&m_button);

        DelayMs(250);
    }

    return 0;
}
