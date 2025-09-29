#include <stddef.h>

#include "adxl345.h"
#include "adxl345-regs.h"
#include "delay.h"
#include "event.h"
#include "ignore.h"

static uint8_t m_accelId = 0;
static Acceleration_t m_accelVector = {0};

static void OnAccelRegisterRead(void* data, void* context)
{
    uint8_t* pValue = (uint8_t*)context;
    *pValue = *(uint8_t*)data;

    Event_t e = { .type = EVENT_ACCEL_ID_READY, .context = pValue };

    EventQueue_Enqueue(&e);
}

static void OnAccelRegisterWrite(void* data, void* context)
{
    IGNORE(data);
    IGNORE(context);

    Event_t e = { .type = EVENT_ACCEL_CONFIG_READY, .context = NULL };

    EventQueue_Enqueue(&e);
}

static void OnAccelVectorRead(void* vector, void* context)
{
    Acceleration_t* pValue = (Acceleration_t*)context;
    Acceleration_t* pVector = (Acceleration_t*)vector;

    pValue->x = pVector->x;
    pValue->y = pVector->y;
    pValue->z = pVector->z;

    Event_t e = { .type = EVENT_ACCEL_VECTOR_READY, .context = pValue };

    EventQueue_Enqueue(&e);
}

int main(void)
{
    uint8_t accalPowerControl = 0x08;
    EventQueueInit();

    ADXL_InitI2C();

    ADXL_ReadRegisterAsyncI2C(ADXL345_DEVID, &OnAccelRegisterRead, &m_accelId);

#if 0
    EventQueueInit();

    ADXL_Init();

    ADXL_ReadRegisterAsync(ADXL345_DEVID, &OnAccelRegisterRead, &m_accelId);

    uint8_t accelMeasure = 0x08;
    ADXL_WriteRegisterAsync(ADXL345_POWER_CTL, &accelMeasure);

    ADXL_ReadVectorAsync(ADXL345_DATAX0, &OnAccelVectorRead, &m_accelVector);
#endif

    while (1)
    {
        Event_t e;
        if (EventQueue_Dequeue(&e))
        {
            switch (e.type)
            {
                case EVENT_ACCEL_VECTOR_READY:
                    /* vector is ready to process */
                    DelayMs(10);
                    ADXL_ReadVectorAsyncI2C(ADXL345_DATAX0, &OnAccelVectorRead, &m_accelVector);
                    break;

                case EVENT_ACCEL_CONFIG_READY:
                    ADXL_ReadVectorAsyncI2C(ADXL345_DATAX0, &OnAccelVectorRead, &m_accelVector);
                    break;

                case EVENT_ACCEL_ID_READY:
                    if (m_accelId == ADXL345_ID)
                    {
                        ADXL_WriteRegisterAsyncI2C(ADXL345_POWER_CTL, &OnAccelRegisterWrite, &accalPowerControl);
                    }
                    break;

                case EVENT_BUTTON_PRESSED:
                    /*TODO:*/
                    break;

                case EVENT_TIMER_TICK:
                    /*TODO:*/
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}
