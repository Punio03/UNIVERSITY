//
// Created by Jakub Malczak on 20/10/2023.
//
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "Najbliższa 0 (zdenormalizowana) wartość dodatnia dla typu float to: " << numeric_limits<float>::denorm_min() << endl;
    cout << "Najbliższa 0 (zdenormalizowana) wartość dodatnia dla typu double to: " << numeric_limits<double>::denorm_min() << endl;
    cout << "Najbliższa 0 wartość dodatnia dla typu float to: " << numeric_limits<float>::min() << endl;
    cout << "Najbliższa 0 wartość dodatnia dla typu double to: " << numeric_limits<double>::min() << endl;
    cout << "Maksymalna wartość dla typu float to: " << numeric_limits<float>::max() << endl;
    cout << "Maksymalna wartość dla typu double to: " << numeric_limits<double>::max() << endl;
    cout << "Różnica pomiędzy 1 a najmniejszą liczbą > 1 w typie float to: " << numeric_limits<float>::epsilon() << endl;
    cout << "Różnica pomiędzy 1 a najmniejszą liczbą > 1 w typie double to: " << numeric_limits<double>::epsilon() << endl;
}