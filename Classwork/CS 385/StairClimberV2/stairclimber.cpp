/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Ben Rose
 * Date        : February 25, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Version	   : 2.0
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector< vector<int> > ways;
	if (num_stairs <= 0) {
		vector<int> empty;
		ways.push_back(empty);
	} else {
		for (int i = 1; i <= 3; i++) { // For climbing up one, two, or three stairs
			if (num_stairs >= i) {
				vector< vector<int> > result = get_ways(num_stairs-i);
				for (auto &r : result) {
					r.insert(r.begin(), i); // Insert item at the front of r
					ways.push_back(r); // Push back to ways
				}
			}
		}
	}
	return ways;
}

// Upgraded Vector_to_String method, Version 2.0
void vector_to_string(vector<int> vec) { // to_string method to display vector content
	cout << "[";
	int temp_calc = vec.size();
	const unsigned int limiter = temp_calc - 1;
	for (unsigned int i = 0; i < vec.size(); i++) {
		cout << vec[i];
		(limiter != i) ? cout << ", " : cout << "";
	}
	cout << "]";
}

int num_digits(int num) {
	int counter = 0;
	while (num >= 1) { // While the num is greater than 1
		counter++; // Increase the digits
		num = num/10; // Divide num by 10
	}
	return counter; // Return number of digits
}

void display_ways(const vector< vector<int> > &ways) {
    // Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int width = num_digits(ways.size()); // Width of the largest end number
	if (ways.size() == 1) { // If there is only one stair, the sentence is singular.
		// Ways is the vector of different ways to climb the stairs, so the
		// number of ways to climb the stairs is equal to the size of the vector.
		// ways[0] represents climbing up each stair one at a time, so by definition
		// ways[0] is how many stairs you climb if you climb one at a time, which is
		// how many stairs there are.
		cout << ways.size() << " way to climb " << ways[0].size() << " stair." << "\n";
	} else { // Otherwise, you're climbing a plural number of stairs.
		cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << "\n";
	}
	for (unsigned int i = 0; i < ways.size(); i++) { // Begin iterating over all of the ways in "ways"
		cout << setw(width) << i + 1 << ". ";
		vector_to_string(ways[i]);
		if (i + 1 < ways.size()) {
			cout << "\n";
		}
	}
}

int main(int argc, char * const argv[]) {
	cin.tie(NULL); // Break the ties between cin and the output stream, speeding up performance.
	ios_base::sync_with_stdio(false); // Break the synchronization between C and C++ in regards to stdio, which speeds up the program.

	int i;
	istringstream iss;
	if (argc != 2) { // If we have less than or more than two arguments
		cerr << "Usage: ./stairclimber <number of stairs>";
		return 1;
	}
	iss.str(argv[1]);
	if (!(iss >> i) || i < 1) { // If argv[1] is not an integer or argv[1] is an integer less than 1
		cerr << "Error: Number of stairs must be a positive integer.";
		return 1;
	}
	display_ways(get_ways(i)); // Otherwise, display the different ways.
	return 0;
}
