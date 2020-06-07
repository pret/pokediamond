CXX ?= g++-9

CXXFLAGS := -std=c++17 -O2 -Wall -Wno-switch -lstdc++fs

SRCS := Source.cpp Narc.cpp
HEADERS := Narc.h

.PHONY: all clean

all: knarc
	@:

knarc: $(SRCS) $(HEADERS)
	$(CXX) $(SRCS) -o $@ $(LDFLAGS) $(CXXFLAGS)

clean:
	$(RM) knarc knarc.exe
