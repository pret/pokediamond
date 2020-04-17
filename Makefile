# Makefile to build Pokemon Diamond image

### Default target ###

default: all

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
CFLAGS = -O4,p -proc v5te -thumb -fp soft -lang c -Cpp_exceptions off -interworking

####################### Other Tools #########################

# DS TOOLS
TOOLS_DIR = tools
SHA1SUM = sha1sum

######################### Targets ###########################

all: $(ROM)
	@$(SHA1SUM) -c $(TARGET).sha1

clean:
	$(RM) -r $(BUILD_DIR)

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
	$(OBJCOPY) -O binary $< $@

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
