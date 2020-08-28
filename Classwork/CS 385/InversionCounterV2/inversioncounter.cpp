/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Ben Rose
 * Version     : 2.0
 * Date        : March 26, 2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

// Visualizing an array
void array_to_string(int my_array[], const int array_size) {
	cout << "{ ";
	int temp_calc = array_size;
	const int limiter = temp_calc - 1;
	for (int i = 0; i < array_size; i++) {
		cout << my_array[i];
		(limiter != i) ? cout << " | " : cout << "";
	}
	cout <<  " }";
}

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */

long count_inversions_slow(int array[], int length) {
	// Uses nested for loops
	long counter = 0;
	for (int i = 0; i < length; i++) { // For each index in the array
		int temp = array[i]; // For the current element in the array
		for (int j = i; j < length; j++) { // For the other elements in the array
			if (temp > array[j]) {
				counter++;
			}
		}
	}
	return counter;
}

// MergeSort algorithm, used to count the number of inversions. Version 2.0
static long mergesort(int array[], int scratch[], int low, int high) {
	int mid;
	long inversions = 0;
	if (low < high) {
		mid = low + (high - low) / 2;
		inversions += mergesort(array, scratch, low, mid); // mergesort the left half of the array and add the left half's inversions to the total
		inversions += mergesort(array, scratch, mid + 1, high); // mergesort the right half of the array and add the left half's inversions to the total
		// Merge the left and right halves of the array and count the number of inversions
		int L = low;
		int H = mid + 1;
		for (int k = low; k <= high; k++) {
			if (L <= mid && (H > high || array[L] <= array[H])) {
				scratch[k] = array[L];
				L++;
			} else {
				scratch[k] = array[H];
				H++;
				inversions++; // Because array[L] must be greater than array[H], giving us an inversion.
				inversions += mid - L;
			}
		}
		for (int k = low; k <= high; k++) {
			array[k] = scratch[k];
		}
	}
	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	int* scratch = new int[length]; // Make the scratch work array, of the same length as the array
	long inversions = mergesort(array, scratch, 0, length-1); // Call mergesort to get the number of inversions
	delete [] scratch; // Delete the scratch array from memory
	return inversions; // Return the inversions
}

int main(int argc, char *argv[]) {
	if (argc > 2) { // If we have more than two arguments
		cerr << "Usage: ./inversioncounter [slow]"; // Print the usage message
		return 1; // Return
	}

	bool slow = false; // If we are using the slow option, originally set to false.

	if (argc == 2) { // If we have two arguments
		istringstream issError(argv[1]); // Take in the second argument variable to check if it is indeed "slow"
		if (issError.str() != "slow") { // If the second argument variable isn't slow
			cerr << "Error: Unrecognized option '" << issError.str() << "'."; // Print error message with the invalid option
			return 1; // Return
		}
		slow = true; // Else, we're using the slow option, so set that boolean to true.
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int values_size = values.size(); // Size of the Values array, used to reduce times computing values.size

    if (values_size == 0) { // If we have no input
    	cerr << "Error: Sequence of integers not received."; // Output error
    	return 1; // Return
    }

    cout << "Number of inversions: ";

    // If the user has specified the slow method (see "slow" boolean above), then count_inversions_slow. Else, count_inversions_fast.
    long result = slow ? count_inversions_slow(&values[0], values_size) : count_inversions_fast(&values[0], values_size);

    cout << result;

    return 0;
}
