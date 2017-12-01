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
			case 'q':
				run = 0;
				break;
			case 'r':
				run = 1;
				break;
			case 'w':
				run = 0;
				break;
			case 'p':
				printValues(cache);
				break;
		}

	}
	
	free(cache);
    return 0;
}