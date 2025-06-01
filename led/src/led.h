#ifndef LED_H
#define LED_H

#include "gpio-name.h"

typedef enum
{
    LED_GREEN = 0,
    LED_YELLOW,
    LED_WHITE,
    LED_GREEN_EXT,
    LED_COUNT,
} LED_IDs;

void LedInit(LED_IDs id, PIN_NAMES gpioName);
void LedOn(LED_IDs id);
void LedOff(LED_IDs id);
void LedToggle(LED_IDs id);

#endif /* LED_H */
