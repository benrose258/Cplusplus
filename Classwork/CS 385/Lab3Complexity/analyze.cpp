/*
 * analyze.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: Ben Rose
 */

#include <iostream>

using namespace std;

void function1(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += 2) {
            cout << "*";
        }
    }
}


void function2(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        count++;
    }
    cout << count;
}


void function3(int n) {
    int count = 0;
        for (int k = 1; k <= n; k *= 2) {
            count++;
    }
    cout << count;
}


void function4(int n) {
    int count = 0;
    for (int i = n/2; i <= n; i++) {
        for (int j = 1; j <= n; j *= 2) {
            for (int k = 1; k <= n; k *= 2) {
                count++;
            }
        }
    }
    cout << count;
}


void function5(int n) {
    if (n % 2 == 0) {
        return;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << "*";
            break;
        }
    }
}


void function6(int n) {
    int count = 0;
    for (int i = 1; i <= n/2; i++) {
        for (int j = 1; j <= n/3; j++) {
            for (int k = 1; k <= n/4; k++) {
                count++;
            }
        }
    }
    cout << count;
}


void function7(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j += i) {
            cout << "*";
        }
    }
}


void function8(int n) {
    int i = 1, s = 1;
    while (s <= n) {
        i++;
        s += i;
        cout << "*";
    }
}

int main() {
	int n = 30;
	function8(n);
}
