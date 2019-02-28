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

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, int len) {
	int i;
	for (i = 0; i < len; i++)
		printf(" %.2x ", start[i]);
	printf(" ");
}

void printValues(block* cache) {
	int i;
	block targetBlock;
	for (i = 0; i < 16; i = i + 1) {
		targetBlock = cache[i];
		if (targetBlock.valid == 1) {
			printf("set: %i | tag: %i | valid: %i | value:", i, targetBlock.tag, targetBlock.valid);
			show_bytes((byte_pointer) &targetBlock.value, sizeof(char) * 4);
			printf("\n");
		}
	}
} 

int getSet(unsigned int address) {
	address <<= 26;
	address >>= 28;
	return address;
}

int getBlockOffset(unsigned int address) {
	address <<= 30;
	address >>= 30;
	return address;
}

int getTag(unsigned int address) {
	address >>= 6;
	return address;
}

void writeToCache(block* cache, unsigned int address, unsigned int value) {
	short setNum = getSet(address);
	unsigned int setTag = getTag(address);
	block targetBlock =  cache[setNum];
	if (targetBlock.valid == 0) {
		targetBlock.valid = 1;
		targetBlock.tag = setTag;
		targetBlock.value[0] = value;
		targetBlock.value[1] = value >> 8;
		targetBlock.value[2] = value >> 16;
		targetBlock.value[3] = value >> 24;
		printf("wrote set: %i | tag: %i | valid: %i | value:", setNum, targetBlock.tag, targetBlock.valid);
		show_bytes((byte_pointer) &targetBlock.value, sizeof(char) * 4);
		printf("\n");
	} else {
		printf("evicting block: set: %i | tag: %i | valid: %i | value:", setNum, targetBlock.tag, targetBlock.valid);
		show_bytes((byte_pointer) &targetBlock.value, sizeof(char) * 4);
		printf("\n");
		targetBlock.tag = setTag;
		targetBlock.value[0] = value;
		targetBlock.value[1] = value >> 8;
		targetBlock.value[2] = value >> 16;
		targetBlock.value[3] = value >> 24;
		printf("wrote set: %i | tag: %i | valid: %i | value:", setNum, targetBlock.tag, targetBlock.valid);
		show_bytes((byte_pointer) &targetBlock.value, sizeof(char) * 4);
		printf("\n");
	}
	cache[setNum] = targetBlock;
}

void readFromCache(block* cache, unsigned int address) {
	short setNum = getSet(address);
	block targetBlock =  cache[setNum];
	int blockTag = getTag(address);
	printf("looking for set: %i | tag: %i\n", setNum, blockTag);
	if (targetBlock.valid == 0) {
		printf("no valid set found - miss!\n");
	} else {
		short blockOffset = getBlockOffset(address);
		printf("found set: %i | tag: %i | offset: %i | valid: %i | value: %x\n", setNum, targetBlock.tag, 
			blockOffset, targetBlock.valid, targetBlock.value[blockOffset]);
		if (targetBlock.tag != blockTag) {
			printf("tags don't match - miss!\n");
		} else {
			printf("hit!\n");
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
	char input;
	while(run) {
		printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: \n");
		scanf(" %c", &input);

		if (input == 'w') {
			unsigned int address;
			printf("Enter 32-bit unsigned hex address: \n");
			scanf(" %x", &address);
			unsigned int value;
			printf("Enter 32-bit unsigned hex value: \n");
			scanf(" %x", &value);
			writeToCache(cache, address, value);
		} else if (input == 'r') {
			unsigned int address;
			printf("Enter 32-bit unsigned hex address: \n");
			scanf(" %x", &address);
			readFromCache(cache, address);
		} else if (input == 'p') {
			printValues(cache);
		} else if (input == 'q') {
			printf("Successfully quit.");
			run = 0;
		} else {
			printf("Invalid input, please try again.\n");
		}

	}
	
	free(cache);
    return 0;
}