/*
Dynamic Triangle Test
Author: Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

int main() {
    int input;

    INPUT:
        printf("Please enter the size of the triangle [1-5]: ");
        scanf("%i", &input);
        while(getchar() != '\n');
        if (input < 1 || input > 5) {
            goto INPUT;
    }

    int** triangle;
    allocateNumberTriangle(input, &triangle);
    initializeNumberTriangle(input, triangle);
    printNumberTriangle(input, triangle);
    deallocateNumberTriangle(input, &triangle);

    return 0;
}
