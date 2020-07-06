CXXFLAGS := -std=c++17 -O2 -Wall -Wno-switch -lstdc++fs

SRCS := Source.cpp Narc.cpp fnmatch.c
HEADERS := Narc.h fnmatch.h

.PHONY: all clean

all: knarc
	@:

knarc: $(SRCS) $(HEADERS)
	$(CXX) $(SRCS) -o $@ $(LDFLAGS) $(CXXFLAGS)

clean:
	$(RM) knarc knarc.exe
