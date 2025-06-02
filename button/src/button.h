#ifndef BUTTON_H
#define BUTTON_H

#include "gpio-name.h"

typedef void (*ButtonEventHandler)(void);

typedef enum
{
    BUTTON_INTERNAL = 0,
    BUTTON_COUNT
} BUTTON_IDs;

void ButtonInit(BUTTON_IDs id, PIN_NAMES gpioName);
void ButtonRegisterPressHandler(ButtonEventHandler callback);

#endif /* BUTTON_H */
