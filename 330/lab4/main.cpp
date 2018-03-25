/* Lab 4
   Andrew Letz
*/

#include <iostream>
using namespace std;

void increment1(int x, int y) {
	x++; // this wont actually update the original variable
	y++;
}

void increment2(int &x, int &y) {
	x++;
	y++;
}

void increment3(int *x, int *y) {
	(*x)++;
	(*y)++;
}

int main() {
	int x = 1;
	int y = 6;

	increment1(x, y);
	cout << x;
	cout << y << endl;
	increment2(x, y);
	cout << x;
	cout << y << endl;
	increment3(&x, &y);
	cout << x;
	cout << y << endl;

	return 0;
}