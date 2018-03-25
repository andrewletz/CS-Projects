/* Lab 2 static array test 
   Andrew Letz & Ethan Quick
*/

#include <stdio.h>

int arrayEqual(int m, int n, int a[m][n], int b[m][n]) {
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
	int a[3][4];
	int b[3][4];
	int c[3][4];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] = 4;
			b[i][j] = 4;
			c[i][j] = 3;
		}
	}

	printf("A and B are equal: %i\n", arrayEqual(3, 4, a, b));
	printf("A and C are equal: %i\n", arrayEqual(3, 4, a, c));

	return 0;
}