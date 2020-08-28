/*******************************************************************************
* Name          : gcd.cpp
* Author        : Ben Rose
* Date          : January 25, 2019
* Description   : Finding the Greatest Common Denominator
* Pledge        : I pledge my honor that I have abided by the Stevens Honor System
* Version		: 2.0
******************************************************************************/

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int gcd_iterative(int m, int n) {
	while (n != 0) {
		int denom = m % n;
		m = n;
		n = denom;
	}
	return m;
}

int gcd_recursive(int m, int n) {
	if (m == 0 || n == 0) {
		return m;
	}
	if (m % n == 0) {
		return n;
	} else {
		return gcd_recursive(n, m % n);
	}
}

int main(int argc, char* const argv[]) {
	int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }
    /*
     * The GCD of m and -m as well as n and -n would come out
     * as the same, however the GCD cannot be negative, so x and y
     * are the absolute value versions of m and n.
     */
    int x = abs(m); // Setting m to be positive in calculations
    int y = abs(n); // Setting n to be positive in calculations

    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(x, y) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(x, y) << endl;
//    cout << "m is " << m << endl;
//    cout << "n is " << n << endl;
//    cout << "iterative_gcd(" << m << ", " << n << ") is " << min(m, n) << endl;
    return 0;
}
