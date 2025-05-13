#include "board.h"

#define LED_GREEN_PIN       5
#define LED_WHITE_PIN       13
#define LED_YELLOW_PIN      3

typedef enum
{
    LED_STATE_OFF = 0,
    LED_STATE_ON,
} LED_STATE;

static Led_t m_leds[LED_MAX] = {
    { "GREEN", .port = GPIOA, .pin = LED_GREEN_PIN, .defaultValue = LED_STATE_OFF },
    { "WHITE", .port = GPIOB, .pin = LED_WHITE_PIN, .defaultValue = LED_STATE_ON },
    { "YELLOW", .port = GPIOC, .pin = LED_YELLOW_PIN, .defaultValue = LED_STATE_ON },
};

volatile static uint32_t m_ticks = 0;

Led_t* BoardLedConfig_Get(void)
{
    return m_leds;
}

void SysTick_Handler(void)
{
    m_ticks++;
}

void DelayMs(uint32_t ms)
{
    uint32_t start = m_ticks;

    while ((m_ticks - start) < ms);
}
