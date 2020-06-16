CC = gcc
CFLAGS = -O3

growth_rates_txt = $(wildcard *.txt)
growth_rates_bin = $(growth_rates_txt:%.txt=%.bin)

.PHONY: all clean

all: csv2bin $(growth_rates_bin)
	@:

clean:
	$(RM) csv2bin $(growth_rates_bin)

csv2bin: csv2bin.c
	$(CC) $(CFLAGS) -o $@ $^

%.bin: %.txt
	./csv2bin $<
