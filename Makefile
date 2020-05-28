# Makefile to build Pokemon Diamond image

.PHONY: clean tidy all default patch_mwasmarm

# Try to include devkitarm if installed
TOOLCHAIN := $(DEVKITARM)

ifneq (,$(wildcard $(TOOLCHAIN)/base_tools))
include $(TOOLCHAIN)/base_tools
endif

### Default target ###

default: all

# If you are using WSL, it is recommended you build with NOWINE=1.
WSLENV ?= no
ifeq ($(WSLENV),)
NOWINE = 1
else
NOWINE = 0
endif

ifeq ($(OS),Windows_NT)
EXE := .exe
WINE := 
else
EXE := 
WINE := wine
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
ASM_DIRS := asm data files

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \

ARM9SBIN := arm9/build/arm9.sbin
ARM7SBIN := arm7/build/arm7.sbin

BINFILES = \
	arm9/build/arm9.bin \
	arm9/build/arm9_table.bin \
	arm9/build/arm9_defs.bin \
	arm7/build/arm7.bin \
	arm9/build/MODULE_00.bin \
	arm9/build/MODULE_01.bin \
	arm9/build/MODULE_02.bin \
	arm9/build/MODULE_03.bin \
	arm9/build/MODULE_04.bin \
	arm9/build/MODULE_05.bin \
	arm9/build/MODULE_06.bin \
	arm9/build/MODULE_07.bin \
	arm9/build/MODULE_08.bin \
	arm9/build/MODULE_09.bin \
	arm9/build/MODULE_10.bin \
	arm9/build/MODULE_11.bin \
	arm9/build/MODULE_12.bin \
	arm9/build/MODULE_13.bin \
	arm9/build/MODULE_14.bin \
	arm9/build/MODULE_15.bin \
	arm9/build/MODULE_16.bin \
	arm9/build/MODULE_17.bin \
	arm9/build/MODULE_18.bin \
	arm9/build/MODULE_19.bin \
	arm9/build/MODULE_20.bin \
	arm9/build/MODULE_21.bin \
	arm9/build/MODULE_22.bin \
	arm9/build/MODULE_23.bin \
	arm9/build/MODULE_24.bin \
	arm9/build/MODULE_25.bin \
	arm9/build/MODULE_26.bin \
	arm9/build/MODULE_27.bin \
	arm9/build/MODULE_28.bin \
	arm9/build/MODULE_29.bin \
	arm9/build/MODULE_30.bin \
	arm9/build/MODULE_31.bin \
	arm9/build/MODULE_32.bin \
	arm9/build/MODULE_33.bin \
	arm9/build/MODULE_34.bin \
	arm9/build/MODULE_35.bin \
	arm9/build/MODULE_36.bin \
	arm9/build/MODULE_37.bin \
	arm9/build/MODULE_38.bin \
	arm9/build/MODULE_39.bin \
	arm9/build/MODULE_40.bin \
	arm9/build/MODULE_41.bin \
	arm9/build/MODULE_42.bin \
	arm9/build/MODULE_43.bin \
	arm9/build/MODULE_44.bin \
	arm9/build/MODULE_45.bin \
	arm9/build/MODULE_46.bin \
	arm9/build/MODULE_47.bin \
	arm9/build/MODULE_48.bin \
	arm9/build/MODULE_49.bin \
	arm9/build/MODULE_50.bin \
	arm9/build/MODULE_51.bin \
	arm9/build/MODULE_52.bin \
	arm9/build/MODULE_53.bin \
	arm9/build/MODULE_54.bin \
	arm9/build/MODULE_55.bin \
	arm9/build/MODULE_56.bin \
	arm9/build/MODULE_57.bin \
	arm9/build/MODULE_58.bin \
	arm9/build/MODULE_59.bin \
	arm9/build/MODULE_60.bin \
	arm9/build/MODULE_61.bin \
	arm9/build/MODULE_62.bin \
	arm9/build/MODULE_63.bin \
	arm9/build/MODULE_64.bin \
	arm9/build/MODULE_65.bin \
	arm9/build/MODULE_66.bin \
	arm9/build/MODULE_67.bin \
	arm9/build/MODULE_68.bin \
	arm9/build/MODULE_69.bin \
	arm9/build/MODULE_70.bin \
	arm9/build/MODULE_71.bin \
	arm9/build/MODULE_72.bin \
	arm9/build/MODULE_73.bin \
	arm9/build/MODULE_74.bin \
	arm9/build/MODULE_75.bin \
	arm9/build/MODULE_76.bin \
	arm9/build/MODULE_77.bin \
	arm9/build/MODULE_78.bin \
	arm9/build/MODULE_79.bin \
	arm9/build/MODULE_80.bin \
	arm9/build/MODULE_81.bin \
	arm9/build/MODULE_82.bin \
	arm9/build/MODULE_83.bin \
	arm9/build/MODULE_84.bin \
	arm9/build/MODULE_85.bin \
	arm9/build/MODULE_86.bin

SBINFILES = $(BINFILES:%.bin=%.sbin)

##################### Compiler Options #######################

MWCCVERSION = 2.0/base

CROSS   := arm-none-eabi-

MWCCARM  = tools/mwccarm/$(MWCCVERSION)/mwccarm.exe
# Argh... due to EABI version shenanigans, we can't use GNU LD to link together
# MWCC built objects and GNU built ones. mwldarm, however, doesn't care, so we
# have to use mwldarm for now.
# TODO: Is there a hack workaround to let us go back to GNU LD? Ideally, the
# only dependency should be MWCCARM.
MWLDARM  = tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM = tools/mwccarm/$(MWCCVERSION)/mwasmarm.exe

AS      = $(WINE) $(MWASMARM)
CC      = $(WINE) $(MWCCARM)
CPP     := cpp -P
LD      = $(WINE) $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
ASFLAGS = -proc arm5te
CFLAGS = -O4,p -proc arm946e -fp soft -lang c99 -Cpp_exceptions off -ir include -ir include-mw -ir arm9/lib/include
LDFLAGS = -map -nodead -w off -proc v5te -interworking -map -symtab -m _start

####################### Other Tools #########################

# DS TOOLS
TOOLS_DIR = tools
SHA1SUM = sha1sum
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx
MWASMARM_PATCHER = $(TOOLS_DIR)/mwasmarm_patcher/mwasmarm_patcher$(EXE) -q

TOOLDIRS = $(filter-out $(TOOLS_DIR)/mwccarm $(TOOLS_DIR)/bin,$(wildcard $(TOOLS_DIR)/*))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

export LM_LICENSE_FILE := $(TOOLS_DIR)/mwccarm/license.dat
export MWCIncludes := arm9/lib/include

######################### Targets ###########################

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all,$(MAKECMDGOALS)))
$(call infoshell, $(MAKE) tools patch_mwasmarm)
else
NODEP := 1
endif

.PHONY: all clean mostlyclean tidy tools $(TOOLDIRS) patch_mwasmarm arm9 arm7

MAKEFLAGS += --no-print-directory

all: $(ROM)
	@$(SHA1SUM) -c $(TARGET).sha1

clean: mostlyclean
	make -C arm9 clean
	make -C arm7 clean
	make -C tools/mwasmarm_patcher clean

mostlyclean: tidy
	make -C arm9 mostlyclean
	make -C arm7 mostlyclean
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' \) -exec $(RM) {} +

tidy:
	make -C arm9 tidy
	make -C arm7 tidy
	$(RM) -r $(BUILD_DIR)

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@

$(MWASMARM): patch_mwasmarm
	@:

patch_mwasmarm:
	$(MWASMARM_PATCHER) $(MWASMARM)

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) $(VERSION_CFLAGS) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(SBINFILES): arm9 arm7

arm9:
	$(MAKE) -C arm9

arm7:
	$(MAKE) -C arm7

$(BINFILES): %.bin: %.sbin
	@cp $< $@

$(ELF): $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT) $(BINFILES)
	# Hack because mwldarm doesn't like the sbin suffix
	$(LD) $(LDFLAGS) $(BUILD_DIR)/$(LD_SCRIPT) -o $(ELF) $(O_FILES) $(BINFILES)

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

%.png: ;
%.pal: ;

$(BUILD_DIR)/data/icon.o: graphics/icon.4bpp graphics/icon.gbapal

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
