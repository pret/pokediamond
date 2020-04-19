# Makefile to build Pokemon Diamond image

.PHONY: clean tidy all default

# Try to include devkitarm if installed
TOOLCHAIN := $(DEVKITARM)

ifneq (,$(wildcard $(TOOLCHAIN)/base_tools))
include $(TOOLCHAIN)/base_tools
endif

### Default target ###

default: all

# If you are using WSL, it is recommended you build with NOWINE=1.
NOWINE ?= 0

ifeq ($(OS),Windows_NT)
EXE := .exe
WINE := 
else
EXE := 
WINE := "wine "
endif

ifeq ($(NOWINE),1)
WINE := 
endif

################ Target Executable and Sources ###############

BUILD_DIR := build

TARGET := pokediamond.us

ROM := $(BUILD_DIR)/$(TARGET).nds
ELF := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := pokediamond.lcf

# Directories containing source files
SRC_DIRS := src
ASM_DIRS := asm

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
		   
################### Universal Dependencies ###################

# Make tools if out of date
DUMMY != make -s -C tools/mwasmarm_patcher >&2 || echo FAIL
ifeq ($(DUMMY),FAIL)
  $(error Failed to build tools)
endif

##################### Compiler Options #######################

MWCCVERSION := 2.0/base

CROSS   := arm-none-eabi-

MWCCARM  := tools/mwccarm/$(MWCCVERSION)/mwccarm.exe
# Argh... due to EABI version shenanigans, we can't use GNU LD to link together
# MWCC built objects and GNU built ones. mwldarm, however, doesn't care, so we
# have to use mwldarm for now. 
# TODO: Is there a hack workaround to let us go back to GNU LD? Ideally, the
# only dependency should be MWCCARM.
MWLDARM  := tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM := tools/mwccarm/$(MWCCVERSION)/mwasmarm.exe

AS      := $(WINE)$(MWASMARM)
CC      := $(WINE)$(MWCCARM)
CPP     := cpp -P
LD      := $(WINE)$(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
ASFLAGS = -proc arm5te
CFLAGS = -O4,p -proc v5te -thumb -fp soft -lang c -Cpp_exceptions off -interworking

####################### Other Tools #########################

# DS TOOLS
TOOLS_DIR = tools
SHA1SUM = sha1sum
MWASMARM_PATCHER = tools/mwasmarm_patcher/mwasmarm_patcher$(EXE)

######################### Targets ###########################

all: $(ROM)
	@$(SHA1SUM) -c $(TARGET).sha1

clean: tidy
	make -C tools/mwasmarm_patcher clean

tidy:
	$(RM) -r $(BUILD_DIR)

patch_mwasmarm:
	$(MWASMARM_PATCHER) $(MWASMARM)

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.s patch_mwasmarm
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) $(VERSION_CFLAGS) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(ELF): $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT)
	$(LD)  $(BUILD_DIR)/$(LD_SCRIPT) -o $(ELF) $(O_FILES) -nodead -w off

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
