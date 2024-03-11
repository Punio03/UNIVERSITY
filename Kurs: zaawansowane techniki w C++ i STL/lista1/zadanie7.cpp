//
// Created by Jakub Malczak on 12/10/2023.
//
#include <iostream>
using namespace std;

int main() {
    string date;
    cin >> date;
    cout << stoi(date.substr(0, date.find('.'))) << " ";
    date = date.substr(date.find('.')+1);
    switch (int month{stoi(date.substr(0, date.find('.')))}; month) {
        case 1: cout << "styczeń"; break;
        case 2: cout << "luty"; break;
        case 3: cout << "marzec"; break;
        case 4: cout << "kwiecień"; break;
        case 5: cout << "maj"; break;
        case 6: cout << "czerwiec"; break;
        case 7: cout << "lipiec"; break;
        case 8: cout << "sierpień"; break;
        case 9: cout << "wrzesień"; break;
        case 10: cout << "październik"; break;
        case 11: cout << "listopad"; break;
        case 12: cout << "grudzień"; break;
    }
    cout << " " << date.substr(date.find('.')+1);
}