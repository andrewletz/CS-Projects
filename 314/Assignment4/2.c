#include <stdio.h>
#include <stdlib.h>

/*
 * Andrew Letz, October 25th 2017
 * Assignment 4, Problem 2.c
 */

#define M 13

typedef int Marray_t[M][M];

void transpose(Marray_t A) {
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < i; j++) {
			int t = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = t;
 		}
 	}
}

void transpose_O(Marray_t A) {
	int i, j;
	for (i = 0; i < M; i++) {

		j = 0;
		// Creates a pointer to A[i][0] (the row we are indexing)
		int *row_pointer = &(*((int *)A + i * M + 0));

		// Creates a base column pointer to A[0][i] (the column we start indexing)
		int *col_pointer = &(*((int *)A + 0 + i));

		do {

			// Save the result of row[j] in t
			int t = *(row_pointer + j);
			// Set the value at row[j] to the value at col_pointer
			*(row_pointer + j) = *col_pointer;
			// Set the value at col_pointer to t
			*col_pointer = t;
			// Move col_pointer over by 13 bytes, so to the next row at the same column
			col_pointer += M;
			j++;
			
 		} while (j < i);
 	}
}

void print_matrix(Marray_t A) {
	int i,j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}	
}


int main(void)
{
	Marray_t mray = {
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
	};
	
	printf("Before transposing: \n");
	print_matrix(mray);
	printf("\n");

	transpose_O(mray);

	printf("After transposing: \n");
	print_matrix(mray);
	printf("\n");
}