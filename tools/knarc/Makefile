.PHONY: all clean

all: knarc
	@:

knarc: Source.cpp Narc.cpp Narc.h
	g++-9 Source.cpp Narc.cpp -o $@ -std=c++17 -O2 -Wall -Wno-switch -lstdc++fs

clean:
	$(RM) knarc knarc.exe
