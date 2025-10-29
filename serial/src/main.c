#include <stddef.h>

#include "logger.h"
#include "cli.h"
#include "cli-commands.h"
#include "uart-service.h"
#include "delay.h"

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
    UartServiceInit();

    CliInit();
    CliCommandsInit();

    LogLevel(LOG_LEVEL_DEBUG);

    LogPrint("%s", "CLI ready. Type 'help' for list of commands\r\n");

    while (1)
    {

    }

    return 0;
}
