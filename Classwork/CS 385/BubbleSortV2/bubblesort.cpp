/*
 * bubblesort.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: Ben Rose
 * Created for: Lab 5, Elementary Sorting Algorithms
 *
 * Version: 2.0
 */

#include <iostream>
#include <cmath>
#include <array>
#include <string>

using namespace std;

// My own coded array thing. Used borowski's as a model to finish it after I realized he had one.

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

static void swap(int array[], const int a, const int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void bubble_sort(int array[], const int length) {
    int len = length;
    while (len > 0) {
        int n = 0;
        for (int i = 1; i < len; ++i) {
            if (array[i - 1] > array[i]) {
                swap(array, i - 1, i);
                n = i;
            }
        }
        len = n;
        array_to_string(array, length); // This line does the intermediate printing
        cout << endl;
    }
}

int main(int argc, char* const argv[]) {
//	cout << "hi" << endl;
	// 78 15 23 2 97 85
	int lab5[6] = { 78 , 15 , 23 , 2 , 97 , 85 };
//	cout << lab5;
//	array_to_string(lab5, 6);
//	cout << endl;
	bubble_sort(lab5, 6);
//	array_to_string(lab5, 6);
	return 0;
}
