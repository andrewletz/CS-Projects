#include <stdio.h>

/*
 * Andrew Letz, September 30th 2017
 */

/*
 * Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n) {
    /*
     * Used hint on page 118 in the book about (1<<k)-1 (bit
     * pattern of the form [0, . . . , 0, 1, . . . , 1]).
     * Because there needs to be support for n = w, I substituted k
     * with (n - 1) as recommended. This would fall one bit short, 
     * however, so the number that is being shifted needed to change to 2.
     */

    return (2 << (n - 1)) - 1;
}

int main(void)
{
    printf("Replacing least significant 1 bits with 1: %i\n", lower_one_mask(1));
    printf("Replacing least significant 2 bits with 1: %i\n", lower_one_mask(2));
    printf("Replacing least significant 3 bits with 1: %i\n", lower_one_mask(3));
    printf("Replacing least significant 5 bits with 1: %i\n", lower_one_mask(5));
    printf("Replacing least significant 6 bits with 1: 0x%X\n", lower_one_mask(6));
    printf("Replacing least significant 17 bits with 1: 0x%X\n", lower_one_mask(17));
    // According to two's complement this will be -1
    printf("Replacing least significant 32 bits with 1: %i", lower_one_mask(32));
    return 0;
}