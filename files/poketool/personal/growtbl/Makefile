CC = gcc
CFLAGS = -O3

growth_rates_txt = $(wildcard *.txt)
growth_rates_bin = $(growth_rates_txt:%.txt=%.bin)

.PHONY: all clean

all: grow2bin $(growth_rates_bin)
	@:

clean:
	$(RM) grow2bin $(growth_rates_bin)

grow2bin: grow2bin.c
	$(CC) $(CFLAGS) -o $@ $^

%.bin: %.txt
	./grow2bin $<
