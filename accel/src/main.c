#include "adxl345.h"
#include "adxl345-regs.h"
#include "delay.h"

static uint8_t m_accelId = 0;
static uint8_t m_accelThresTap = 0;

static void OnAccelRead(uint8_t regValue, void* context)
{
    uint8_t* pValue = (uint8_t*)context;
    *pValue = regValue;
}

int main(void)
{
    uint8_t accelThresTap = 0xbb;

    ADXL_Init();

    ADXL_ReadRegisterAsync(ADXL345_DEVID, &OnAccelRead, &m_accelId);

    ADXL_WriteRegisterAsync(ADXL345_THRESH_TAP, &accelThresTap);

    ADXL_ReadRegisterAsync(ADXL345_THRESH_TAP, &OnAccelRead, &m_accelThresTap);

    while (1)
    {
        DelayMs(100);
    }

    return 0;
}
