CC := gcc
CFLAGS := -O3

all: mwasmarm_patcher

mwasmarm_patcher: mwasmarm_patcher.c
	$(CC) $(CFLAGS) -o $@ $< -lssl -lcrypto
