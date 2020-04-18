# Makefile to build Pokemon Diamond image

### Default target ###

default: all

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
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

##################### Compiler Options #######################

MWCCVERSION := 2.0/base

CROSS   := arm-linux-gnueabi-

MWCCARM  := tools/mwccarm/$(MWCCVERSION)/mwccarm.exe
# Argh... due to EABI version shenanigans, we can't use GNU LD to link together
# MWCC built objects and GNU built ones. mwldarm, however, doesn't care, so we
# have to use mwldarm for now. 
# TODO: Is there a hack workaround to let us go back to GNU LD? Ideally, the
# only dependency should be MWCCARM.
MWLDARM  := tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM := tools/mwccarm/$(MWCCVERSION)/mwasmarm.exe

AS      := $(MWASMARM)
CC      := $(MWCCARM)
CPP     := cpp -P
LD      := $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
ASFLAGS = -proc arm5te
CFLAGS = -O4,p -proc v5te -thumb -fp soft -lang c -Cpp_exceptions off -interworking -i nitro

####################### Other Tools #########################

# DS TOOLS
TOOLS_DIR = tools
SHA1SUM = sha1sum
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx

TOOLDIRS = $(filter-out $(TOOLS_DIR)/mwccarm,$(wildcard $(TOOLS_DIR)/*))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

######################### Targets ###########################

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all,$(MAKECMDGOALS)))
$(call infoshell, $(MAKE) tools)
else
NODEP := 1
endif

.PHONY: all clean tools $(TOOLDIRS)

MAKEFLAGS += --no-print-directory

all: $(ROM)
	@$(SHA1SUM) -c $(TARGET).sha1

clean:
	$(RM) -r $(BUILD_DIR)

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) $(VERSION_CFLAGS) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(ELF): $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT)
	$(LD)  $(BUILD_DIR)/$(LD_SCRIPT) -o $(ELF) $(O_FILES) -nodead -w off

$(ROM): $(ELF)
	$(OBJCOPY) -O binary --gap-fill=0xFF --pad-to=0x04000000 $< $@

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

%.4bpp: %.png
	$(GFX) $< $@

%.gbapal: %.png
	$(GFX) $< $@

%.gbapal: %.pal
	$(GFX) $< $@

%.lz: %
	$(GFX) $< $@

$(BUILD_DIR)/asm/icon.o: graphics/icon.4bpp graphics/icon.gbapal

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
