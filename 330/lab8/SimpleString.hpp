#include <string>
#include <iostream>

class SimpleString {
	public:
		SimpleString();
   		SimpleString(std::string str);

		void setString(std::string str);	
		std::string getString();    
    
	    // All operator overloading member functions.
		SimpleString& operator=(const SimpleString &);
		SimpleString operator+(const SimpleString &);

		// Pre-increment and pre-decrement. 
   		SimpleString& operator++();
   		SimpleString operator++(int);
   		SimpleString& operator--();

   		// Operator overloading friend functions.
   		friend std::ostream& operator<<(std::ostream& os, const SimpleString& s);
   		friend std::istream& operator>>(std::istream& is, SimpleString& s);

	private:
	 	std::string input;
};



