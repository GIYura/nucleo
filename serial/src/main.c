#include "logger.h"
#include "delay.h"
#include "uart.h"

static char m_bufferTx[] = "Hello\r\n";
static Usart_t m_usart;

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

    UartInit(&m_usart, BAUD_921600);

    while (1)
    {
        UartWrite(&m_usart, m_bufferTx);

        DelayMs(1000);
    }

    return 0;
}
