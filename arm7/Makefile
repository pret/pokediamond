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

TARGET := arm7

ROM := $(BUILD_DIR)/$(TARGET).sbin
ELF := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := $(TARGET).lcf
LD_SPEC := $(TARGET).lsf
LD_TEMPLATE := ARM7-TS.lcf.template

# Directories containing source files
SRC_DIRS := src lib lib/src
ASM_DIRS := asm data files

# sorting wildcards required for versions of make >= 3.8.2 and < 4.3 for consistent builds
C_FILES := $(foreach dir,$(SRC_DIRS),$(sort $(wildcard $(dir)/*.c)))
S_FILES := $(foreach dir,$(ASM_DIRS),$(sort $(wildcard $(dir)/*.s)))

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)
S_OBJS = $(S_FILES:%.s=$(BUILD_DIR)/%.o)

# Object files
O_FILES := $(C_OBJS) $(S_OBJS)

.SECONDARY:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

##################### Compiler Options #######################

MWCCVERSION = 2.0/base
TOOLS_DIR = ../tools

CROSS   := arm-none-eabi-

MWCCARM  = $(TOOLS_DIR)/mwccarm/$(MWCCVERSION)/mwccarm.exe
# Argh... due to EABI version shenanigans, we can't use GNU LD to link together
# MWCC built objects and GNU built ones. mwldarm, however, doesn't care, so we
# have to use mwldarm for now.
# TODO: Is there a hack workaround to let us go back to GNU LD? Ideally, the
# only dependency should be MWCCARM.
MWLDARM  = $(TOOLS_DIR)/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM = $(TOOLS_DIR)/mwccarm/$(MWCCVERSION)/mwasmarm.exe
MAKELSF := $(WINE) $(TOOLS_DIR)/bin/makelcf.exe

AS      = $(WINE) $(MWASMARM)
CC      = $(WINE) $(MWCCARM)
CPP     := cpp -P
LD      = $(WINE) $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm7_thumb.s -o arm7.o
ASFLAGS = -proc arm4t -i  ..
CFLAGS = -O4,s -proc arm7tdmi -fp soft -lang c99 -Cpp_exceptions off -i ../include -ir ../include-mw -ir lib/include -interworking -DFS_IMPLEMENT -enum int -W all
LDFLAGS = -map -nodead -w off -proc v4t -interworking -map -symtab -m _start

####################### Other Tools #########################

# DS TOOLS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
SHA1SUM = shasum
else
SHA1SUM = sha1sum
endif
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx
SCANINC = $(TOOLS_DIR)/scaninc/scaninc$(EXE)
MWASMARM_PATCHER = $(TOOLS_DIR)/mwasmarm_patcher/mwasmarm_patcher$(EXE) -q

TOOLDIRS = $(filter-out $(TOOLS_DIR)/asm_processor $(TOOLS_DIR)/mwccarm $(TOOLS_DIR)/bin,$(wildcard $(TOOLS_DIR)/*))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

export LM_LICENSE_FILE := $(TOOLS_DIR)/mwccarm/license.dat
export MWCIncludes := lib/include

######################### Targets ###########################

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all,$(MAKECMDGOALS)))
$(call infoshell, $(MAKE) tools patch_mwasmarm)
else
NODEP := 1
endif

.PRECIOUS: $(ROM)
.PHONY: all clean mostlyclean tidy tools $(TOOLDIRS) patch_mwasmarm

MAKEFLAGS += --no-print-directory

all: $(ROM)
ifeq ($(COMPARE),1)
	@$(SHA1SUM) -c $(TARGET).sha1
endif

clean: mostlyclean
	make -C $(TOOLS_DIR)/mwasmarm_patcher clean

mostlyclean: tidy
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' \) -exec $(RM) {} +

tidy:
	$(RM) -r $(BUILD_DIR)

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@

$(MWASMARM): patch_mwasmarm

patch_mwasmarm:
	$(MWASMARM_PATCHER) $(MWASMARM)

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

######################## Special Rules ########################

# TODO: Move out to lib/Makefile
$(BUILD_DIR)/lib/src/%.o: MWCCVERSION = 1.2/sp2p3

####################### Everything Else ######################

ifeq (,$(NODEP))
$(BUILD_DIR)/%.o: dep = $(shell $(SCANINC) -I ../include -I ../include-mw -I lib/include $(filter $*.c,$(C_FILES)) $(filter $*.s,$(S_FILES)))
else
$(BUILD_DIR)/%.o: dep :=
endif

$(C_OBJS): $(BUILD_DIR)/%.o: %.c $$(dep)
	$(CC) -c $(CFLAGS) -o $@ $<

$(S_OBJS): $(BUILD_DIR)/%.o: %.s $$(dep)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SPEC) $(LD_TEMPLATE)
	$(MAKELSF) $< $(LD_TEMPLATE) $@

$(ROM): $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT) $(BIN_FILES)
	$(LD) $(LDFLAGS) $(BUILD_DIR)/$(LD_SCRIPT) -o $(ELF) $(O_FILES) $(BIN_FILES)
	$(OBJCOPY) --update-section arm7=$@ -j arm7 $(foreach ov,$(OVERLAYS),--update-section $(ov)=$(BUILD_DIR)/$(ov).sbin -j $(ov)) $(ELF) 2>/dev/null

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

# Included files
%.h: ;
%.inc: ;

$(BIN_FILES): ;

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
