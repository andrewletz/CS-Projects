#include <iostream>

int main() {
	int array[10];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		array[i] = i;
		sum += i;
	}
	std::cout << "sum is " << sum << std::endl;

	
}