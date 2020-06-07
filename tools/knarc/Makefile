CXXFLAGS := -std=c++17 -O2 -Wall -Wno-switch -lstdc++fs

SRCS := Source.cpp Narc.cpp
HEADERS := Narc.h

.PHONY: all clean

all: knarc
	@:
	
knarc: $(SRCS) $(HEADERS)
	g++-8 $(CXXFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	$(RM) knarc knarc.exe
