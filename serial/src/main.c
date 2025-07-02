#include "logger.h"

int main(void)
{
    LogInit(LOG_LEVEL_ERROR);

    while (1)
    {
        LogPrint("%d %u %x %c %s", -15, 17, 10, 'A', "FAIL");
    }

    return 0;
}
