CC = gcc
CFLAGS = -O3

.PHONY: all clean

all: csv2bin $(growth_rates_bin)
	@:

clean:
	$(RM) csv2bin

csv2bin: csv2bin.c
	$(CC) $(CFLAGS) -o $@ $^
