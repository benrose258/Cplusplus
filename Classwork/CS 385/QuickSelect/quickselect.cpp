/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Ben Rose
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : October 28, 2018
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// NOTE: MAXTIME IS TEMPORARILY ALTERED IN TESTQUICKSELECT SHELL SCRIPT, IT SHOULD BE 2.0 SECONDS

void array_to_string(int my_array[], const int array_size) {
	cout << "{ ";
	int temp_calc = array_size;
	const int limiter = temp_calc - 1;
	for (int i = 0; i < array_size; i++) {
		if (limiter != i) {
			cout << my_array[i] << " | ";
		} else {
			cout << my_array[i];
		}
	}
	cout <<  " }";
}

size_t lomuto_partition(int array[], size_t left, size_t right) {
    int pivot = array[left];
    size_t s = left; // s marks the index of the LAST element of the segment of elements greater than or equal to pivot.
    // NOTE: when working on test case 15 (recently), I changed the line: i <= right (which it was) to: i < right. It seems to have
    // fixed that test case, but revert if it breaks the others.
    for (size_t i = left + 1; i <= right; i++) { // i marks the first element after the segment where all elements are greater than or equal to the pivot.
    	if (array[i] <= pivot) { // If array[i] <= the pivot, then we expand the segment of elements > the pivot.
    		s++;
    		swap(array[s], array[i]);
    	}

    }
    swap(array[left], array[s]);
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k, size_t left_displaced, const size_t original_k) {
    // TODO
//	cout << "left = " << left << ", right = " << right << endl;
	size_t s = lomuto_partition(array, left, right);
	if (s == k - 1 + left_displaced) {
		return array[original_k-1];
	} else if (s > (left + k - 1)) {
//		cout << endl << "IN ELSE IF" << endl;
		return quick_select(array, left, s-1, k, left_displaced, original_k);
	} else {
		return quick_select(array, s + 1, right, k - 1 - s, s + 1, original_k);
	}
}

int quick_select(int array[], const size_t length, size_t k) { // Returns the "k"th smallest element in the array
    return quick_select(array, 0, length - 1, k, 0, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
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

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    int values_size = values.size();
    if (k > values_size) { // If k > the vector's size, then k will exceed the bounds of the vector.
    	string plural = values.size() == 1 ? "" : "s"; // Creates a string "s" if we have more than one value, or nothing otherwise.
    									// In simpler terms, "does values.size() equal 1? If so, the string "plural" == "", otherwise, the string plural == "s"
    	cerr << "Error: Cannot find smallest element " << k << " with only " << values.size() << " value" << plural << ".";
    	return 1;
    }

    // TODO - call the quick_select function and display the result
    int* values_array = new int[values.size()];
    for (int i = 0; i < values_size; i++) {
    	values_array[i] = values[i];
    }
    int result = quick_select(values_array, values_size, k);
    cout << "Smallest element " << k << ": " << result;
    return 0;
}
