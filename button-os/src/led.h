#ifndef LED_H
#define LED_H

#include <stdbool.h>

#include "gpio-name.h"
#include "gpio.h"

/* LED definition */
typedef struct
{
    Gpio_t gpio;
} Led_t;

/*Brief: LED initialization
 * [in] - led - pointer to LED object
 * [in] - pinName - name of the pin defined in gpio-name.h
 * [out] - none
 * */
void LedInit(Led_t* const led, PIN_NAMES pinName);

/*Brief: LED On
 * [in] - led - pointer to LED object
 * [out] - none
 * */
void LedOn(const Led_t* const led);

/*Brief: LED Off
 * [in] - led - pointer to LED object
 * [out] - none
 * */
void LedOff(const Led_t* const led);

/*Brief: LED toggle
 * [in] - led - pointer to LED object
 * [out] - none
 * */
void LedToggle(const Led_t* const led);

#endif /* LED_H */
