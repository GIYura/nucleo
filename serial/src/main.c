#include <stddef.h>

#include "logger.h"

static void AppEnterLowPowerMode(void)
{
    while (!LogIdle());

    LogLevel(LOG_LEVEL_INFO);

    LogPrint("%s", "System enters low power mode...");

    while (1);

/* NOTE: enter low power mode */
    /*__WFI();*/
}

int main(void)
{
    LogInit();

    while (1)
    {
        LogLevel(LOG_LEVEL_WARN);
        LogPrint("%d %u %x %c %s", -15, 17, 10, 'B', "FAIL");

        LogLevel(LOG_LEVEL_DEBUG);
        LogPrint("%d %u %x %c %s", -122, 1700, 1000, 'A', "OK");

        AppEnterLowPowerMode();
    }

    return 0;
}
