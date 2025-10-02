#include <stddef.h>

#include "assert.h"
#include "led.h"

/* array of gpios to control LEDs */
static Gpio_t m_ledGpio[LED_MAX];

/* gpio index */
static uint8_t m_ledGpioIndex = 0;

uint8_t LedInit(Led_t* const led, PIN_NAMES pinName)
{
    ASSERT(led != NULL);

    if (m_ledGpioIndex >= LED_MAX)
    {
        return 1;
    }

    led->gpio = &m_ledGpio[m_ledGpioIndex++];

    GpioInit(led->gpio, pinName, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    led->initialized = true;

    return 0;
}

void LedOn(const Led_t* const led)
{
    ASSERT(led != NULL);

    if (led->initialized)
    {
        GpioWrite(led->gpio, PIN_STATE_HIGH);
    }
}

void LedOff(const Led_t* const led)
{
    ASSERT(led != NULL);

    if (led->initialized)
    {
        GpioWrite(led->gpio, PIN_STATE_LOW);
    }
}

void LedToggle(const Led_t* const led)
{
    ASSERT(led != NULL);

    if (led->initialized)
    {
        GpioToggle(led->gpio);
    }
}
