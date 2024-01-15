CXX = g++
CXXFLAGS = -g -Wall -Wextra

.PHONY: all
all: CW1

CW1: CW1.o
	$(CXX) $(CXXFLAGS) -o $@ $^

CW1.o: CW1.cpp 
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clear
clear:
	$(RM) *~ *.o *.exe CW1
