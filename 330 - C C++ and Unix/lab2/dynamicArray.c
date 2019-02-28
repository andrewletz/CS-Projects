/* Lab 2 dynamic array test 
   Andrew Letz
*/

#include <stdio.h>
#include <stdlib.h>

int arrayEqual2(int m, int n, int **a, int **b) {
    for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != b[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int main() {
	int **a2 = (int **)malloc(2 * sizeof(int));
	int **b2 = (int **)malloc(2 * sizeof(int));
	int **c2 = (int **)malloc(2 * sizeof(int));
	for (int i = 0; i < 2; i++) {
		a2[i] = (int *)malloc(3 * sizeof(int));
		b2[i] = (int *)malloc(3 * sizeof(int));
		c2[i] = (int *)malloc(3 * sizeof(int));
	}
	

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			a2[i][j] = 4;
			b2[i][j] = 4;
			c2[i][j] = 3;
		}
	}

	printf("A and B are equal: %i\n", arrayEqual2(2, 3, a2, b2));
	printf("A and C are equal: %i\n", arrayEqual2(2, 3, a2, c2));

	for (int i = 0; i < 2; i++) {
		free(a2[i]);
		free(b2[i]);
		free(c2[i]);
	}
	free(a2);
	free(b2);
	free(c2);

	return 0;
}