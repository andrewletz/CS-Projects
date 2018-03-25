/*
 * lab7.cpp
 *
 * Author: Andrew Letz
 */

#include <iostream>
#include <string>
#include <vector>
#include <random>
// #include "matplotlibcpp.h"
#include <algorithm>

using namespace std;
// namespace plt = matplotlibcpp;

void printV(const vector<int> &v) {
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) { 
		cout << *it << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1,100);
	vector<int> v;

	for (int i = 0; i < 15; i++) {
		int num = distribution(generator);
		v.push_back(num);
		// plt::plot(num);
	}

	cout << "Unsorted vector:" << endl;
	printV(v);
	// plt::show();

	cout << "Sorted vector:" << endl;
	sort(v.begin(), v.end());
	printV(v);
	// plt::show();

	vector<int> vCopy;
	copy(v.begin(), v.end(), back_inserter(vCopy));
	cout << "Copy of sorted vector:" << endl;
	printV(vCopy);

	random_shuffle(vCopy.begin(), vCopy.end());
	cout << "Shuffled of copied vector:" << endl;
	printV(vCopy);
}