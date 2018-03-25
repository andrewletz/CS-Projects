/* Lab 3 static library main
   Andrew Letz
*/

#include <stdio.h>
#include "power.h"

int main() {
    int input;
    INPUT:
        printf("What power do you want to raise 2 to? ");
        scanf("%i", &input);
        while(getchar() != '\n');
        if (input < 2 || input > 8) {
            goto INPUT;
    }
    printf("result is: %i\n", power(2, input));

    return 0;
}