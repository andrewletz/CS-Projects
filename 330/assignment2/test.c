/*
Dynamic Memory Shapes Test
Author: Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"
#include "diamond.h"
#include "square.h"

int main() {
    // Test for square
    int input1;
    INPUT1:
        printf("Please enter the size of the square [2-10]: ");
        scanf("%i", &input1);
        while(getchar() != '\n');
        if (input1 < 2 || input1 > 10) {
            goto INPUT1;
    }

    int** square;
    allocateNumberSquare(input1, &square);
    initializeNumberSquare(input1, square);
    printNumberSquare(input1, square);
    deallocateNumberSquare(input1, &square);

    // Test for triangle
    int input2;
    INPUT2:
        printf("Please enter the size of the triangle [1-5]: ");
        scanf("%i", &input2);
        while(getchar() != '\n');
        if (input2 < 1 || input2 > 5) {
            goto INPUT2;
    }

    int** triangle;
    allocateNumberTriangle(input2, &triangle);
    initializeNumberTriangle(input2, triangle);
    printNumberTriangle(input2, triangle);
    deallocateNumberTriangle(input2, &triangle);

    // Test for diamond
    int input3;
    INPUT3:
        printf("Please enter the size of the diamond [an odd number between 3 and 9 (inclusive)]: ");
        scanf("%i", &input3);
        while(getchar() != '\n');
        if (input3 < 3 || input3 > 9 || input3 % 2 == 0) {
            goto INPUT3;
    }

    int** diamond;
    allocateNumberSquare(input3, &diamond);
    initializeNumberSquare(input3, diamond);
    printNumberDiamond(input3, diamond);
    deallocateNumberSquare(input3, &diamond);

    return 0;
}
