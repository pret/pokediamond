# Makefile to build Pokemon Diamond image

include ../config.mk

.PHONY: clean tidy all default patch_mwasmarm

# Try to include devkitarm if installed
ifdef DEVKITARM
TOOLCHAIN := $(DEVKITARM)
endif

ifdef TOOLCHAIN
export PATH := $(TOOLCHAIN)/bin:$(PATH)
endif

PREFIX := arm-none-eabi-

OBJCOPY := $(PREFIX)objcopy
AR      := $(PREFIX)ar

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

BUILD_DIR := build/$(BUILD_NAME)

TARGET := arm9

ROM := $(BUILD_DIR)/$(TARGET).sbin
ELF := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := $(TARGET).lcf
LD_SPEC := $(TARGET).lsf
LD_TEMPLATE := ARM9-TS.lcf.template

# Directories containing source files

# sorting wildcards required for versions of make >= 3.8.2 and < 4.3 for consistent builds
SRC_DIRS := src lib lib/libnns/src lib/NitroSDK/src lib/libc/src $(sort $(wildcard modules/*/src))
ASM_DIRS := asm data files $(sort $(wildcard modules/*/asm))
LIBASM_DIRS := lib/syscall
INCLUDE_RECURSIVE_DIRS := ../include-mw lib/libc/include lib/libnns/include lib/NitroSDK/include
INCLUDE_DIRS := ../include $(sort $(wildcard modules/*/include)) ../files

C_FILES    := $(foreach dir,$(SRC_DIRS),$(sort $(wildcard $(dir)/*.c)))
CXX_FILES  := $(foreach dir,$(SRC_DIRS),$(sort $(wildcard $(dir)/*.cpp)))
S_FILES    := $(foreach dir,$(ASM_DIRS),$(sort $(wildcard $(dir)/*.s)))
LIBS_FILES := $(foreach dir,$(LIBASM_DIRS),$(sort $(wildcard $(dir)/*.s)))

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)
CXX_OBJS = $(CXX_FILES:%.cpp=$(BUILD_DIR)/%.o)
S_OBJS = $(S_FILES:%.s=$(BUILD_DIR)/%.o)
LIBS_OBJS = $(LIBS_FILES:%.s=$(BUILD_DIR)/%.o)

# Object files
O_FILES := $(C_OBJS) $(CXX_OBJS) $(S_OBJS)

GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(C_FILES)
GLOBAL_ASM_O_FILES = $(addprefix $(BUILD_DIR)/,$(GLOBAL_ASM_C_FILES:.c=.o))

# Overlay modules
OVERLAYS := $(shell grep -oE "Overlay \w+" $(LD_SPEC) | cut -d' ' -f2)

.SECONDARY:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

##################### Compiler Options #######################

MWCCVERSION = 2.0/sp1
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
MAKELCF := $(WINE) $(TOOLS_DIR)/bin/makelcf.exe

AS      = $(WINE) $(MWASMARM)
CC      = $(WINE) $(MWCCARM)
CXX     = $(WINE) $(MWCCARM)
CPP     := cpp -P
LD      = $(WINE) $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

ASM_PROCESSOR_DIR := ../tools/asm_processor
ASM_PROCESSOR := $(ASM_PROCESSOR_DIR)/compile.sh

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
MWASFLAGS = -proc arm5te -i ../include -i .. -D$(GAME_VERSION) -D$(GAME_LANGUAGE)
MWCFLAGS = -O4,p -gccext,on -proc arm946e -ipa file -fp soft -lang c99 -Cpp_exceptions off $(foreach dir,$(INCLUDE_DIRS),-i $(dir)) $(foreach dir,$(INCLUDE_RECURSIVE_DIRS),-ir $(dir)) -interworking -DFS_IMPLEMENT -enum int -W all -D$(GAME_VERSION) -D$(GAME_LANGUAGE)
MWCXXFLAGS = -O4,p -proc arm946e -fp soft -lang c99 -Cpp_exceptions off $(foreach dir,$(INCLUDE_DIRS),-i $(dir)) $(foreach dir,$(INCLUDE_RECURSIVE_DIRS),-ir $(dir)) -interworking -DFS_IMPLEMENT -enum int -W all -D$(GAME_VERSION) -D$(GAME_LANGUAGE)
MWLDFLAGS = -w off -proc v5te -interworking -map closure,unused -symtab sort -m _start
LIBS := -Llib -lsyscall
ARFLAGS = rcS
STATIC_LIBS := $(addprefix $(BUILD_DIR)/lib/,libsyscall.a)

####################### Other Tools #########################

# DS TOOLS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
SHA1SUM = shasum
else
ifndef BUSYBOX
SHA1SUM = sha1sum --quiet
else
SHA1SUM = sha1sum
endif
endif
JSONPROC = $(TOOLS_DIR)/jsonproc/jsonproc$(EXE)
GFX = $(TOOLS_DIR)/nitrogfx/nitrogfx$(EXE)
SCANINC = $(TOOLS_DIR)/scaninc/scaninc$(EXE)
MWASMARM_PATCHER = $(TOOLS_DIR)/mwasmarm_patcher/mwasmarm_patcher$(EXE) -q

TOOLDIRS = $(dir $(wildcard $(TOOLS_DIR)/*/Makefile))
TOOLBASE = $(TOOLDIRS:$(TOOLS_DIR)/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),$(TOOLS_DIR)/$(tool)/$(tool)$(EXE))

TOOLS: tools

export LM_LICENSE_FILE := $(TOOLS_DIR)/mwccarm/license.dat
export MWCIncludes := $(CURDIR)/lib/libc/include $(CURDIR)/lib/NitroSDK/include $(CURDIR)/lib/libnns/include
export MWLibraries := $(CURDIR)/lib

######################### Targets ###########################
######################## Targets ###########################

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all,$(MAKECMDGOALS)))
$(call infoshell,$(MAKE) tools patch_mwasmarm)
else
NODEP := 1
endif

.PRECIOUS: $(ROM)
.PHONY: all clean mostlyclean tidy tools $(TOOLDIRS) patch_mwasmarm

MAKEFLAGS += --no-print-directory

all: tools patch_mwasmarm

all: $(ROM)
ifeq ($(COMPARE),1)
	@$(SHA1SUM) -c $(BUILD_TARGET).sha1
	@echo $(ROM): OK
endif

clean: mostlyclean
	$(MAKE) -C $(TOOLS_DIR)/mwasmarm_patcher clean

mostlyclean: tidy
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' \) -exec $(RM) {} +

tidy:
	$(RM) -r $(BUILD_DIR)
	$(MAKE) clean -C lib

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@

$(MWASMARM): patch_mwasmarm

patch_mwasmarm:
	$(MWASMARM_PATCHER) $(MWASMARM)

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS) $(LIBASM_DIRS))

######################## Special Rules ########################

# TODO: Move out to lib/Makefile
$(BUILD_DIR)/lib/%.o: MWCCVERSION = 1.2/sp2p3
$(BUILD_DIR)/lib/%.o: MWCFLAGS = -O4,p -gccext,on -proc arm946e -fp soft -lang c99 -Cpp_exceptions off -interworking -DFS_IMPLEMENT -enum int -W all -i ../include -ir ../include-mw -ir lib/libc/include -ir lib/libnns/include -ir lib/NitroSDK/include

$(BUILD_DIR)/lib/libnns/%.o: MWCCVERSION = 1.2/sp3

####################### Everything Else ######################

ifeq (,$(NODEP))
$(BUILD_DIR)/%.o: dep = $(shell $(SCANINC) -I ../include -I ../include-mw -I lib/libc/include -I lib/libnns/include -I lib/NitroSDK/include $(filter $*.c,$(C_FILES)) $(filter $*.cpp,$(CXX_FILES)) $(filter $*.s,$(S_FILES)) $(filter $*.s,$(LIBS_FILES)))
else
$(BUILD_DIR)/%.o: dep :=
endif

# Cpp asm processor is not supported at this time.
$(GLOBAL_ASM_O_FILES): BUILD_C := $(ASM_PROCESSOR) "$(CC) $(MWCFLAGS)" "$(AS) $(MWASFLAGS)"
BUILD_C ?= $(CC) -c $(MWCFLAGS) -o

$(C_OBJS): $(BUILD_DIR)/%.o: %.c $$(dep)
	$(BUILD_C) $@ $<

$(CXX_OBJS): $(BUILD_DIR)/%.o: %.cpp $$(dep)
	$(CXX) -c $(MWCXXFLAGS) -o $@ $<

$(S_OBJS) $(LIBS_OBJS): $(BUILD_DIR)/%.o: %.s $$(dep)
	$(AS) $(MWASFLAGS) -o $@ $<

# Bugfix note: zsh doesn't like escapes
$(BUILD_DIR)/$(LD_TEMPLATE): $(BUILD_DIR)/%: %
	(printf "KEEP_SECTION\n{\n\t.exceptix\n}\n"; cat $<) > $@

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SPEC) $(BUILD_DIR)/$(LD_TEMPLATE)
	$(MAKELCF) $(MAKELCF_FLAGS) $^ $@

$(ROM): $(BUILD_DIR)/$(LD_SCRIPT) $(O_FILES) $(STATIC_LIBS)
	echo "$(O_FILES:$(BUILD_DIR)/%=%)" > $(ELF).objlist
	cd $(BUILD_DIR) && LM_LICENSE_FILE=../../$(LM_LICENSE_FILE) $(WINE) ../../$(MWLDARM) $(MWLDFLAGS) $(LIBS) -o ../../$(ELF) $(LD_SCRIPT) @../../$(ELF).objlist
	$(OBJCOPY) $(foreach ov,arm9 $(OVERLAYS),--update-section $(ov)=$(BUILD_DIR)/$(ov).sbin -j $(ov)) $(ELF) 2>/dev/null

ifeq ($(SHIFTED),0)
SYSCALL_OBJS := $(BUILD_DIR)/lib/syscall/secure.o
else
SYSCALL_OBJS := $(BUILD_DIR)/lib/syscall/_svc_mw.o
endif
$(BUILD_DIR)/lib/libsyscall.a: $(SYSCALL_OBJS)
	$(AR) $(ARFLAGS) -o $@ $^

# Make sure build directory exists before compiling anything
DUMMY := $(shell mkdir -p $(ALL_DIRS))

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

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
