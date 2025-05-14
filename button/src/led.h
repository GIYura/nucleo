#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f411xe.h"

typedef struct
{
    const char* name;
    GPIO_TypeDef* port;
    uint8_t pin;
    bool defaultValue;
} Led_t;

void Led_Init(const Led_t* const led);
void Led_On(const Led_t* const led);
void Led_Off(const Led_t* const led);
void Led_Toggle(const Led_t* const led);

#endif /* LED_H */
