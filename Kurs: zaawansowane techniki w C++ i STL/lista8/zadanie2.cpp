//
// Created by Jakub Malczak on 07/12/2023.
//
#include <iostream>
#include <regex>
using namespace std;

/*
15-09-1999
05-12-2018
28-02-2021
03/07/1917
6-3-1945
29-02-2022
*/

int main() {
    regex pattern("^(([01][0-9]|2[0-8])-(0[1-9]|1[0-2])|(29|30)-(0[13-9]|1[0-2])|(31)-(0[13578]|1[02]))-\\d{4}$");
    string s;

    cout << "Wprowadź datę do sprawdzenia: ";
    while (getline(cin, s)) {
        if (regex_match(s, pattern)) {
            cout << "Prawidłowy format daty." << endl;
        } else {
            cout << "Nieprawidłowy format daty." << endl;
        }
        cout << "Wprowadź datę do sprawdzenia: ";
    }
}