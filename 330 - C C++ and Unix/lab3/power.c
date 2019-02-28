/* Lab 3 static array test 
   Andrew Letz
*/

#include "power.h"

int power(double a, double b) {
	int result = a;
	int i;
    for (i = 1; i < b; i++) {
		result = result * a;
	}
	return result;
}