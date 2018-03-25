#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 		Memory related functions
 */

void allocateNumberMaze(const int size, char ***maze) {
	*maze = (char **)malloc(size * sizeof(char*));
	for(int i = 0; i < size; i++) {
		(*maze)[i] = (char *)malloc(size * sizeof(char));
	}
}

void deallocateNumberMaze(const int size, char ***maze) {
	for (int i = 0; i < size; i++) {
		free((*maze)[i]);
	}
	free(*maze);
}

void printNumberMaze(const int size, char **maze) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
}

/*
 * 		Maze solving functions
 */

enum Direction {DOWN, RIGHT, UP, LEFT};

void mazeSolve(char ***maze, int mazeSize, int xrow, int xcol) {
	enum Direction dir;
	int row = xrow;
	int col = xcol;

	// Set initial direction
	if (col < mazeSize - 1 && (*maze)[row][col + 1] == '.') {
		dir = UP;
	} else if (row < mazeSize - 1 && (*maze)[row + 1][col] == '.') {
		dir = RIGHT;
	} else if (col > 0 && (*maze)[row][col - 1] == '.') {
		dir = DOWN;
	} else if (row > 0 && (*maze)[row - 1][col] == '.') {
		dir = LEFT;
	}

	while (1) {
		// First switch to move our imaginary guy around (always follow the right)
		switch (dir) {
			case UP:
				if ((*maze)[row][col + 1] == '.') {
					dir = RIGHT;
					col++;
				} else if ((*maze)[row - 1][col] == '.') {
					dir = UP;
					row--;
				} else if ((*maze)[row][col - 1] == '.') {
					dir = LEFT;
					col--;
				} else if ((*maze)[row + 1][col] == '.') {
					dir = DOWN;
					row++;
				} 
				break;

			case RIGHT:
				if ((*maze)[row + 1][col] == '.') {
					dir = DOWN;
					row++;
				} else if ((*maze)[row][col + 1] == '.') {
					dir = RIGHT;
					col++;
				} else if ((*maze)[row - 1][col] == '.') {
					dir = UP;
					row--;
				} else if ((*maze)[row][col - 1] == '.') {
					dir = LEFT;
					col--;
				}
				break;

			case DOWN:
				if ((*maze)[row][col - 1] == '.') {
					dir = LEFT;
					col--;
				} else if ((*maze)[row + 1][col] == '.') {
					dir = DOWN;
					row++;
				} else if ((*maze)[row][col + 1] == '.') {
					dir = RIGHT;
					col++;
				} else if ((*maze)[row - 1][col] == '.') {
					dir = UP;
					row--;
				}
				break;

			case LEFT:
				if ((*maze)[row - 1][col] == '.') {
					dir = UP;
					row--;
				} else if ((*maze)[row][col - 1] == '.') {
					dir = LEFT;
					col--;
				} else if ((*maze)[row + 1][col] == '.') {
					dir = DOWN;
					row++;
				} else if ((*maze)[row][col + 1] == '.') {
					dir = RIGHT;
					col++;
				}
				break;
		}

		// Once direction has been finalized print where we went
		switch (dir) {
			case UP:
				printf("UP\n");
				break;
			case RIGHT:
				printf("RIGHT\n");
				break;
			case DOWN:
				printf("DOWN\n");
				break;
			case LEFT:
				printf("LEFT\n");
				break;
		}

		// If any of these are true, we are on the border (ie, we found the exit)
		if (row == 0 || col == 0 || row == mazeSize - 1 || col == mazeSize - 1) {
			break;
		}
	}
}


/*
 * 		Main
 */

int main(int argc, const char* argv[])
{
    if (argc != 2) {
        printf("error; no input file name\n");
        return 1;
    }

    FILE *filePointer;
    filePointer = fopen(argv[1], "r");

    int numberOfTestCases = 0;
    fscanf(filePointer, "%d\n", &numberOfTestCases);

    for (int testCaseNumber = 0; testCaseNumber < numberOfTestCases; testCaseNumber++) {
        int mazeSize = 0;
        fscanf(filePointer, "%d\n", &mazeSize);
        
        printf("ENTER\n");

       	char** maze;
       	allocateNumberMaze(mazeSize, &maze);
		
		int xrow = 0;
		int xcol = 0;
		// scan each line of the maze into our char array
		for (int i = 0; i < mazeSize; i++) { 
			fscanf(filePointer, "%s", maze[i]);
			for (int j = 0; j < mazeSize; j++) {
				if(maze[i][j] == 'x') { // get our exit coordinates now
					xrow = i;
					xcol = j;
				}
			}
		}
		
		mazeSolve(&maze, mazeSize, xrow, xcol);
       	deallocateNumberMaze(mazeSize, &maze);

        printf("EXIT\n***\n");        
    }

    fclose(filePointer);
    return 0;
}
