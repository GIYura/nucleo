#include <stddef.h>
#include <stdlib.h>

#include "cli.h"
#include "cli-commands.h"
#include "logger.h"

static void CmdHelp(int argc, char** argv)
{
    LogPrint("Commands:\r\n");
    LogPrint("  read <reg>\r\n");
    LogPrint("  write <reg> <val>\r\n");
}

static void CmdRead(int argc, char** argv)
{
    if (argc < 2)
    {
        LogPrint("Usage: read <reg>\r\n");
        return;
    }

    /* TODO: stub */
    uint8_t reg = (uint8_t)strtol(argv[1], NULL, 16);
    uint8_t val = 0xab;

    LogPrint("Reg [%x] = %x\r\n", reg, val);
}

static void CmdWrite(int argc, char** argv)
{
    if (argc < 3)
    {
        LogPrint("Usage: write <reg> <val>\r\n");
        return;
    }

    /* TODO: stub */
    uint8_t reg = (uint8_t)strtol(argv[1], NULL, 16);
    uint8_t val = (uint8_t)strtol(argv[2], NULL, 16);

    LogPrint("Reg [%x] = %x\r\n", reg, val);
}

void CliCommandsInit(void)
{
    CliRegisterCommand("help", &CmdHelp, "Commands List");
    CliRegisterCommand("read", &CmdRead, "Read");
    CliRegisterCommand("write", &CmdWrite, "Write");
}

