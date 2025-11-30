##############################################
# Multi-Platform Build
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
SUBMODULES = submodules
SRCDIR = src

#######################
# Target platform
#######################
PLATFORM ?= 

SUPPORTED_PLATFORMS := stm32f4xx cc32xx atmega328
IGNORE_GOAL := clean help ocd gdb flash debug

ifeq ($(MAKECMDGOALS),)
    GOAL := all
else
    GOAL := $(MAKECMDGOALS)
endif

ifeq (,$(filter $(GOAL),$(IGNORE_GOAL)))

    ifeq ($(PLATFORM),)
        $(info Supported platforms: $(SUPPORTED_PLATFORMS))
        $(error PLATFORM is undefined. Usage: make PLATFORM=$(SUPPORTED_PLATFORMS))
    endif

    ifeq (,$(filter $(PLATFORM),$(SUPPORTED_PLATFORMS)))
        $(error Unsupported PLATFORM '$(PLATFORM)'. Supported: $(SUPPORTED_PLATFORMS))
    endif

endif

#############################################
# Load platform-specific configuration
#############################################
.DEFAULT_GOAL := all

ifneq ($(PLATFORM),)
    include $(SUBMODULES)/platforms/config/$(PLATFORM).mk
endif

#######################
# Output directory
#######################
OBJDIR = Obj
BUILD = Build

#######################
# Binary
#######################
CC = $(GCC_PATH)/$(TOOLCHAIN_PREFIX)gcc
AS = $(GCC_PATH)/$(TOOLCHAIN_PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(TOOLCHAIN_PREFIX)objcopy
SZ = $(GCC_PATH)/$(TOOLCHAIN_PREFIX)size

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

DIRS = \
    $(SUBMODULES)/hal/include \
    $(PLATFORM_DIRS) \
    $(SRCDIR) \
    $(PLATFORM_BOOT_DIR) \
    $(SUBMODULES)/core/assert 
    #$(SUBMODULES)/delay \
    #$(SUBMODULES)/lib/drivers/esp8266 \
    #$(SUBMODULES)/utils \
    #$(SUBMODULES)/buffer \
    #$(SUBMODULES)/event
       
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
STANDARD = c99
OPT = -O0
DEFINES += -DNDEBUG=1
APPLICATION = esp
TARGET = $(BUILD)/$(PLATFORM)-$(APPLICATION)
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

# Run GDB client
debug: ## Debug over 'gdb'
	@echo 'GDB running!'
	$(GCC_PATH)/$(TOOLCHAIN_PREFIX)gdb $(TARGET).elf
	
help:
	@echo "Common targets: clean, all, debug"
ifneq ($(PLATFORM),)
	@$(MAKE) --no-print-directory help-$(PLATFORM)
endif

#debug:
#	@echo $(GCC_PATH)/$(TOOLCHAIN_PREFIX)gdb
#	@echo 'DIR:' $(DIRS)
#	@echo 'SRC:' $(SRC)
#	@echo 'INC:' $(INC)
#	@echo 'CFLAGS:' $(CFLAGS)
#	@echo 'COBJS:' $(COBJS)
#	@echo 'ASMOBJS:' $(ASMOBJS)
#	@echo 'OBJS:' $(OBJS)
#	@echo 'deps:' $(COBJS:%.o=%.d)
