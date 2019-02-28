/*
 * maze.cpp
 *
 * Author: Andrew Letz
 */

#include "maze.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>

Maze::Maze(int size) {
	this->size = size;
	this->numberOfMoves = 0;
}

// code here taken from utils.cpp
void Maze::readFromFile(std::ifstream &f) {
	//std::streampos cPos = f.tellg(); 
	std::string theline;
	for (int i = 0; i < size; i++) {
		getline( f, theline );
		mazeData += theline.substr(0,size);
		//std::cout << mazeData.substr(i* size, size) << "\n";
		for (int j = 0; j < size; j++) {
			if (mazeData.substr((i * size) + j, 1) == "x") {
				this->xStart = i;
				this->row = xStart;
				this->yStart = j;
				this->col = yStart;
			}
		}
	}
	// reset the file stream
	//f.seekg(cPos);
}

void Maze::initialize() {
	// Set starting point
	this->row = xStart;
	this->col = yStart;

	// Set initial currentDirectionection
	if (col < size - 1 && isValidMove(row, col + 1)) {
		currentDirection = UP;
	} else if (row < size - 1 && isValidMove(row + 1, col)) {
		currentDirection = RIGHT;
	} else if (col > 0 && isValidMove(row, col - 1)) {
		currentDirection = DOWN;
	} else if (row > 0 && isValidMove(row - 1, col)) {
		currentDirection = LEFT;
	}
}

void Maze::printDir() {
	// Once direction has been finalized print where we went
	switch (currentDirection) {
		case UP:
			std::cout << "UP\n";
			break;
		case RIGHT:
			std::cout << "RIGHT\n";
			break;
		case DOWN:
			std::cout << "DOWN\n";
			break;
		case LEFT:
			std::cout << "LEFT\n";
			break;
	}
}

void Maze::step() {
	if (numberOfMoves == 0) {
		initialize();
	}

	switch (currentDirection) {
		case UP:
			if (isValidMove(row, col + 1)) {
				currentDirection = RIGHT;
				col++;
			} else if (isValidMove(row - 1, col)) {
				currentDirection = UP;
				row--;
			} else if (isValidMove(row, col - 1)) {
				currentDirection = LEFT;
				col--;
			} else if (isValidMove(row + 1, col)) {
				currentDirection = DOWN;
				row++;
			} 
			break;

		case RIGHT:
			if (isValidMove(row + 1, col)) {
				currentDirection = DOWN;
				row++;
			} else if (isValidMove(row, col + 1)) {
				currentDirection = RIGHT;
				col++;
			} else if (isValidMove(row - 1, col)) {
				currentDirection = UP;
				row--;
			} else if (isValidMove(row, col - 1)) {
				currentDirection = LEFT;
				col--;
			}
			break;

		case DOWN:
			if (isValidMove(row, col - 1)) {
				currentDirection = LEFT;
				col--;
			} else if (isValidMove(row + 1, col)) {
				currentDirection = DOWN;
				row++;
			} else if (isValidMove(row, col + 1)) {
				currentDirection = RIGHT;
				col++;
			} else if (isValidMove(row - 1, col)) {
				currentDirection = UP;
				row--;
			}
			break;

		case LEFT:
			if (isValidMove(row - 1, col)) {
				currentDirection = UP;
				row--;
			} else if (isValidMove(row, col - 1)) {
				currentDirection = LEFT;
				col--;
			} else if (isValidMove(row + 1, col)) {
				currentDirection = DOWN;
				row++;
			} else if (isValidMove(row, col + 1)) {
				currentDirection = RIGHT;
				col++;
			}
			break;
	}

	numberOfMoves++;
}

bool Maze::atExit() {
	if (numberOfMoves == 0) {
		return false;
	}
	return atEdge(row, col);
}

void Maze::getCurrentPosition(int &row, int &col) {
	row = this->row;
	col = this->col;
}

bool Maze::atEdge(int x, int y) {
	// If any of these are true, we are on the border (ie, we found the exit)
	if (x == 0 || y == 0 || x == size - 1 || y == size - 1) {
		return true;
	}
	return false;
}

char Maze::getValue(int x, int y) {
	return mazeData.substr((x * size) + y, 1)[0];
}

bool Maze::isValidMove(int x, int y) {
	return mazeData.substr((x * size) + y, 1) == ".";
}