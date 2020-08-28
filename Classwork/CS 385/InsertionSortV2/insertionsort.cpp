/*
 * insertionsort.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: Ben Rose
 *  Created for: Lab 5, Elementary Sorting Algorithms
 *  Version: 2.0
 */

#include <iostream>
#include <cmath>
#include <array>
#include <string>

using namespace std;

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

void insertion_sort(int array[], const int length) {
    for (int i = 1; i < length; ++i) {
        int k, current = array[i];
        for (k = i - 1; k >= 0 && array[k] > current; --k) {
            array[k + 1] = array[k];
        }
        array[k + 1] = current;
        array_to_string(array, length);
        cout << endl;
    }
}

int main(int argc, char* const argv[]) {
	int lab5[6] = { 78 , 15 , 23 , 2 , 97 , 85 };
	insertion_sort(lab5, 6);
	array_to_string(lab5, 6);
	return 0;
}
