CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $< 

# Link with external main (on ix-dev only)
test-main.exe: main.o maze.o utils.o
	$(CXX) -fPIC -o $@ $^

test-maze.exe: test-maze.cpp maze.o utils.o #add your objects to this line
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	$(RM) test-main.exe $(OBJECTS)
