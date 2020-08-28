/*
 * Generates CWIDs (Stevens Campus-Wide IDs) based on input.
 * Will generate 10xx0000 - 10xx9999, where xx is user input.
 */

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int cwid_gen(int input) {
	int const origin = 10000000 + (input * 10000);
	for (int i = 0; i < 10000; i++) {
		cout << origin + i << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int i;
	istringstream iss;
	if (argc != 2) { // If we have less than or more than two arguments
		cerr << "Usage: ./cwid_gen <integer between 0 and 99>";
		return 1;
	}
	iss.str(argv[1]);
	if (!(iss >> i) || i < 0 || i > 99) { // If argv[1] is not an integer or argv[1] is an integer less than 1
		cerr << "Error: CWID variation must be an integer between 0 and 99." << endl;
		return 1;
	}
	cwid_gen(i);
	return 0;
}
