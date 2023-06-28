# Try to include devkitarm if installed
TOOLCHAIN := $(DEVKITARM)

ifneq (,$(wildcard $(TOOLCHAIN)/base_tools))
include $(TOOLCHAIN)/base_tools
endif

# If you are using WSL, it is recommended you build with NOWINE=1.
WSLENV ?= no
ifeq ($(WSLENV),no)
NOWINE = 0
else
NOWINE = 1
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

# Compare result of arm9, arm7, and ROM to sha1 hash(s)
COMPARE ?= 1

##################### Compiler Options #######################

MWCCVERSION = 1.2/sp2p3

CROSS   := arm-none-eabi-

MWCCARM  = ../../../tools/mwccarm/$(MWCCVERSION)/mwccarm.exe
# Argh... due to EABI version shenanigans, we can't use GNU LD to link together
# MWCC built objects and GNU built ones. mwldarm, however, doesn't care, so we
# have to use mwldarm for now.
# TODO: Is there a hack workaround to let us go back to GNU LD? Ideally, the
# only dependency should be MWCCARM.
MWLDARM  = ../../../tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWASMARM = ../../../tools/mwccarm/$(MWCCVERSION)/mwasmarm.exe
SCANINC = ../../../tools/scaninc/scaninc$(EXE)

AS      = $(WINE) $(MWASMARM)
CC      = $(WINE) $(MWCCARM)
CPP     := cpp -P
LD      = $(WINE) $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

# ./tools/mwccarm/2.0/base/mwasmarm.exe -proc arm5te asm/arm9_thumb.s -o arm9.o
MWASFLAGS = -proc arm5te -ir ../../..
MWCFLAGS = -O4,p -gccext,on -proc arm946e -msgstyle gcc -gccinc -fp soft -lang c99 -Cpp_exceptions off -i ../include -ir ../include-mw -ir lib/libc/include -ir lib/libnns/include -ir lib/NitroSDK/include -interworking -DFS_IMPLEMENT -enum int -D$(GAME_VERSION) -D$(GAME_LANGUAGE) -W all -W pedantic -W noimpl_signedunsigned -W noimplicitconv -W nounusedarg -W nomissingreturn -W error
MWLDFLAGS = -library -nodead -w off -proc v5te -interworking -pic -msgstyle gcc
ARFLAGS = rcS

export MWCIncludes := include

################ Targets #################

.PHONY: all clean

all:
	@:

clean:
	$(RM) $(%.a=%/*.o)

%.a:
	$(AR) $(ARFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(MWCFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(MWASFLAGS) -o $@ $<
