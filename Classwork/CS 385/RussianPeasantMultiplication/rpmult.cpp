/*******************************************************************************
 * Name          : rpmult.cpp
 * Author        : Ben Rose
 * Version       : 1.0
 * Date          : March 29, 2019
 * Description   : Performs Russian Peasant Multiplication.
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n) {
	if (m < n) { // If m < n, then switch the values of m and n, as n must always be the smaller of the two.
		int temp = n; // Temporary variable to store n's value in, since we must replace n by m.
		n = m;
		m = temp;
	}
	// left shift (<<): multiply by 2, right shift (>>): divide by 2

	unsigned long product = 0; // Initialize the product
	unsigned long long_m = m; // Give m the ability to grow past the bounds of an integer.

	while (n > 0) { // While n is greater than zero, continue creating the product
		// if (n % 2 != 0) { // If the remainder of n/2 is not 0, indicating that n is odd
		if (n != ((n >> 1) << 1)) { // If the remainder of n/2 is not 0, indicating that n is odd, or rather if n/2 * 2 is not equal to the original n
			product += long_m; // Add the current value of long_m to the product
		}
		n = n >> 1; // Divide n by 2
		long_m = long_m << 1; // Multiply long_m by 2
	}
    return product;
}

int main(int argc, char* const argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
        return 1;
    }

    int m, n;
    istringstream iss;

    iss.str(argv[1]);
    if ( !(iss >> m) || m < 0 ) {
        cerr << "Error: The first argument is not a valid nonnegative integer."
             << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[2]);
    if ( !(iss >> n) || n < 0 ) {
        cerr << "Error: The second argument is not a valid nonnegative integer."
             << endl;
        return 1;
    }

    // Output the sum in the specified format
    cout << m << " x " << n << " = " << russian_peasant_multiplication(m, n);

    return 0;
}
