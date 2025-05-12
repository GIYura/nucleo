#include "board.h"

typedef enum
{
    LED_STATE_OFF = 0,
    LED_STATE_ON,
} LED_STATE;

#define LED_GREEN_PIN   5
#define LED_WHITE_PIN   13
#define LED_YELLOW_PIN   3

static Led_t m_leds[LED_MAX] = {
    { "GREEN", .port = GPIOA, .pin = LED_GREEN_PIN, .defaultValue = LED_STATE_OFF },
    { "WHITE", .port = GPIOB, .pin = LED_WHITE_PIN, .defaultValue = LED_STATE_ON },
    { "YELLOW", .port = GPIOC, .pin = LED_YELLOW_PIN, .defaultValue = LED_STATE_ON },
};

Led_t* BoardLedConfig_Get(void)
{
    return m_leds;
}
