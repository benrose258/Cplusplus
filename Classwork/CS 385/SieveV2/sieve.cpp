/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Ben Rose
 * Date        : February 8, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Version	   : 2.0
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve(); // Initialized Sieve function
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
    	cout << "Number of primes found: " << num_primes() << endl;
    	cout << "Primes up to " << limit_ << ":" << endl;
    	if (count_num_primes() <= primes_per_row) { // If the number of primes does not exceed the allowed primes per row
    		int primes_counter = 0;
    		int spaces = 2; // Correcting for spacing on single lines when switching from 7 to 11
    		for (int i = 2; i <= limit_; i++) {
    			if (is_prime_[i] == true) {
    				if (primes_counter < 4) { // If we are within the first four primes
    					primes_counter++; // Increment primes counter
    					if (primes_counter == 4) { // We are at 7 (the fourth prime)
    						spaces++; // Increase spaces
    					}
    				}
    				cout << i << setw(spaces);
    			}
    		}
    	} else { // The number of primes exceeds primes_per_row
    		int primes_counter = primes_per_row; // Counting down from the max
    		for (int i = 2; i <= limit_; i++) {
    			const int width = max_prime_width + 1; // Spaces, each number will have spaces-num_digits spaces.
    			if (is_prime_[i] == true) {
    				if (primes_counter == primes_per_row) { // We are at the front
    					primes_counter--;
    					int this_width = width - num_digits(is_prime_[i]);
    					cout << setw(this_width) << i;
    				} else if (primes_counter == 1) { // We are at the end
    					primes_counter = primes_per_row;
    					cout << setw(width) << i << endl;
    				} else { // We are neither at the front nor the end
    					cout << setw(width) << i << setw(width);
    					primes_counter--;
    				}
    			}
    		}
    	}
    }

private:
    bool * const is_prime_; // is_prime_ is an array of boolean values
    const int limit_; // the limit
    int num_primes_, max_prime_;
    int max_prime_width;// = num_digits(max_prime_);
    int primes_per_row;// = 80 / (max_prime_width + 1);



    int count_num_primes() const {
    	int counter = 0;
    	 // Number of primes is initially set to zero // Size of is_prime_ array, description below
    	for (int i = 2; i <= limit_; i++) { // While we are in the array, which starts at the index 2 and ends at array_size
    		if (is_prime_[i] == true) { // If, after the sieve function has worked through the array, the value is prime
    			counter++;
    		}
    	}
    	return counter;
    }

    int num_digits(int num) const {
    	return num < 1 ? 0 : 1 + num_digits(num/10);
    }

    void set_max_prime() { // Sets the max prime by looking in the opposite direction at the boolean array
		for (int i = limit_; i >= 2; i--) { // While we are in the array
			if (is_prime_[i] == true) { // If, after the sieve function has worked through the array, the value is prime
				max_prime_ = i;
				break;
			}
	    }
    }

    void set_max_prime_width() {
    	max_prime_width = num_digits(max_prime_);
    }

    void set_primes_per_row() {
        primes_per_row = 80 / (max_prime_width + 1);
    }

    void sieve() {
    	for (int i = 2; i <= limit_; i++) { // Initializes array, sets values from 2 to
    		is_prime_[i] = true;
    	}

    	for (int index = 2; index <= floor(sqrt(limit_)); index++) { // Stop when we reach the floor (integer rounding) of the square root of the limit
    		if (is_prime_[index] == true) {
    			for (int j = index * index; j <= limit_; j += index) {
    				is_prime_[j] = false;
    			}
    		}
       	}
    	num_primes_ = count_num_primes();
    	set_max_prime();
    	max_prime_width = num_digits(max_prime_);
    	primes_per_row = 80 / (max_prime_width + 1);
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    cout << endl;
    PrimesSieve sieve(limit); // Sieve object, taking in limit
    sieve.display_primes();
    return 0;
}
