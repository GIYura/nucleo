#include "logger.h"

static void AppEnterLowPowerMode(void)
{
    while (!LogIdle());

    LogLevel(LOG_LEVEL_INFO);

    LogPrint("%s", "System enters low power mode...");

    while (1);

    /*TODO:*/
    /*__WFI();*/
}

int main(void)
{
    LogInit();
    LogLevel(LOG_LEVEL_ERROR);

    while (1)
    {
        LogPrint("%d %u %x %c %s", -15, 17, 10, 'B', "FAIL");
        LogPrint("%d %u %x %c %s", -122, 1700, 1000, 'A', "OK");

        AppEnterLowPowerMode();
    }

    return 0;
}
