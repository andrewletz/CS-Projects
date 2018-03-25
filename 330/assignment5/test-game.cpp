/*
 * test-game.cpp
 *
 * Author: Andrew Letz
 */

#include "game.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	// Game g1; // empty constructor for manual stepping
	// Game g2(10); // if you only want to specify steps, default size 10
	// Game g3(10, 5); // square grid of size 5x5 with 10 steps
	
	int rows, cols;
	cout << "Please enter the size of the grid (int int): \n";
	cin >> rows >> cols;
	int steps;
	cout << "Please enter the number of steps (int): \n";
	cin >> steps;

	Game g4(steps, rows, cols);
}