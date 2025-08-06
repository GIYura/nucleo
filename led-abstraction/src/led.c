#include <assert.h>
#include <stddef.h>

#include "led.h"

void LedInit(Led_t* const led, LedInterface_t* driver, void* context)
{
    assert(led != NULL);
    assert(driver != NULL);
    assert(context != NULL);

    led->driver = driver;
    led->context = context;

    led->driver->init(led->context);

    led->initialized = true;
}

void LedOn(const Led_t* const led)
{
    assert(led != NULL);

    if (led->initialized)
    {
        led->driver->write(led->context, 1);
    }
}

void LedOff(const Led_t* const led)
{
    assert(led != NULL);

    if (led->initialized)
    {
        led->driver->write(led->context, 0);
    }
}

void LedToggle(const Led_t* const led)
{
    assert(led != NULL);

    if (led->initialized)
    {
        led->driver->toggle(led->context);
    }
}
