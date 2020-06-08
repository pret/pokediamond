CXXFLAGS := -O3 -std=c++11

.PHONY: all clean

all: narccomp
	@:

clean:
	$(RM) narccomp narccomp.exe

narccomp: narccomp.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
