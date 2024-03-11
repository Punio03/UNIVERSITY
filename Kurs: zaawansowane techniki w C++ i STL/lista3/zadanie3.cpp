//
// Created by Jakub Malczak on 21/10/2023.
//
#include <iostream>
#include <ratio>
using namespace std;

template<int N>
struct Harmonic;

template<>
struct Harmonic<1> {
    using type = ratio<1, 1>;
};

template<int N>
struct Harmonic {
    using type = ratio_add<typename Harmonic<N-1>::type, ratio<1, N>>;
};


int main() {
    Harmonic<46>::type s;
    cout << s.num << "/" << s.den;
}


