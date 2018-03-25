CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $<

test-game.exe: test-game.cpp game.o
	$(CXX) $(CFLAGS) -o $@ $^

clean: 
	$(RM) $(wildcard *.exe) $(wildcard *.o)
