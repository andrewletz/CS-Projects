#include <stdio.h>
#include <stdlib.h>

/*
 * Andrew Letz, November 18th 2017
 * Assignment 7, Problem 3
 */

void inner(float *u, float *v, int length, float *dest) {
	int i;
	float sum = 0.0f;
	for (i = 0; i < length; ++i) {
		sum += u[i] * v[i];
	}
	*dest = sum;
} 

void inner2(float *u, float *v, int length, float *dest) {
	int i;
	float sum1 = 0.0f;
	float sum2 = 0.0f;
	float sum3 = 0.0f;
	float sum4 = 0.0f;
	for (i = 0; i < length; i += 4) { // Add elements 4 at a time
		sum1 += u[i] * v[i];
		sum2 += u[i + 1] * v[i + 1];
		sum3 += u[i + 2] * v[i + 2];
		sum4 += u[i + 3] * v[i + 3];
	}

	for (; i < length; i++) { // Add remaining elements
		sum1 += u[i] * v[i];
	}

	*dest = sum1 + sum2 + sum3 + sum4;
} 


int main(void)
{
	// Test number 1
	printf("Vector 1 is {1, 2, 3, 4}");
	printf("\nVector 2 is {7, 8, 9, 10}");
	printf("\nTheir inner-product value should be 90.");
	printf("\nUsing the normal loop we get:");
	float vec1[4] = {1.0, 2.0, 3.0, 4.0};
	float vec2[4] = {7.0, 8.0, 9.0, 10.0};
	
	float destSum1 = 0;
	inner(vec1, vec2, 4, &destSum1);
	printf("\n	> Sum is %f", destSum1);

	printf("\nUsing the 4-way unrolled loop we get:");
	
	float destSum2 = 0;
	inner2(vec1, vec2, 4, &destSum2);
	printf("\n 	> Sum is %f", destSum2);

	printf("\n");
	// Test number 2
	printf("\nVector 1 is {1, 2, 3, 4, 5, 6, 7}");
	printf("\nVector 2 is {1, 2, 3, 4, 5, 6, 7}");
	printf("\nTheir inner-product value should be 140.");
	printf("\nUsing the normal loop we get:");
	float vec3[7] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
	float vec4[7] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
	
	float destSum3 = 0;
	inner(vec3, vec4, 7, &destSum3);
	printf("\n	> Sum is %f", destSum3);

	printf("\nUsing the 4-way unrolled loop we get:");
	
	float destSum4 = 0;
	inner2(vec3, vec4, 7, &destSum4);
	printf("\n 	> Sum is %f", destSum4);
}