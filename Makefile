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

# TODO: Replace mwldarm with gnu ld

MWLDARM := ./tools/mwccarm/$(MWCCVERSION)/mwldarm.exe
MWCCARM := ./tools/mwccarm/$(MWCCVERSION)/mwccarm.exe

AS      := $(CROSS)as
CC      := $(MWCCARM)
CPP     := cpp -P
LD      := $(MWLDARM)
AR      := $(CROSS)ar
OBJDUMP := $(CROSS)objdump
OBJCOPY := $(CROSS)objcopy

CFLAGS = -c -O4,p -proc arm946e -thumb -fp soft -lang c -Cpp_exceptions off

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

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -MD $(BUILD_DIR)/$*.d -o $@ $<

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(MWLDARM) -LC:/pokediamond/$(BUILD_DIR)/asm/ $(O_FILES) $(LD_SCRIPT) -o $@ -nodead

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
