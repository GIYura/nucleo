#include "accel.h"
#include "adxl345.h"

void AccelInit(void)
{
    ADXL_Init();
}

void AccelGetId(uint8_t* const id)
{
    ADXL_GetId(id);
}

void AccelDumpRegisters(void)
{
    ADXL_DumpRegisters();
}
