CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $< 

main.exe: main.cpp student.o
	$(CXX) -fPIC -o $@ $^

clean:
	$(RM) test-main.exe $(OBJECTS)
