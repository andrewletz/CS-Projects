/*
Dynamic Triangle
Author: Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

/* Allocate a triangle of height "height" (a 2-D array of int) */
void allocateNumberTriangle(const int height, int ***triangle) {
	*triangle = (int **)malloc(height * sizeof(int*));
	int counter = 1;
	for(int i = 0; i < height; i++) {
		(*triangle)[i] = (int *)malloc(counter * sizeof(int));
		counter += 2;
	}
}

/* Initialize the 2-D triangle array */
void initializeNumberTriangle(const int height, int **triangle) {
	int counter = 1;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < counter; j++) {
			// printf("%i is less than %i\n", j, counter );
			// printf("accessing triangle[%i][%i]\n", i, j);
			triangle[i][j] = j;
		}
		counter += 2;
	}
}

/* Print a formatted triangle */
void printNumberTriangle(const int size, int **triangle) {
	int counter = 1;
	int spaces = (size * 2) - 2;
	for(int i = 0; i < size; i++) {
		for (int l = 0; l < spaces; l++) {
				printf(" ");
		}
		for(int j = 0; j < counter; j++) {
			printf("%i ", triangle[i][j]);
		}
		counter += 2;
		spaces -= 2;
		printf("\n");
	}
}

/* Free the memory for the 2-D triangle array */
void deallocateNumberTriangle(const int size, int ***triangle) {
	for (int i = 0; i < size; i++) {
		free((*triangle)[i]);
	}
	free(*triangle);
}
