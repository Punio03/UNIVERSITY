//
// Created by Jakub Malczak on 12/10/2023.
//
#include <iostream>
using namespace std;

enum class imie : uint16_t { Kuba, Piotrek, Julka, Ala};
void print(const string& komunikat, imie i) {
    switch (i) {
        case imie::Piotrek: cout << "Piotrek "; break;
        case imie::Kuba: cout << "Kuba "; break;
        case imie::Julka: cout << "Julka "; break;
        case imie::Ala: cout << "Ala "; break;
    }
    cout << komunikat;
}

int main() {
    print("umyj naczynia!", imie::Julka);
}