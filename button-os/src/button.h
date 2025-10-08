#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "gpio-name.h"
#include "gpio.h"

#if 0
Current implementation supports single button. Gpio pin for button statically allocated in button.c.
This implemantation can be improved by passing gpio object from the caller.
#endif

typedef void (*ButtonEventHandler)(void);

/* Button definition */
typedef struct
{
    Gpio_t gpio;
} Button_t;

/*Brief: Button initialization
 * [in] - led - pointer to button object
 * [in] - pinName - name of the pin defined in gpio-name.h
 * [out] - true - button successfully init; false - otherwise
 * */
bool ButtonInit(Button_t* const button, PIN_NAMES gpioName);

/*Brief: Register button press handler
 * [in] - callback - callback function
 * [out] - none
 * */
void ButtonRegisterPressHandler(ButtonEventHandler callback);

#endif /* BUTTON_H */
