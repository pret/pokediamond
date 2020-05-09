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

TARGET := arm9

ROM := $(BUILD_DIR)/$(TARGET).sbin
ELF := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := $(TARGET).lcf
LD_SPEC := $(TARGET).lsf
LD_TEMPLATE := ARM9-TS.lcf.template

# Directories containing source files
SRC_DIRS := src lib lib/src $(wildcard modules/*/src)
ASM_DIRS := asm data files $(wildcard modules/*/asm)

C_FILES   := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
CXX_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
S_FILES   := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)
CXX_OBJS = $(CXX_FILES:%.cpp=$(BUILD_DIR)/%.o)
S_OBJS = $(S_FILES:%.s=$(BUILD_DIR)/%.o)

# Object files
O_FILES := $(C_OBJS) $(CXX_OBJS) $(S_OBJS)

# Overlay modules
# FIXME: lcf doesn't like this
# BIN_FILES := $(wildcard files/*.__AT_*)
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
MAKELSF_FLAGS := -DCONST_34=0x34 -DCONST_3F=0x3F

AS      = $(WINE) $(MWASMARM)
CC      = $(WINE) $(MWCCARM)
CXX     = $(WINE) $(MWCCARM)
CPP     := cpp -P
LD      = $(WINE) $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
ASFLAGS = -proc arm5te -i ..
CFLAGS = -O4,p -proc arm946e -fp soft -lang c99 -Cpp_exceptions off -ir ../include -ir ../include-mw -ir lib/include -interworking -DFS_IMPLEMENT -enum int
CXXFLAGS = -O4,p -proc arm946e -fp soft -lang c99 -Cpp_exceptions off -ir ../include -ir ../include-mw -ir lib/include -interworking -DFS_IMPLEMENT -enum int
LDFLAGS = -map -nodead -w off -proc v5te -interworking -map -symtab -m _start

####################### Other Tools #########################

# DS TOOLS
SHA1SUM = sha1sum --quiet
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc$(EXE)
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx$(EXE)
SCANINC = $(TOOLS_DIR)/scaninc/scaninc$(EXE)
MWASMARM_PATCHER = $(TOOLS_DIR)/mwasmarm_patcher/mwasmarm_patcher$(EXE) -q

TOOLDIRS = $(filter-out $(TOOLS_DIR)/mwccarm $(TOOLS_DIR)/bin,$(wildcard $(TOOLS_DIR)/*))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

######################### Targets ###########################

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all,$(MAKECMDGOALS)))
$(call infoshell, $(MAKE) tools patch_mwasmarm)
else
NODEP := 1
endif

.PHONY: all clean mostlyclean tidy tools $(TOOLDIRS) patch_mwasmarm

MAKEFLAGS += --no-print-directory

all: $(ROM)
	@$(SHA1SUM) -c $(TARGET).sha1
	@echo $(ROM): OK

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
build/lib/src/%.o: MWCCVERSION = 1.2/sp2p3
build/src/FUN_020910A4.o: MWCCVERSION = 1.2/sp2p3

####################### Everything Else ######################

ifeq (,$(NODEP))
$(BUILD_DIR)/%.o: dep = $(shell $(SCANINC) -I ../include -I ../include-mw -I lib/include $(filter $*.c,$(C_FILES)) $(filter $*.cpp,$(CXX_FILES)) $(filter $*.s,$(S_FILES)))
else
$(BUILD_DIR)/%.o: dep :=
endif

$(C_OBJS): $(BUILD_DIR)/%.o: %.c $$(dep)
	$(CC) -c $(CFLAGS) -o $@ $<

$(CXX_OBJS): $(BUILD_DIR)/%.o: %.cpp $$(dep)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(S_OBJS): $(BUILD_DIR)/%.o: %.s $$(dep)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT) $(LD_TEMPLATE) undefined_syms.txt macros.lcf.inc
	# $(MAKELSF) $(MAKELSF_FLAGS) $< $(LD_TEMPLATE) $@
	$(CPP) $(VERSION_CFLAGS) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(ROM): $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT) $(BIN_FILES)
	$(LD) $(LDFLAGS) $(BUILD_DIR)/$(LD_SCRIPT) -o $(ELF) $(O_FILES) $(BIN_FILES)


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
baserom.%: ;
%.h: ;
%.inc: ;

$(BIN_FILES): ;

$(BUILD_DIR)/data/icon.o: graphics/icon.4bpp graphics/icon.gbapal

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
