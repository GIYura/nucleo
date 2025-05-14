#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f411xe.h"

typedef void (*ButtonEventHandler)(void* context);

typedef struct
{
    const char* name;
    GPIO_TypeDef* port;
    uint8_t pin;
    uint32_t debounceTimeout;
} Button_t;

void Button_Init(const Button_t* const button);
void Button_RegisterPressHandler(const Button_t* const button, ButtonEventHandler callback);

#endif /* BUTTON_H */
