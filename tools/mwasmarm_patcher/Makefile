.PHONY: all clean

CC := gcc
CFLAGS := -O3

all: mwasmarm_patcher

clean: ; rm -f mwasmarm_patcher$(EXE)

mwasmarm_patcher: mwasmarm_patcher.c
	$(CC) $(CFLAGS) -o $@ $<
