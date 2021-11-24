.PHONY: all clean

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
CC := clang
else
CC := gcc
endif
CFLAGS := -O3

.PHONY: all clean

all: mwasmarm_patcher
	@:

clean: ; $(RM) mwasmarm_patcher$(EXE)

mwasmarm_patcher: mwasmarm_patcher.c
	$(CC) $(CFLAGS) -o $@ $<
