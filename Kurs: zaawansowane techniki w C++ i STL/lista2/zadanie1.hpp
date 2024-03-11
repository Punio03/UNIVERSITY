//
// Created by Jakub Malczak on 13/10/2023.
//

#ifndef STLTASKS_ZADANIE1_HPP
#define STLTASKS_ZADANIE1_HPP
#include <iostream>
#include <memory>
#include <random>
using namespace std;

class licznik {
private:
    uint64_t wartosc{1};
public:
    virtual ~licznik() { cerr << wartosc << " "; }
    void zwieksz(uint64_t ile) { wartosc += ile; }
};

random_device device;
mt19937 engine(device());

void modyfikuj(unique_ptr<licznik[]>& tab, int n, int m, int i) {
    if (i > m) return;
    uniform_int_distribution<> dist(0, n-1);
    for (int j = 0; j < n/10; j++) tab[dist(engine)].zwieksz(i);
    modyfikuj(tab, n, m, i+1);
}

#endif //STLTASKS_ZADANIE1_HPP
