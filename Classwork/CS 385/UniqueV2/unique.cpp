/*******************************************************************************
* Name          : unique.cpp
* Author        : Ben Rose
* Date          : February 19, 2019
* Description   : Determining uniqueness of chars with int as bit vector.
* Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
* Version		    : 2.0
******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) { // Determines if all characters are lowercase letters
	int size = s.length(); // Size of the input string
	bool all_lower = true; // If we have all lowercase characters, initially true
	for (int i = 0; i < size; i++) { // Iterating over the string
		char c = s[i]; // Current character in the string
		if (!isalpha(c) || !islower(c)) { // If the character isn't in the alphabet or the character isn't lowercase
			all_lower = false; // Set all_lowercase to false
			break; // Break the loop
		}
	}
	return all_lower; // Return whether the string contains only lowercase letters
}

bool all_unique_letters(const string &s) { // Determines if all letters are unique
	unsigned int bitvector = 0; // Tracking what characters we have and have not seen
	int size = s.length(); // Size of input string
	bool all_unique = true; // If all characters are unique, initially true
	for (int i = 0; i < size; i++) { // Iterating over the string
		int shift = s[i] - 'a'; // Bitshifting
		if (((1 << shift) & bitvector) > 0) { // If we have seen the character before (if not, the and statement would return false)
			all_unique = false; // All characters are not unique, so all_unique is now false
		}
		bitvector = (bitvector | (1 << shift)); // Set bitvector to show that we have seen the character
	}
	return all_unique; // Return if all characters are unique
}

int main(int argc, char * const argv[]) {
	if (argc != 2) { // If we have an incorrect input
		cerr << "Usage: " << argv[0] << " <string>"; // Output usage message
		return 1; // Exit, returning unsuccessful execution
	}
	if (!is_all_lowercase(argv[1])) { // If the input string is not all lowercase
		cerr << "Error: String must contain only lowercase letters."; // Output error message
		return 1; // Return exit code 1 (failure)
	}
	if (!all_unique_letters(argv[1])) { // If not all characters in the string are unique
		cerr << "Duplicate letters found."; // Output error message
		return 1; // Return exit code 1
	}
	else { // Otherwise
		cout << "All letters are unique."; // All letters are unique.
		return 0; // Return exit code 0 (success)
	}
}
