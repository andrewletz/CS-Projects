#include “SimpleString.hpp”

SimpleString::SimpleString() {
    this->input = “Default value”;
}

SimpleString::SimpleString(std::string s) {
    this->input = s;
}

SimpleString::setString(std::string str) {
	this->input = str;
}

std::string SimpleString::getString() {
	return this->input;
}
    
SimpleString& SimpleString::operator=(const SimpleString &) {
	
}

SimpleString SimpleString::operator+(const SimpleString &) {

}

SimpleString& SimpleString::operator++() {
	this->input.push_back('*');
}

SimpleString& SimpleString::operator--() {

}

friend std::ostream& SimpleString::operator<<(std::ostream& os, const SimpleString& s) {

}

friend std::istream& SimpleString::operator>>(std::istream& is, SimpleString& s) {

}





