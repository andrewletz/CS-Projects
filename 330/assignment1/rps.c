/* Rock Paper Scissors, Andrew Letz */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[8];
    int choice;

    printf("Enter rock, paper, or scissors:\n");
    scanf("%s", input);
    if (strcmp(input, "rock") == 0) {
    	printf("You picked rock.\n");
    	choice = 0;
    } else if (strcmp(input, "paper") == 0) {
    	printf("You picked paper.\n");
    	choice = 1;
    } else if (strcmp(input, "scissors") == 0) {
    	printf("You picked scissors.\n");
    	choice = 2;
    } else {
    	printf("Invalid user choice, you must enter rock, paper, or scissors.\n");
    	return 0;
    }

	srand(time(NULL));
	int ai_choice = rand() % 3; // get a random number from 0 to 2

    if (ai_choice == 0) {
    	printf("Computer picked rock.\n");
    	if (choice == 1) {
    		printf("Paper wins.\n");
    	} else if (choice == 2) {
    		printf("Rock wins.\n");
    	}
    } else if (ai_choice == 1) {
    	printf("Computer picked paper.\n");
    	if (choice == 0) {
    		printf("Paper wins.\n");
    	} else if (choice == 2) {
    		printf("Scissors wins.\n");
    	}
    } else {
    	printf("Computer picked scissors.\n");
    	if (choice == 0) {
    		printf("Rock wins.\n");
    	} else if (choice == 1) {
    		printf("Scissors wins.\n");
    	}
    }

    if (ai_choice == choice) {
    	printf("The game is a tie.\n");
    }

    return 0;
}
