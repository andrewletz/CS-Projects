#include <stdio.h>

/*
 * Andrew Letz, October 6th 2017
 * Textual answers in solution document
 */

unsigned f2u(float f) {
	return *((unsigned*)&f);
}

/*
 * Returns 1 if x < y or x == y, 0 otherwise
 */
int float_le(float x, float y) {
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;

	return (sx > sy) || // true if sx is 1 and sy is zero, meaning x is smaller			
		((sx == sy == 0) && (ux >= uy)) || // if both positive, compare values
		((sx == sy == 1) && (ux <= uy)) || // if both negative, compare values
		(ux << 1 == 0 && uy << 1 == 0); // if they are both 0, return true
} 


int main(void)
{
	printf("float_le(0.0f, 0.0f): %i\n", float_le(0.0f, 0.0f));
	printf("float_le(-0.0f, 0.0f): %i\n", float_le(-0.0f, 0.0f));
	printf("float_le(-1.0f, 0.0f): %i\n", float_le(-1.0f, 0.0f));
	printf("float_le(0.0f, 1.0f): %i\n", float_le(0.0f, 1.0f));
	printf("float_le(1.0f, 0.0f): %i\n", float_le(1.0f, 0.0f));
	printf("float_le(0.0f, -1.0f): %i\n", float_le(0.0f, -1.0f));

    return 0;
}