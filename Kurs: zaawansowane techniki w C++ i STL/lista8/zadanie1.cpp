//
// Created by Jakub Malczak on 07/12/2023.
//
#include <iostream>
#include <regex>
using namespace std;

/*
14:17
09:15
23:37:08
14.16
19:5
21:32:07,10
*/

int main() {
    regex pattern("^([01][0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$");
    string s;

    cout << "Wprowadź godzinę do sprawdzenia: ";
    while (getline(cin, s)) {
        if (regex_match(s, pattern)) {
            cout << "Prawidłowy format godziny." << endl;
        } else {
            cout << "Nieprawidłowy format godziny." << endl;
        }
        cout << "Wprowadź godzinę do sprawdzenia: ";
    }
}
