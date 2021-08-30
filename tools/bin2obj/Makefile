CXX := g++
CXXFLAGS := -O2 -g -std=c++17

.PHONY: all clean

all: bin2obj
	@:

clean:
	$(RM) bin2obj bin2obj.exe

bin2obj: bin2obj.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
