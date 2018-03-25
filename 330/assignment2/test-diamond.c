/*
Dynamic Diamond Test
Author: Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>
#include "diamond.h"
#include "square.h"

int main() {
    int input;

    INPUT:
        printf("Please enter the size of the diamond [an odd number between 3 and 9 (inclusive)]: ");
        scanf("%i", &input);
        while(getchar() != '\n');
        if (input < 3 || input > 9 || input % 2 == 0) {
            goto INPUT;
    }

    int** diamond;
    allocateNumberSquare(input, &diamond);
    initializeNumberSquare(input, diamond);
    printNumberDiamond(input, diamond);
    deallocateNumberSquare(input, &diamond);

    return 0;
}
