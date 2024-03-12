//
// Created by Jakub Malczak on 07/12/2023.
//
#include <iostream>
#include <regex>
using namespace std;

/*
Wroclaw
Bielsko-Biala
Tarnowskie Gory
WARSZAWA
Zle mieso
Zimna-Wodka-07
*/

int main() {
    regex pattern("^([A-Z][a-z]+)((\\s+|-)[A-Z][a-z]+)*$");
    string s;

    cout << "Wprowadź miejscowość do sprawdzenia: ";
    while (getline(cin, s)) {
        if (regex_match(s, pattern)) {
            cout << "Prawidłowy format miejscowości." << endl;
        } else {
            cout << "Nieprawidłowy format miejscowości." << endl;
        }
        cout << "Wprowadź miejscowość do sprawdzenia: ";
    }
}