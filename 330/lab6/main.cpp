/*
 * main.cpp for student
 *
 * Author: Andrew Letz
 */

#include "student.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	Student s;
	Student s_input("Andrew", "Letz", 19);
	Student s_copy = s_input;
	cout << s_input;
}