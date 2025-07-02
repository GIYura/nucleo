#include "logger.h"

static uint32_t m_counter = 0;

int main(void)
{
    LogInit(LOG_LEVEL_ERROR);

    while (1)
    {
        LogPrint("%d %u %x %c %s", -15, 17, 10, 'B', "FAIL");

        LogFlush();

        if (LogIdle())
        {
            ++m_counter;
        }
    }

    return 0;
}
