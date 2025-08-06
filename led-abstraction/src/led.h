#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>

#include "led-interface.h"

/* LED definition */
typedef struct
{
    LedInterface_t* driver;
    void* context;
    bool initialized;
} Led_t;

/*Brief: LED initialization
 * [in] - led - pointer to LED object
 * [in] - driver - pointer to LED driver
 * [in] - context - pointer to LED context (LED specific)
 * [out] - none
 * */
void LedInit(Led_t* const led, LedInterface_t* driver, void* context);

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
