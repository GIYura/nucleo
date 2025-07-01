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
        LogHex(22);
        LogHex(0x22);
        LogHex(0xDEADBEEF);
        LogDec(1234);
        LogDec(-1234);
    }

    return 0;
}
