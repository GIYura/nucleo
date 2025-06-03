#ifndef LED_H
#define LED_H

#include <stdbool.h>

#include "gpio-name.h"
#include "gpio.h"

#if 0
Current implementation support 4 LEDs. Gpio pins for LEDs statically allocated in led.c.
This implemantation can be improved by passing gpio object from the caller.
#endif

#define LED_MAX     4   /* max available LEDs in the system */

/* LED definition */
typedef struct
{
    Gpio_t* gpio;
    bool initialized;
} Led_t;

/*Brief: LED initialization
 * [in] - led - pointer to LED object
 * [in] - pinName - name of the pin defined in gpio-name.h
 * [out] - 0 - success; 1 - fail (run out of available gpio)
 * */
uint8_t LedInit(Led_t* const led, PIN_NAMES pinName);

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
