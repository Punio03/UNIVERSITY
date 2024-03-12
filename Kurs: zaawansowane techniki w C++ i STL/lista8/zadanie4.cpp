//
// Created by Jakub Malczak on 07/12/2023.
//
#include <iostream>
#include <regex>
using namespace std;

/*
(12+3I)
(7.4-0.5i)
(2+0.01i)
3+4I
(3,14-2,72i)
(5.7i)
*/

int main() {
    regex pattern("^[(]-?\\d+([.]\\d+)?[+-]\\d+([.]\\d+)?[iI][)]$");
    string s;

    cout << "Wprowadź liczbę zespoloną do sprawdzenia: ";
    while (getline(cin, s)) {
        if (regex_match(s, pattern)) {
            cout << "Prawidłowy format liczby zespolonej." << endl;
        } else {
            cout << "Nieprawidłowy format liczby zespolonej." << endl;
        }
        cout << "Wprowadź liczbę zespoloną do sprawdzenia: ";
    }
}