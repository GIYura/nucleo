#include <string.h>

#include "logger.h"
#include "delay.h"
#include "uart.h"

static char m_messageUart1[] = "Hello STM32F411 Nucleo board over UART-1\r\n";

static Uart_t m_uart1;

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

    while (1)
    {
        UartWrite(&m_uart1, (uint8_t*)m_messageUart1, strlen(m_messageUart1));
    }

    return 0;
}
