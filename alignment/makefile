##############################################
# Makefile for alignment test
# Define GCC_PATH (e.g. GCC_PATH=/path/to/gcc/bin) to set compiler path
# Define SMT32 SDK path (e.g. SDK_PATH=/path/to/stm32/sdk)
# Define Open OCD path (e.g. OCD_PATH=/path/to/openocd/)
# Define board config. file (used by OCD)
##############################################

# Check if .config file is present and print error if not
ifeq (, $(wildcard .config))
    $(error ERROR: '.config' is missing. Please create '.config' file based on default.config as template.)
endif

-include .config

#######################
# Pre-compiled lib for linker
#######################

#######################
# Source directory
#######################
STM32_DRIVERS = $(SDK_PATH)/Drivers
SRCDIR = src

#######################
# Linker script path
#######################
LINKER_SCRIPT = $(SRCDIR)/hal/stm32f4xx/stm32f411retx_flash.ld

#######################
# Output directory
#######################
OBJDIR = Obj
BUILD = Build

#######################
# Binary
#######################
PREFIX = arm-none-eabi-
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size

#######################
# CFLAGS
#######################
CFLAGS = -mcpu=$(CPU) \
         -mthumb \
         -std=$(STANDARD) \
         -g $(OPT)\
         -MP \
         -MMD \
         -Wall \
         -ffunction-sections \
         -fdata-sections

#######################
# List of directories
#######################
DIRS = $(STM32_DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
       $(STM32_DRIVERS)/CMSIS/Include \
       $(SRCDIR) \
       $(SRCDIR)/hal/stm32f4xx \

#######################
# List of source files (.c)
#######################
SRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

#######################
# List of ASM files (.s)
#######################
ASMS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.s))

#######################
# List of header files (.h)
#######################
INC = $(foreach dir, $(DIRS), $(addprefix -I, $(dir)))

#######################
# Replace all '*.c' and all '.s' files to '.o'
#######################
COBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))
ASMOBJS = $(patsubst %.s, $(OBJDIR)/%.o, $(ASMS))

#######################
# List of all relocatable object files (.o)
#######################
OBJS = $(COBJS) $(ASMOBJS)

#######################
# Variables
#######################
CPU = cortex-m4
MCU = STM32F411xE
STANDARD = c99
OPT = -O0
DEFINES = -DNDEBUG=1 \
          -D$(MCU)
          
ALIGN = align
TARGET = $(BUILD)/$(ALIGN)
EXEC = $(TARGET).elf
RM = rm -rf

#######################
# LDFLAGS (linker flags)
# NOTE: use newlib-nano link to libc_nano.a
# NOTE: --gc-sections - garbage collection (delete unused data and functions)
#######################
LDFLAGS = -T $(LINKER_SCRIPT) -Xlinker --gc-sections -Xlinker \
  -Map=$(TARGET).map --specs=nano.specs -u _print_float -Wl,--print-memory-usage -o $(TARGET).elf

#######################
# Default action: build all
#######################
all: $(TARGET)
$(TARGET): $(EXEC) $(TARGET).bin

$(EXEC): $(OBJS)
	@mkdir -p $(@D)
	@echo '============='
	@echo 'Linking the target $@'
	@echo '============='
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIB) -o $@
	@echo 'Linking Successful !!!'

$(OBJDIR)/%.o: %.c
	@echo '> Building C file $<'
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFINES) $(INC) -c $< -o $@

$(OBJDIR)/%.o: %.s
	@echo '> Building ASM file $<'
	@mkdir -p $(dir $@)
	$(AS) $(CFLAGS) -c $< -o $@
	
$(TARGET).bin: $(TARGET).elf
	@echo '> Building bin file from $<'
	@mkdir -p $(dir $@)
	$(CP) -O binary $< $@
	@echo '!!! ====== DONE =======!!!'
	
#######################
# Dependency
-include $(COBJS:%.o=%.d)
#######################

.PHONY: all clean

clean: ## 'clean'
	@echo 'Cleaning...Done!'
	@$(RM) $(OBJDIR) $(BUILD)

# Run open OCD server
ocd: ## Run 'ocd' server
	@echo 'OCD running!'
	$(OCD_PATH)/openocd -f $(BOARD_CFG)

# Run GDB client
gdb: ## Debug over 'gdb'
	@echo 'GDB running!'
	$(GCC_PATH)/$(PREFIX)gdb $(TARGET).elf

# Load .bin to the target
flash: $(TARGET).bin ## 'flash' .bin to target over st-link
	@echo 'Flash running!'
	st-flash write $(TARGET).bin 0x8000000
	
help: ## 'help'
	@echo 'Available targets:'
	@grep -E '^[a-zA-Z_-]+:.*?## ' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-12s\033[0m %s\n", $$1, $$2}'

#debug:
#	@echo $(GCC_PATH)/$(PREFIX)gdb
#	@echo 'DIR:' $(DIRS)
#	@echo 'SRC:' $(SRC)
#	@echo 'INC:' $(INC)
#	@echo 'CFLAGS:' $(CFLAGS)
#	@echo 'COBJS:' $(COBJS)
#	@echo 'ASMOBJS:' $(ASMOBJS)
#	@echo 'OBJS:' $(OBJS)
#	@echo 'deps:' $(COBJS:%.o=%.d)
