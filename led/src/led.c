#include <assert.h>

#include "led.h"

#include "gpio.h"

static Gpio_t m_leds[LED_COUNT];

void LedInit(LED_IDs id, PIN_NAMES gpioName)
{
    assert(id < LED_COUNT);

    GpioInit(&m_leds[id], gpioName, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);
}

void LedOn(LED_IDs id)
{
    assert(id < LED_COUNT);

    GpioWrite(&m_leds[id], PIN_STATE_HIGH);
}

void LedOff(LED_IDs id)
{
    assert(id < LED_COUNT);

    GpioWrite(&m_leds[id], PIN_STATE_LOW);
}

void LedToggle(LED_IDs id)
{
    assert(id < LED_COUNT);

    GpioToggle(&m_leds[id]);
}
