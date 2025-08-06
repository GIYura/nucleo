#ifndef LED_GPIO_H
#define LED_GPIO_H

#include "gpio.h"
#include "gpio-name.h"
#include "led-interface.h"

typedef struct
{
    Gpio_t* gpio;
    PIN_NAMES gpioName;
} LedGpioContext_t;

extern LedInterface_t g_ledGpioDriver;

#endif /* LED_GPIO_H */
