/*
 * test-maze.cpp
 *
 * Author: Andrew Letz
 */

#include "maze.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	std::ifstream f (argv[1]);

	std::string numMazes;
	getline(f, numMazes);
	int num = std::stoi(numMazes);

	for (int i = 0; i < num; i++) {
		std::string mazeSize;
		getline(f, mazeSize);

		int size = std::stoi(mazeSize);
		Maze m = Maze(size);

		m.readFromFile(f);
		std::cout << "ENTER\n";
		while(!m.atExit()) {
			m.step();
			m.printDir();
		}
		
		std::cout << "EXIT\n***\n";
	}

}