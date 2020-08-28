/*******************************************************************************
 * Name        : quicksort.cpp
 * Author      : Ben Rose
 * Date        : March 15, 2019
 * Description : Implements quicksort with Lomuto partitioning.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Upgraded vector_to_string method, Version 2.0
void vector_to_string(vector<int> vec) { // to_string method to display vector content
	cout << "[";
//	printf("[");
//	const int vec_size = vec.size();
	int temp_calc = vec.size();
//	const int vector_size = vec.size();
	const unsigned int limiter = temp_calc - 1;
	for (unsigned int i = 0; i < vec.size(); i++) {
		cout << vec[i];
		(limiter != i) ? cout << ", " : cout << "";
//		if (limiter != i) {
//			cout << vec[i] << ", ";
//		} else {
//			cout << vec[i];
//		}
	}
	cout << "]";
}

/*
 * Swaps array[a] with array[b], with the assumption that we do not go outside of the array.
 */
static void swap(int array[], const int a, const int b) {
	int temp = array[b]; // Save the value of array[b] in a temporary variable in preparation for it being overwritten.
	array[b] = array[a]; // Overwrite the value of array[b] with the value of array[a].
	array[a] = temp; // Finally, write the previous value of array[b] to its place in array[a].
}

static int lomuto_partition(int array[], const int left, const int right) {
	int pivot = array[left];
	int s = left; // s marks the index of the LAST element of the segment of elements greater than or equal to pivot.
	for (int i = left + 1; i <= right; i++) { // i marks the first element after the segment where all elements are greater than or equal to the pivot.
		if (array[i] <= pivot) { // If array[i] <= the pivot, then we expand the segment of elements > the pivot.
			s++;
			swap(array, s, i);
		}

	}
	swap(array, left, s);
	return s;
}

/*
 * Performs the quicksort operations to sort the array.
 */
static void quicksort_helper(int array[], int left, int right) {
	if (left < right) {
		int partition = lomuto_partition(array, left, right);
		quicksort_helper(array, left, partition - 1);
		quicksort_helper(array, partition + 1, right);
	}
}

/**
 * Implements quicksort.
 * Calls the helper function that takes in left and right parameters.
 **/
void quicksort(int array[], int length) {
    quicksort_helper(array, 0, length - 1);
}

int main(int argc, char *argv[]) {
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
    if (values.empty()) {
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }
    quicksort(&values[0], values.size());
    vector_to_string(values);
    return 0;
}
