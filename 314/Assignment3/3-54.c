#include <stdio.h>
#include <stdlib.h>

/*
 * Andrew Letz, October 14th 2017
 * Assignment 3, Problem 2
 */

int decode2(int x, int y, int z) 
{
	/* z = ebp + 16
	 * y = ebp + 12
	 * x = ebp + 8
	*/
	int edx = y; // movl 12(%ebp), %edx
	edx = edx - z; //  subl 16(%ebp), %edx
	int eax = edx; // movl %edx, %eax
	eax = eax << 31; // sall $31, %eax
	eax = eax >> 31; // sarl $31, %eax
	edx = edx * x; // imull 8(%ebp), %edx
	eax = eax ^ edx; // xorl %edx, %eax
	return eax;
}


int main(void)
{
	printf("decode2(1, 2, 4): %d\n", decode2(1, 2, 4));
	printf("decode2(-4, -8, -12): %d\n", decode2(-4, -8, -12));
    return 0;
}