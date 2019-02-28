/*
 * game.cpp
 *
 * Author: Andrew Letz
 */

#include "game.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <climits>

using namespace std;

const int Game::y[8] = { -1, -1, -1,  1, 1, 1,  0, 0 };
const int Game::x[8] = { -1,  0,  1, -1, 0, 1, -1, 1 };
bool Game::seeded = false;

// Simple constructor for testing, allows for a lot of stepping
Game::Game() : grid(10, vector<char>(10, '.')), maxSteps(INT_MAX) {
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	initializeGrid();
}

Game::Game(int steps) : grid(10, vector<char>(10, '.')), maxSteps(steps) { 
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	initializeGrid();
	for (int i = 0; i < maxSteps; i++) {
		step();
	}
}

Game::Game(int steps, int size) : grid(size, vector<char>(size, '.')), maxSteps(steps) { 
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	initializeGrid();
	for (int i = 0; i < maxSteps; i++) {
		step();
	}
} 

Game::Game(int steps, int rows, int cols) : grid(rows, vector<char>(cols, '.')), maxSteps(steps) { 
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	initializeGrid();
	for (int i = 0; i < maxSteps; i++) {
		step();
	}
}

void Game::initializeGrid() {
	int random;
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int j = 0; j < grid[i].size(); j++) {
			random = rand() % 101;
			if (random <= 45) { // 45% chance for sheep
				grid[i][j] = 'S';
			} else if (random <= 51) { // 6% chance for wolf
				grid[i][j] = 'W';
			} else if (random <= 55) { // 4% chance for farmer
				grid[i][j] = 'F';
			}
		}
	}
	printGrid();
}

// modified a nifty outOfBounds check from http://www.cplusplus.com/forum/general/189857/
bool Game::outOfBounds(int row, int col, int numRows, int numCols) {
	if(row < 0 || row >= numRows) return true;
  	if(col < 0 || col >= numCols) return true;
    return false;
}

void Game::step() {
	if (numSteps >= maxSteps) {
		return;
	}
	unsigned int rows = grid.size();
	unsigned int cols = grid[0].size();

	int wolves = 0, sheep = 0, farmers = 0; // keep track of number of animals
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			vector<vector<int>> empties; // so we know which neighbors are empty

			for (int k = 0; k < 8; k++) { // for every neighbor
				int newRow = i + y[k];
				int newCol = j + x[k];
				if (!outOfBounds(newRow, newCol, rows, cols)) {
					switch(grid[newRow][newCol]) {
						case 'W':	// running sums of neighbor types
							wolves++;
							break;
						case 'S':
							sheep++;
							break;
						case 'F':
							farmers++;
							break;
						default:
							vector<int> coord = {newRow, newCol};
							empties.push_back(coord); // keep track of empty coords
							break;
						}
					}
				} // end of neighbor loop

				// Perform updates on current selected cell (grid[i][j])
				// cout << "Working on (" << i << ',' << j << ") with W: " << wolves << ", S: " << sheep << ", F: " << farmers << endl;
				switch(grid[i][j]) {
					case 'S':
						if (sheep > 3 || wolves > 0) {
							grid[i][j] = '.';
						}
						break;
					case '.':
						if (sheep == 2) {
							grid[i][j] = 'S';
						} else if (wolves == 2) {
							grid[i][j] = 'W';
						} else if (farmers == 2) {
							grid[i][j] = 'F';
						}
						break;
					case 'W':
						if (farmers > 0 || sheep == 0) {
							grid[i][j] = '.';
							//cout << "W at (" << i << ',' << j << ") died" << endl;

						}
						break;
					case 'F':
						if (!empties.empty()) {
							grid[i][j] = '.';
							int randIdx = rand() % empties.size();
							grid[empties[randIdx][0]][empties[randIdx][1]] = 'F';
						}
						break;
				}
				wolves = 0, sheep = 0, farmers = 0;
			} // end of column loop
		} // end of row loop
	cout << endl;
	numSteps++;
	cout << "Step " << numSteps << ":\n";
	printGrid();
}

void Game::printGrid() {
	for (vector<vector<char>>::const_iterator row = grid.begin(); row != grid.end(); ++row) { 
		for (vector<char>::const_iterator col = row->begin(); col != row->end(); ++col) {
			cout << *col; 
		}
		cout << endl;
	}
}