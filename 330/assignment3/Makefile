SOURCES = $(wildcard *.c)

CC = gcc
CFLAGS = -std=c11 -g -Wall

# Pattern used in target and prerequisites
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $<

#tests: test-square.exe test-triangle.exe test-diamond.exe test-all.exe

maze: maze.o
	$(CC) -o $@ $^ -lm

memcheck: maze
	valgrind --leak-check=yes --track-origins=yes ./maze

clean: 
	$(RM) $(wildcard *.exe) $(wildcard *.o) maze