/*
 * game.hpp
 *
 * Author: Andrew Letz
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <string>

using namespace std;

class Game
{
public:
	Game();
	Game(int steps);
	Game(int steps, int size);
	Game(int steps, int rows, int cols);
	~Game() {}

	static const int y[8]; // 8 shifts to neighbors
	static const int x[8]; // used in functions 

	// step through the simulation once
	void step();

private:
	void initializeGrid();
	void printGrid();
	bool outOfBounds(int row, int col, int numRows, int numCols);

	vector<vector<char>> grid;
	int maxSteps;
	int numSteps = 0;
	static bool seeded;
};


#endif /* GAME_HPP_ */
