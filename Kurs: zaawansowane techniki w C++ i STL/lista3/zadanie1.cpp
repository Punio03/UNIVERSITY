//
// Created by Jakub Malczak on 20/10/2023.
//
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "Minimum typu long long int: " << numeric_limits<long long int>::min() << endl;
    cout << "Maksimum typu long long int: " << numeric_limits<long long int>::max() << endl;
    cout << "Te liczby zapisywane są na: " << numeric_limits<long long int>::digits+1 << " bitach" << endl;
    cout << "Te liczby będą miały: " << numeric_limits<long long int>::digits10+1 << " cyfr dziesiętnych!" << endl;
}