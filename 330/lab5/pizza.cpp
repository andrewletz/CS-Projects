/*
 * pizza.cpp
 *
 * Author: Andrew Letz
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza {

	public:
		Pizza(vector<string> &v) {
			this->toppings = v;
			cout << "You made your own pizza with " << v.size() << " toppings\n"; 
		}

		Pizza() {
			vector<string> defaultToppings;
			defaultToppings.push_back("marinara");
			defaultToppings.push_back("cheese");
			this->toppings = defaultToppings;
			cout << "You got a boring cheese pizza\n"; 
		}

		friend ostream &operator<<( ostream &output, const Pizza &p ) {
			output << "Pizza's toppings are: ";
			for (int i = 0; i < p.toppings.size(); i++) {
				output << p.toppings[i] << " ";
			}
			output << "\n";
	        return output;            
      	}

      	friend Pizza &operator+( const Pizza &p, const Pizza &p2 ) {
			// to be filled in         
      	}
	
	private:
		vector<string> toppings;

};

int main() {
	Pizza p1;
	vector<string> gloriousToppings;
	gloriousToppings.push_back("pepperoni");
	gloriousToppings.push_back("black olives");
	gloriousToppings.push_back("bacon");
	gloriousToppings.push_back("pepperonchinis");
	Pizza p2(gloriousToppings);
	cout << p1;
	cout << p2;
}