//
// Created by Jakub Malczak on 12/10/2023.
//
#include <iostream>
using namespace std;

auto lucas(uint64_t n) {
    if (n == 0) return (uint64_t)2;
    if (n == 1) return (uint64_t)1;
    return lucas(n-1)+ lucas(n-2);
}

int main() {
    uint64_t n;
    cin >> n;
    cout << lucas(n);
}