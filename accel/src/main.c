#include "accel.h"
#include "adxl345.h"

#include "delay.h"

static uint8_t accelId = 0;

int main(void)
{
    AccelInit();

    AccelGetId(&accelId);

    while (1)
    {
        DelayMs(100);
    }

    return 0;
}
