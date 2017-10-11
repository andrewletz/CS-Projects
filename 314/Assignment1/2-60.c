#include <stdio.h>

/*
 * Andrew Letz, September 30th 2017
 */

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	// Shifting to the left 3 times is equivalent to multiplying by 8.
	int shift_amt = (i << 3);

	// Pushing the mask over to where it needs to be (same position as the byte we want to replace)
	unsigned mask = 0xFF << shift_amt;

	/*
 	 * (x & ~mask): Gives us a string of bytes that is missing the byte we want to replace.
 	 * ((b << shift_amt)): Gives us a string of bytes with the new byte in the position we want.
 	 * |: or the previous two, filling the empty space with the new byte and leaving the rest the same.
 	 */ 
	return (x & ~mask) | ((b << shift_amt));	
}

int main(void)
{
    unsigned int input = 0x12345678;
    unsigned int switcheroo = 0xAB;
    int pos = 2;

    unsigned int testint = replace_byte(input, pos, switcheroo);
    printf("Replacing byte %i in %X with %X\n", pos, input, switcheroo);
    printf("Result: %X", testint);

    return 0;
}