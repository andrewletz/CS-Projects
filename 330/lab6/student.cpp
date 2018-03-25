/*
 *  student.hpp
 *
 *  Author: Andrew Letz
 */

#include <fstream>
#include <iostream>
#include <string>
#include "student.hpp"

using namespace std;

Student::Student() {
	this->firstName = "John";
	this->lastName = "Doe";
	this->age = 18;
	cout << "Default Student: " << firstName << " " << lastName << ", " << age << endl;
}

Student::Student(string firstName, string lastName, int age) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->age = age;
	cout << "Input Student: " << firstName << " " << lastName << ", " << age << endl;
}

// Copy constructor
Student::Student(const Student &s2) {
	this->firstName = s2.firstName;
	this->lastName = s2.lastName;
	this->age = s2.age;
	cout << "Copy Student: " << firstName << " " << lastName << ", " << age << endl;
}

// Move constructor
Student::Student(Student &&s2) {
	this->firstName = s2.firstName;
	this->lastName = s2.lastName;
	this->age = s2.age;
	cout << "Move Student: " << firstName << " " << lastName << ", " << age << endl;
}

Student::~Student() {
	cout << "Destroyed Student: " << firstName << " " << lastName << ", " << age << endl;
}

bool Student::setFirstName(string input) {
	this->firstName = input;
	return true;
}

bool Student::setLastName(string input) {
	this->lastName = input;
	return true;
}

bool Student::setAge(int input) {
	if (input < 0) {
		return false;
	}
	this->age = input;
	return true;
}
