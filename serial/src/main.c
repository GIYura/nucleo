#include "logger.h"

int main(void)
{
    LogInit();
    LogSetLevel(LOG_LEVEL_ERROR);

    while (1)
    {
        LogDebug("Debug message");
        LogInfo("Info message");
        LogWarn("Warning message");
        LogError("Error message");
    }

    return 0;
}
