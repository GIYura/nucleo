#include "logger.h"
#include "delay.h"
#include "uart.h"

static uint8_t m_bufferTx[] = {1,2,3,4};

int main(void)
{
#if 0
    LogInit();
    LogSetLevel(LOG_LEVEL_DEBUG);

    LogDebug("Debug message\r\n");
    LogInfo("Info message\r\n");
    LogWarn("Warn message\r\n");
    LogError("Error message\r\n");
#endif

    UartInit();

    while (1)
    {
        UartWrite(m_bufferTx, sizeof(m_bufferTx));

        DelayMs(1000);
    }

    return 0;
}
