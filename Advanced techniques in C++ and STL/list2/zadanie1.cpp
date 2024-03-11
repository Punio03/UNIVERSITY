//
// Created by Jakub Malczak on 13/10/2023.
//
#include "zadanie1.hpp"

int main() {
    const int n{40}, m{20};
    unique_ptr<licznik[]> tablica = make_unique<licznik[]>(n);
    modyfikuj(tablica, n, m, 1);
}