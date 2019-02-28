/*
Dynamic Square Test
Author: Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>
#include "square.h"

int main() {
    int input;

    INPUT:
        printf("Please enter the size of the square [2-10]: ");
        scanf("%i", &input);
        while(getchar() != '\n');
        if (input < 2 || input > 10) {
            goto INPUT;
    }

    int** square;
    allocateNumberSquare(input, &square);
    initializeNumberSquare(input, square);
    printNumberSquare(input, square);
    deallocateNumberSquare(input, &square);

    return 0;
}
