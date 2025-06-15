#include "logger.h"
#include "delay.h"
#include "uart.h"

static char m_messageUart1[] = "Hello UART-1\r\n";
static char m_messageUart6[] = "Hello UART-6\r\n";

static Uart_t m_uart1;
static Uart_t m_uart6;

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

    UartInit(&m_uart1, UART_1, BAUD_921600);
    UartInit(&m_uart6, UART_6, BAUD_115200);

    while (1)
    {
        UartWrite(&m_uart1, m_messageUart1);
        UartWrite(&m_uart6, m_messageUart6);

        DelayMs(1000);
    }

    return 0;
}
