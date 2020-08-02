CXXFLAGS := -std=c++17 -O2 -Wall -Wno-switch
CFLAGS   := -O2 -Wall -Wno-switch

WSLENV ?= no
ifeq ($(OS),Windows_NT)
LDFLAGS  += -lstdc++fs
else
UNAME_S  := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
LDFLAGS  += -lstdc++ -lc++ -lc
else
ifneq ($(WSLENV),)
LDFLAGS  += -lstdc++fs
endif
endif
endif

CXX_SRCS := msgenc.cpp
HEADERS :=

.PHONY: all clean

all: msgenc
	@:

clean:
	$(RM) msgenc msgenc.exe

msgenc: $(CXX_SRCS) $(HEADERS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)
