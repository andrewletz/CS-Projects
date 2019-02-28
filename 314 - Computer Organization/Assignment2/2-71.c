#include <stdio.h>

/*
 * Andrew Letz, October 6th 2017
 * Textual answers in solution document
 */

/* Declaration of data type where 4 bytes are packed
 into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum) 
{
		/*
 		* Instead of shifting right, we shift left in order to get the byte
 		* we want into the most significant spot. This allows us to shift it
 		* to the right by 24 bits, which will sign extend the most significant 
 		* bit, retaining negative values in the process.
 		*/
 		int signedBit = word << ((3 - bytenum) << 3);
 		return signedBit >> 24;
}


int main(void)
{
	int pos1 = 0x11550000;
	int pos2 = 0x11003400;

	int neg1 = 0x11880000;
	int neg2 = 0x1100AA00;

	printf("Positive tests: \n");
	int pos1Test = xbyte(pos1, 2);
	printf("Getting byte 2 from 0x%X returns 0x%X, which is %i.\n", pos1, pos1Test, pos1Test);

	int pos2Test = xbyte(pos2, 1);
	printf("Getting byte 1 from 0x%X returns 0x%X, which is %i.\n", pos2, pos2Test, pos2Test);

	printf("\nNegative tests: \n");
	int neg1Test = xbyte(neg1, 2);
	printf("Getting byte 2 from 0x%X returns 0x%X, which is %i.\n", neg1, neg1Test, neg1Test);

	int neg2Test = xbyte(neg2, 1);
	printf("Getting byte 1 from 0x%X returns 0x%X, which is %i.", neg2, neg2Test, neg2Test);


    return 0;
}