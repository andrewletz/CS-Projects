#include <stdio.h>
#include <stdlib.h>

/*
 * Andrew Letz, October 14th 2017
 * Assignment 3, Problem 1
 */

int* readArray(int length) 
{
	// Allocate length * 4 bytes worth of memory on the heap to use as our array
	int* a = malloc(sizeof(int) * length);
	// If you want to fill it with 0s instead of random numbers (not necessary
	// as we override it with user input)
	// int i;
	// for (i = 0; i < length; i = i + 1) {
	// 	a[i] = 0;
	// } 
	return a;
}

void swap(int *xp, int *yp) 
{
	// Hardest to read method by Zach Schmidt in lab
	// We do this on pointers so that it actually affects
	// the data and not the temporary variables
	*xp ^= *yp;
	*yp ^= *xp;
	*xp ^= *yp;
	return;	
}

void sortArray(int* array, int length) 
{
	// Selection sort is pretty simple
	int i;
	for (i = 0; i < length; i = i + 1) {
		int j;
		for (j = i + 1; j < length; j = j + 1) {
			if (array[j] < array[i]) {
				// Remember to pass in their addresses
				swap(&array[j], &array[i]);
			}
		}
	}
	return;
}

void printArray(int* array, int length) 
{
	int i;
	printf("[ ");
	for (i = 0; i < length; i = i + 1) {
		printf("%d ", array[i]);
	}
	printf("]\n");
	return;
}


int main(void)
{
	int length;
	printf("Enter array length: \n");
	scanf("%d", &length);

	int* array = readArray(length);

	int s;
	// Loop to get all user values into our array
	for (s = 0; s < length; s = s + 1) {
		int val;
		printf("Enter value for array index %d:\n", s);
		scanf("%d", &val);
		array[s] = val;
	}

	printf("Before sorting the array:\n");
	printArray(array, length);

	sortArray(array, length);

	printf("After sorting the array:\n");
	printArray(array, length);
	
	free(array);
    return 0;
}