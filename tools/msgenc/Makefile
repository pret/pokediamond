CC := gcc
CFLAGS := -O2

.PHONY: all clean

all: msgenc
	@:

clean:
	$(RM) msgenc msgenc.exe

msgenc: msgenc.c
	$(CC) $(CFLAGS) -o $@ $^
