/*
 *  student.hpp
 *
 *  Author: Andrew Letz
 */

#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include <fstream>
#include <string>

using namespace std;

class Student
{
public:
	Student();
	Student(string firstName, string lastName, int age);
	Student(Student &&s2);
	Student(const Student &s2);
	~Student();

	bool setFirstName(string input);
	bool setLastName(string input);
	bool setAge(int input);

	friend ostream &operator<<( ostream &output, const Student &s) {
			output << "Student info: ";
			output << s.firstName;
			output << ", " << s.lastName;
			output << ", " << s.age;
			output << "\n";
	        return output;            
}

private:
	// Private data
	string firstName;
	string lastName;
	int age;
};


#endif /* STUDENT_HPP_ */
