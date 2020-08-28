/*
 * selectionsort.cpp
 *
 *  Created on: Sep 29, 2018
 *      Author: Ben Rose
 *  Created for: Lab 5, Elementary Sorting Algorithms
 */
#include <iostream>
#include <cmath>
#include <array>
#include <string>

using namespace std;

// For array visualization

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

static void swap(int array[], const int a, const int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void selection_sort(int array[], const int length) {
    for (int i = 0, i_bound = length - 1; i < i_bound; ++i) {
        int min_index = i, min = array[i];
        for (int j = i + 1; j < length; ++j) {
            if (array[j] < min) {
                min_index = j;
                min = array[j];
            }
        }
        if (min_index != i) {
            swap(array, i, min_index);
        }
        array_to_string(array, length);
        cout << endl;
    }
}

int main(int argc, char* const argv[]) {
	int lab5[6] = { 78 , 15 , 23 , 2 , 97 , 85 };
	selection_sort(lab5, 6);
	array_to_string(lab5, 6);
	return 0;
}
