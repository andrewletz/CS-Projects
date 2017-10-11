#include <stdio.h>
#include <string.h>

/*
 * Andrew Letz, October 6th 2017
 * Textual answers in solution document
 */

void copy_int(int val, void *buf, int maxbytes) {
	/*
 	 * Casting sizeof(val) to an int makes it a signed value, so the 
 	 * result of the expression is capable of going below 0.
 	 */
	if (maxbytes - (int)sizeof(val) >= 0) {
		memcpy(buf, (void *) &val, sizeof(val));
	}
} 


int main(void)
{
	int buffer[0];

	printf("Call copy_int(42, buffer, 4)\n");
	copy_int((int) 42, buffer, 4);
	printf("Check what is stored in buffer: %i\n", *buffer);

	printf("\nCall copy_int(999, buffer, 4)\n");
	copy_int((int) 999, buffer, 4);
	printf("Check what is stored in buffer: %i\n", *buffer);

	printf("\nCall copy_int(1337, buffer, 3)\n");
	printf("The value should still be 999 as a maxbyte size of 3 is too small\n");
	// This won't be called as it will not pass the conditional (3 - 4 >= 0), 
	// 4 being the byte size of a 32bit integer
	copy_int((int) 1337, buffer, 3);
	printf("Check what is stored in buffer: %i", *buffer);

    return 0;
}