#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include <stdbool.h>

typedef struct
{
    void (*init)(void* context);
    void (*write)(void* context, bool newValue);
    void (*toggle)(void* context);
} LedInterface_t;

#endif /* LED_INTERFACE_H */
