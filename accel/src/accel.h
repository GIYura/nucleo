#ifndef ACCEL_H
#define ACCEL_H

#include "spi.h"
#include "gpio.h"

typedef struct
{
    Spi_t spi;
    Gpio_t cs;
} Accel_t;

void AccelInit(Accel_t* accel);
void AccelDetect(Accel_t* accel);

#endif /* ACCEL_H */
