#include "accel.h"

static void AccelEnable(Accel_t* accel)
{
    GpioWrite(&accel->cs, 0);
}

void AccelInit(Accel_t* accel)
{
    SpiInit(&accel->spi, SPI_1, CPOL_0, CPHA_0, 4000000);

    GpioInit(&accel->cs, PA_0, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_HIGH, PIN_CONFIG_PUSH_PULL, 1);
}

void AccelDetect(Accel_t* accel)
{
    GpioWrite(&accel->cs, 0);

    SpiTransmit()

    GpioWrite(&accel->cs, 1);
}

