#include <stdio.h>
#include <stdlib.h>

/*
 * Andrew Letz, November 28th, 2017
 * Assignment 8, Problem 2
 */

typedef struct cache_block
{
	// Represents a single valid bit
	unsigned char valid;
	// Represents a 26-bit tag
	unsigned int tag;
	// Represents a 4-byte value
	unsigned char value[4];
} block;

void printValues(block* cache) {
	int i;
	for (i = 0; i < 16; i = i + 1) {
		if (cache[i].valid == 1) {
			printf("Valid block\n");
		}
	}
} 

int getSet(unsigned int address) {
	address <<= 26;
	address >>= 28;
	return address
}

int main(void)
{
	// char input;
	// printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: w \n");
	// scanf("%d", &input);

	block* cache = malloc(sizeof(block) * 16);

	int i;
	for (i = 0; i < 16; i = i + 1) {
		block newBlock = {0, 0, 0x0000};
		cache[i] = newBlock;
	}

	unsigned int run = 1;
	while(run) {
		char input;
		printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: w \n");
		scanf(" %c", &input);

		switch(input) {
			case 'w':
				unsigned int address;
				printf("Enter 32-bit unsigned hex address: \n");
				scanf(" %x", address);
				unsigned int value;
				printf("Enter 32-bit unsigned hex value: \n");
				scanf(" %x", value);
				break;
			case 'r':
				
				break;
			case 'p':
				printValues(cache);
				break;
			case 'q':
				run = 0;
				break;
		}

	}
	
	free(cache);
    return 0;
}