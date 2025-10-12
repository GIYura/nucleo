#include <stddef.h>

#include "assert.h"
#include "led.h"

void LedInit(Led_t* const led, PIN_NAMES pinName)
{
    ASSERT(led != NULL);

    GpioInit(&led->gpio, pinName, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);
}

void LedOn(const Led_t* const led)
{
    ASSERT(led != NULL);

    GpioWrite(&led->gpio, PIN_STATE_HIGH);
}

void LedOff(const Led_t* const led)
{
    ASSERT(led != NULL);

    GpioWrite(&led->gpio, PIN_STATE_LOW);
}

void LedToggle(const Led_t* const led)
{
    ASSERT(led != NULL);

    GpioToggle(&led->gpio);
}
