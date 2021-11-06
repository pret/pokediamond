# Makefile to build Pokemon Diamond image

include config.mk
include graphics_rules.mk

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

# sorting wildcards required for versions of make >= 3.8.2 and < 4.3 for consistent builds
C_FILES := $(foreach dir,$(SRC_DIRS),$(sort $(wildcard $(dir)/*.c)))
S_FILES := $(foreach dir,$(ASM_DIRS),$(sort $(wildcard $(dir)/*.s)))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \

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
MSGENC = tools/msgenc/msgenc$(EXE)
MWLDARM  = tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM = tools/mwccarm/$(MWCCVERSION)/mwasmarm.exe
NITROBANNER = tools/nitrobanner/nitrobanner$(EXE)
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
CFLAGS = -O4,p -gccext,on -proc arm946e -fp soft -lang c99 -Cpp_exceptions off -i include -ir include-mw -ir arm9/lib/libc/include -ir arm9/lib/libnns/include -ir arm9/lib/NitroSDK/include -W all
LDFLAGS = -map -nodead -w off -proc v5te -interworking -map -symtab -m _start

####################### Other Tools #########################

# DS TOOLS
TOOLS_DIR = tools
ifeq ($(UNAME_S),Darwin)
SHA1SUM = shasum
else
SHA1SUM = sha1sum
endif
CSV2BIN = $(TOOLS_DIR)/csv2bin/csv2bin$(EXE)
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc$(EXE)
O2NARC = $(TOOLS_DIR)/o2narc/o2narc$(EXE)
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx$(EXE)
MWASMARM_PATCHER = $(TOOLS_DIR)/mwasmarm_patcher/mwasmarm_patcher$(EXE) -q
MAKEROM    = $(WINE) $(TOOLS_DIR)/bin/makerom.exe
FIXROM     = $(TOOLS_DIR)/fixrom/fixrom$(EXE)
NTRCOMP    = $(WINE) $(TOOLS_DIR)/bin/ntrcomp.exe

TOOLDIRS = $(filter-out $(TOOLS_DIR)/asm_processor $(TOOLS_DIR)/mwccarm $(TOOLS_DIR)/bin,$(wildcard $(TOOLS_DIR)/*))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

export LM_LICENSE_FILE := $(TOOLS_DIR)/mwccarm/license.dat
export MWCIncludes := arm9/lib/libc/include arm9/lib/NitroSDK/include arm9/lib/libnns/include
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
.PHONY: all libs clean mostlyclean tidy tools clean-tools $(TOOLDIRS) patch_mwasmarm arm9 arm7

MAKEFLAGS += --no-print-directory

all: $(ROM)
ifeq ($(COMPARE),1)
	@$(SHA1SUM) -c $(TARGET).sha1
endif

clean: mostlyclean clean-fs clean-tools
	$(MAKE) -C arm9 clean
	$(MAKE) -C arm7 clean

clean-fs:
	$(RM) $(filter %.narc %.arc,$(HOSTFS_FILES))
	$(RM) $(patsubst %.narc,%.naix,$(patsubst %.arc,%.naix,$(filter %.narc %.arc,$(HOSTFS_FILES))))
	$(RM) $(NCGR_CLEAN_LIST) $(NCLR_CLEAN_LIST) $(NCER_CLEAN_LIST) $(NSCR_CLEAN_LIST)
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' \) -exec $(RM) {} +
	$(RM) files/msgdata/msg/narc_*.bin

mostlyclean: tidy
	$(MAKE) -C arm9 mostlyclean
	$(MAKE) -C arm7 mostlyclean
	find files \( -name '*.c' -o -name '*.o' \) -exec $(RM) {} +

tidy:
	$(MAKE) -C arm9 tidy
	$(MAKE) -C arm7 tidy
	$(RM) -r $(BUILD_DIR)

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(HOST_VARS) $(MAKE) -C $@

clean-tools:
	$(foreach tool,$(TOOLDIRS),$(MAKE) clean -C $(tool);)

$(MWASMARM): patch_mwasmarm
	@:

patch_mwasmarm: tools/mwasmarm_patcher
	$(MWASMARM_PATCHER) $(MWASMARM)

ALL_DIRS := $(BUILD_DIR)

ifeq (,$(NODEP))
$(BUILD_DIR)/%.o: dep = $(shell $(SCANINC) -I include -I include-mw -I arm9/lib/libc/include -I arm9/lib/libnns/include -I arm9/lib/NitroSDK/include $(filter $*.c,$(C_FILES)) $(filter $*.cpp,$(CXX_FILES)) $(filter $*.s,$(S_FILES)))
else
$(BUILD_DIR)/%.o: dep :=
endif

$(BUILD_DIR)/%.o: %.c $$(dep)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.s $$(dep)
	$(AS) $(ASFLAGS) $< -o $@

arm9: filesystem
	$(MAKE) -C arm9 $(MAKE_VARS)

arm7:
	$(MAKE) -C arm7 $(MAKE_VARS)

include filesystem.mk

# TODO: Rules for Pearl
# FIXME: Computed secure area CRC in header is incorrect due to first 8 bytes of header not actually being "encryObj"
$(ROM): rom.rsf arm9 arm7 $(BNR) tools/bin/rom_header.template.sbin
	$(MAKEROM) -DBUILD_DIR="$(BUILD_DIR)" -DBNR="$(BNR)" -DTITLE_NAME="$(TITLE_NAME)" -DNITROFS_FILES="$(NITROFS_FILES)" $< $@
ifeq ($(SHIFTED),0)
	$(FIXROM) $@ --secure-crc $(SECURE_CRC) --game-code $(GAME_CODE)
else
	$(FIXROM) $@ --game-code $(GAME_CODE)
endif

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

%.4bpp: %.png
	$(GFX) $< $@

%.gbapal: %.png
	$(GFX) $< $@

%.gbapal: %.pal
	$(GFX) $< $@

PADDED_LZ_FILES := $(addsuffix .lz,$(wildcard \
	files/battle/graphic/batt_bg/* \
	files/battle/graphic/batt_obj/* \
	files/wazaeffect/effectclact/wecell/* \
	files/wazaeffect/effectclact/wecellanm/* \
	files/wazaeffect/effectclact/wechar/* \
	files/contest/graphic/contest_bg/* \
	files/contest/graphic/contest_obj/* \
	files/application/custom_ball/data/cb_data/* \
	files/demo/egg/data/egg_data/*))

%.lz: %
	$(NTRCOMP) -l2 -s -o $@ $<

$(PADDED_LZ_FILES): %.lz: %
	$(NTRCOMP) -l2 -s -A4 -o $@ $<

$(CLOBBER_SIZE_NCGR_FILES): GFX_FLAGS = -clobbersize
$(CLOBBER_SIZE_VERSION101_NCGR_FILES): GFX_FLAGS = -clobbersize -version101
$(VERSION101_SOPC_8BPP_NCGR_FILES): GFX_FLAGS = -version101 -sopc -bitdepth 8
$(VERSION101_SOPC_NCGR_FILES): GFX_FLAGS = -version101 -sopc
$(SCANNED_NCGR_FILES): GFX_FLAGS = -scanned

$(IR_NCLR_FILES): GFX_FLAGS = -ir
$(4BPP_NCLR_FILES): GFX_FLAGS = -bitdepth 4
$(8BPP_NSCR_FILES): GFX_FLAGS = -bitdepth 8
$(8BPP_COMP10_NOPAD_NCLR_PNG_FILES): GFX_FLAGS = -bitdepth 8 -nopad -comp 10
$(8BPP_COMP10_NOPAD_NCLR_PAL_FILES): GFX_FLAGS = -bitdepth 8 -nopad -comp 10

%.NCGR: %.png
	$(GFX) $< $@ $(GFX_FLAGS)

%.NCLR: %.png
	$(GFX) $< $@ $(GFX_FLAGS)

%.NCLR: %.pal
	$(GFX) $< $@ $(GFX_FLAGS)

%.NCER: %.json
	$(GFX) $< $@

%.NSCR: %_map.json
	$(GFX) $< $@ $(GFX_FLAGS)

%.png: ;
%.pal: ;
%.json: ;

######################## Misc #######################

$(BNR): $(TARGET).bsf $(ICON_FILE:%.png=%.gbapal) $(ICON_FILE:%.png=%.4bpp)
	$(NITROBANNER) $< $@

symbols.csv: arm9 arm7
	(echo "Name,Location"; $(GREP) " *[0-9A-F]{8} [0-9A-F]{8} \S+ +\w+\t\(\w+\.o\)" arm9/$(BUILD_DIR)/arm9.elf.xMAP arm7/build/arm7.elf.xMAP | $(SED) 's/ *([0-9A-F]{8}) [0-9A-F]{8} \S+ +(\w+)\t\(\w+\.o\)/\2,\1/g' | cut -d: -f2) > $@

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

### Other targets

diamond:          ; @$(HOST_VARS) $(MAKE) GAME_VERSION=DIAMOND
pearl:            ; @$(HOST_VARS) $(MAKE) GAME_VERSION=PEARL
compare_diamond:  ; @$(HOST_VARS) $(MAKE) GAME_VERSION=DIAMOND COMPARE=1
compare_pearl:    ; @$(HOST_VARS) $(MAKE) GAME_VERSION=PEARL COMPARE=1
compare: compare_diamond
