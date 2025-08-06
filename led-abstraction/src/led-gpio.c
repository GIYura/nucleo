#include "led-gpio.h"

static void LedGpioInit(void* context)
{
    LedGpioContext_t* ctx = (LedGpioContext_t*)context;

    GpioInit(ctx->gpio, ctx->gpioName, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);
}

static void LedGpioWrite(void* context, bool newValue)
{
    LedGpioContext_t* ctx = (LedGpioContext_t*)context;

    GpioWrite(ctx->gpio, newValue);
}

static void LedGpioToggle(void* context)
{
    LedGpioContext_t* ctx = (LedGpioContext_t*)context;

    GpioToggle(ctx->gpio);
}

LedInterface_t g_ledGpioDriver = { .init = &LedGpioInit, .write = &LedGpioWrite, .toggle = &LedGpioToggle };

