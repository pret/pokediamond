# Makefile to build Pokemon Diamond image

include config.mk

HOSTCC = $(CC)
HOSTCXX = $(CXX)
HOSTCFLAGS = $(CFLAGS)
HOSTCXXFLAGS = $(CXXFLAGS)
HOST_VARS := CC=$(HOSTCC) CXX=$(HOSTCXX) CFLAGS='$(HOSTCFLAGS)' CXXFLAGS='$(HOSTCXXFLAGS)'

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
GREP := grep -P
SED := sed -r
else
EXE :=
WINE := wine
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
GREP := grep -E
SED := perl -p -e
else
GREP := grep -P
SED := sed -r
endif
endif

ifeq ($(NOWINE),1)
WINE :=
endif

################ Target Executable and Sources ###############

BUILD_DIR := build/$(BUILD_NAME)

TARGET := $(BUILD_TARGET)

ROM := $(BUILD_DIR)/$(TARGET).nds
ELF := $(BUILD_DIR)/$(TARGET).elf
BNR := $(BUILD_DIR)/$(TARGET).bnr

# Directories containing source files
SRC_DIRS := src
ASM_DIRS := asm data files

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \

ARM9SBIN := arm9/$(BUILD_DIR)/arm9.sbin
ARM7SBIN := arm7/build/arm7.sbin

SBINFILES = \
	$(ARM9SBIN) \
	$(ARM9SBIN:%.sbin=%_table.sbin) \
	$(ARM9SBIN:%.sbin=%_defs.sbin) \
	$(ARM7SBIN) \
	arm9/$(BUILD_DIR)/MODULE_00.sbin \
	arm9/$(BUILD_DIR)/MODULE_01.sbin \
	arm9/$(BUILD_DIR)/MODULE_02.sbin \
	arm9/$(BUILD_DIR)/MODULE_03.sbin \
	arm9/$(BUILD_DIR)/MODULE_04.sbin \
	arm9/$(BUILD_DIR)/MODULE_05.sbin \
	arm9/$(BUILD_DIR)/MODULE_06.sbin \
	arm9/$(BUILD_DIR)/MODULE_07.sbin \
	arm9/$(BUILD_DIR)/MODULE_08.sbin \
	arm9/$(BUILD_DIR)/MODULE_09.sbin \
	arm9/$(BUILD_DIR)/MODULE_10.sbin \
	arm9/$(BUILD_DIR)/MODULE_11.sbin \
	arm9/$(BUILD_DIR)/MODULE_12.sbin \
	arm9/$(BUILD_DIR)/MODULE_13.sbin \
	arm9/$(BUILD_DIR)/MODULE_14.sbin \
	arm9/$(BUILD_DIR)/MODULE_15.sbin \
	arm9/$(BUILD_DIR)/MODULE_16.sbin \
	arm9/$(BUILD_DIR)/MODULE_17.sbin \
	arm9/$(BUILD_DIR)/MODULE_18.sbin \
	arm9/$(BUILD_DIR)/MODULE_19.sbin \
	arm9/$(BUILD_DIR)/MODULE_20.sbin \
	arm9/$(BUILD_DIR)/MODULE_21.sbin \
	arm9/$(BUILD_DIR)/MODULE_22.sbin \
	arm9/$(BUILD_DIR)/MODULE_23.sbin \
	arm9/$(BUILD_DIR)/MODULE_24.sbin \
	arm9/$(BUILD_DIR)/MODULE_25.sbin \
	arm9/$(BUILD_DIR)/MODULE_26.sbin \
	arm9/$(BUILD_DIR)/MODULE_27.sbin \
	arm9/$(BUILD_DIR)/MODULE_28.sbin \
	arm9/$(BUILD_DIR)/MODULE_29.sbin \
	arm9/$(BUILD_DIR)/MODULE_30.sbin \
	arm9/$(BUILD_DIR)/MODULE_31.sbin \
	arm9/$(BUILD_DIR)/MODULE_32.sbin \
	arm9/$(BUILD_DIR)/MODULE_33.sbin \
	arm9/$(BUILD_DIR)/MODULE_34.sbin \
	arm9/$(BUILD_DIR)/MODULE_35.sbin \
	arm9/$(BUILD_DIR)/MODULE_36.sbin \
	arm9/$(BUILD_DIR)/MODULE_37.sbin \
	arm9/$(BUILD_DIR)/MODULE_38.sbin \
	arm9/$(BUILD_DIR)/MODULE_39.sbin \
	arm9/$(BUILD_DIR)/MODULE_40.sbin \
	arm9/$(BUILD_DIR)/MODULE_41.sbin \
	arm9/$(BUILD_DIR)/MODULE_42.sbin \
	arm9/$(BUILD_DIR)/MODULE_43.sbin \
	arm9/$(BUILD_DIR)/MODULE_44.sbin \
	arm9/$(BUILD_DIR)/MODULE_45.sbin \
	arm9/$(BUILD_DIR)/MODULE_46.sbin \
	arm9/$(BUILD_DIR)/MODULE_47.sbin \
	arm9/$(BUILD_DIR)/MODULE_48.sbin \
	arm9/$(BUILD_DIR)/MODULE_49.sbin \
	arm9/$(BUILD_DIR)/MODULE_50.sbin \
	arm9/$(BUILD_DIR)/MODULE_51.sbin \
	arm9/$(BUILD_DIR)/MODULE_52.sbin \
	arm9/$(BUILD_DIR)/MODULE_53.sbin \
	arm9/$(BUILD_DIR)/MODULE_54.sbin \
	arm9/$(BUILD_DIR)/MODULE_55.sbin \
	arm9/$(BUILD_DIR)/MODULE_56.sbin \
	arm9/$(BUILD_DIR)/MODULE_57.sbin \
	arm9/$(BUILD_DIR)/MODULE_58.sbin \
	arm9/$(BUILD_DIR)/MODULE_59.sbin \
	arm9/$(BUILD_DIR)/MODULE_60.sbin \
	arm9/$(BUILD_DIR)/MODULE_61.sbin \
	arm9/$(BUILD_DIR)/MODULE_62.sbin \
	arm9/$(BUILD_DIR)/MODULE_63.sbin \
	arm9/$(BUILD_DIR)/MODULE_64.sbin \
	arm9/$(BUILD_DIR)/MODULE_65.sbin \
	arm9/$(BUILD_DIR)/MODULE_66.sbin \
	arm9/$(BUILD_DIR)/MODULE_67.sbin \
	arm9/$(BUILD_DIR)/MODULE_68.sbin \
	arm9/$(BUILD_DIR)/MODULE_69.sbin \
	arm9/$(BUILD_DIR)/MODULE_70.sbin \
	arm9/$(BUILD_DIR)/MODULE_71.sbin \
	arm9/$(BUILD_DIR)/MODULE_72.sbin \
	arm9/$(BUILD_DIR)/MODULE_73.sbin \
	arm9/$(BUILD_DIR)/MODULE_74.sbin \
	arm9/$(BUILD_DIR)/MODULE_75.sbin \
	arm9/$(BUILD_DIR)/MODULE_76.sbin \
	arm9/$(BUILD_DIR)/MODULE_77.sbin \
	arm9/$(BUILD_DIR)/MODULE_78.sbin \
	arm9/$(BUILD_DIR)/MODULE_79.sbin \
	arm9/$(BUILD_DIR)/MODULE_80.sbin \
	arm9/$(BUILD_DIR)/MODULE_81.sbin \
	arm9/$(BUILD_DIR)/MODULE_82.sbin \
	arm9/$(BUILD_DIR)/MODULE_83.sbin \
	arm9/$(BUILD_DIR)/MODULE_84.sbin \
	arm9/$(BUILD_DIR)/MODULE_85.sbin \
	arm9/$(BUILD_DIR)/MODULE_86.sbin

##################### Compiler Options #######################

MWCCVERSION = 2.0/sp1

CROSS   := arm-none-eabi-

MWCCARM  = tools/mwccarm/$(MWCCVERSION)/mwccarm.exe
# Argh... due to EABI version shenanigans, we can't use GNU LD to link together
# MWCC built objects and GNU built ones. mwldarm, however, doesn't care, so we
# have to use mwldarm for now.
# TODO: Is there a hack workaround to let us go back to GNU LD? Ideally, the
# only dependency should be MWCCARM.
KNARC = tools/knarc/knarc$(EXE)
MWLDARM  = tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM = tools/mwccarm/$(MWCCVERSION)/mwasmarm.exe
NARCCOMP = tools/narccomp/narccomp$(EXE)
SCANINC = tools/scaninc/scaninc$(EXE)

AS      = $(WINE) $(MWASMARM)
CC      = $(WINE) $(MWCCARM)
CPP     := cpp -P
LD      = $(WINE) $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
ASFLAGS = -proc arm5te
CFLAGS = -O4,p -gccext,on -proc arm946e -fp soft -lang c99 -Cpp_exceptions off -i include -ir include-mw -ir arm9/lib/include -W all
LDFLAGS = -map -nodead -w off -proc v5te -interworking -map -symtab -m _start

####################### Other Tools #########################

# DS TOOLS
TOOLS_DIR = tools
SHA1SUM = sha1sum
CSV2BIN = $(TOOLS_DIR)/csv2bin/csv2bin$(EXE)
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc$(EXE)
O2NARC = $(TOOLS_DIR)/o2narc/o2narc$(EXE)
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx$(EXE)
MWASMARM_PATCHER = $(TOOLS_DIR)/mwasmarm_patcher/mwasmarm_patcher$(EXE) -q
MAKEBANNER = $(WINE) $(TOOLS_DIR)/bin/makebanner.exe
MAKEROM    = $(WINE) $(TOOLS_DIR)/bin/makerom.exe
FIXROM     = $(TOOLS_DIR)/fixrom/fixrom$(EXE)

TOOLDIRS = $(filter-out $(TOOLS_DIR)/mwccarm $(TOOLS_DIR)/bin,$(wildcard $(TOOLS_DIR)/*))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

export LM_LICENSE_FILE := $(TOOLS_DIR)/mwccarm/license.dat
export MWCIncludes := arm9/lib/include
export MWLibraries := arm9/lib

######################### Targets ###########################

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all,$(MAKECMDGOALS)))
$(call infoshell, $(HOST_VARS) $(MAKE) tools patch_mwasmarm)
else
NODEP := 1
endif

.SECONDARY:
.DELETE_ON_ERROR:
.SECONDEXPANSION:
.PHONY: all libs clean mostlyclean tidy tools $(TOOLDIRS) patch_mwasmarm arm9 arm7

MAKEFLAGS += --no-print-directory

all: $(ROM)
ifeq ($(COMPARE),1)
	@$(SHA1SUM) -c $(TARGET).sha1
endif

clean: mostlyclean
	$(MAKE) -C arm9 clean
	$(MAKE) -C arm7 clean
	$(MAKE) -C tools/mwasmarm_patcher clean
	$(RM) $(filter-out files/poketool/personal/pms.narc,$(filter %.narc %.arc,$(HOSTFS_FILES)))

mostlyclean: tidy
	$(MAKE) -C arm9 mostlyclean
	$(MAKE) -C arm7 mostlyclean
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' \) -exec $(RM) {} +
	find files \( -name '*.c' -o -name '*.o' \) -exec $(RM) {} +

tidy:
	$(MAKE) -C arm9 tidy
	$(MAKE) -C arm7 tidy
	$(RM) -r $(BUILD_DIR)

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(HOST_VARS) $(MAKE) -C $@

$(MWASMARM): patch_mwasmarm
	@:

patch_mwasmarm:
	$(MWASMARM_PATCHER) $(MWASMARM)

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

ifeq (,$(NODEP))
$(BUILD_DIR)/%.o: dep = $(shell $(SCANINC) -I include -I include-mw -I arm9/lib/include $(filter $*.c,$(C_FILES)) $(filter $*.cpp,$(CXX_FILES)) $(filter $*.s,$(S_FILES)))
else
$(BUILD_DIR)/%.o: dep :=
endif

$(BUILD_DIR)/%.o: %.c $$(dep)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.s $$(dep)
	$(AS) $(ASFLAGS) $< -o $@

$(SBINFILES): arm9 arm7

arm9:
	$(MAKE) -C arm9 COMPARE=$(COMPARE) GAME_LANGUAGE=$(GAME_LANGUAGE) GAME_VERSION=$(GAME_VERSION)

arm7:
	$(MAKE) -C arm7 COMPARE=$(COMPARE) GAME_LANGUAGE=$(GAME_LANGUAGE) GAME_VERSION=$(GAME_VERSION)

include filesystem.mk

# TODO: Rules for Pearl
# FIXME: Computed secure area CRC in header is incorrect due to first 8 bytes of header not actually being "encryObj"
$(ROM): rom.rsf $(BNR) $(SBINFILES) $(HOSTFS_FILES) tools/bin/rom_header.template.sbin
	$(MAKEROM) -DBUILD_DIR="$(BUILD_DIR)" -DBNR="$(BNR)" -DTITLE_NAME="$(TITLE_NAME)" -DNITROFS_FILES="$(NITROFS_FILES)" $< $@
	$(FIXROM) $@ --secure-crc $(SECURE_CRC) --game-code $(GAME_CODE)

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

######################## Misc #######################

$(BNR): $(TARGET).bsf $(ICON_FILE:%.png=%.gbapal) $(ICON_FILE:%.png=%.4bpp)
	$(MAKEBANNER) $< $@

symbols.csv: arm9 arm7
	(echo "Name,Location"; $(GREP) " *[0-9A-F]{8} [0-9A-F]{8} \S+ +\w+\t\(\w+\.o\)" arm9/$(BUILD_DIR)/arm9.elf.xMAP arm7/$(BUILD_DIR)/arm7.elf.xMAP | $(SED) 's/ *([0-9A-F]{8}) [0-9A-F]{8} \S+ +(\w+)\t\(\w+\.o\)/\2,\1/g' | cut -d: -f2) > $@

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

### Other targets

diamond:          ; @$(MAKE) $(HOST_VARS) GAME_VERSION=DIAMOND
pearl:            ; @$(MAKE) $(HOST_VARS) GAME_VERSION=PEARL
compare_diamond:  ; @$(MAKE) $(HOST_VARS) GAME_VERSION=DIAMOND COMPARE=1
compare_pearl:    ; @$(MAKE) $(HOST_VARS) GAME_VERSION=PEARL COMPARE=1
