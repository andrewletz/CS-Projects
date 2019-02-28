CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $<

lab-7.exe: lab7.cpp
	$(CXX) $(CFLAGS) -o $@ $^

clean: 
	$(RM) $(wildcard *.exe) $(wildcard *.o)
