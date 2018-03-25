/*
Dynamic Diamond
Author: Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>
#include "diamond.h"

/* Print a diamond containing the digits 0 - 9 */
void printNumberDiamond(const int size, int **square) {
	int counter = 1;
	int increasing = 1;
	int spaces = size - 1;
	for(int i = 0; i < size; i++) {
		for (int l = 0; l < spaces; l++) {
				printf(" ");
		}
		for(int j = 0; j < counter; j++) {
			printf("%i ", square[i][j]);
		}
		if (increasing) {
			counter += 2;
			spaces -= 2;
		} else {
			counter -= 2;
			spaces += 2;
		}
		if (spaces <= 0) {
			increasing = 0;
		}
		
		printf("\n");
	}
}