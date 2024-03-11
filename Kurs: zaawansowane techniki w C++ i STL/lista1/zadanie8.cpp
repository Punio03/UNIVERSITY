//
// Created by Jakub Malczak on 12/10/2023.
//
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

struct osoba{
    string nazwisko, imie;
    int rok_urodzenia;
    osoba(string n, string i, int r) : nazwisko(std::move(n)), imie(std::move(i)), rok_urodzenia(r) {}
    friend bool operator<(osoba x, osoba y) {
        return tie(x.nazwisko,x.imie, x.rok_urodzenia) < tie(y.nazwisko, y.imie, y.rok_urodzenia);
    }
};

int main() {
    deque<osoba> osoby {
            {"Malczak", "Jakub", 2003},
            {"Nowak", "Piotr", 1990},
            {"Kowalski", "Adam", 1985},
            {"Nowak", "Jan", 1995},
            {"Kowalski", "Włodzimierz", 1980},
            {"Adamska", "Karolina", 2000}
    };
    sort(osoby.begin(),osoby.end());
    for (const auto& o: osoby) {
        cout << o.nazwisko << " " << o.imie << " " << o.rok_urodzenia << endl;
    }
}