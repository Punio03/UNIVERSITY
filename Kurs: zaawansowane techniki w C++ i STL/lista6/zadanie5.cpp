//
// Created by Jakub Malczak on 21/11/2023.
//
#include <iostream>
#include <algorithm>
using namespace std;

void printAllPermutations(string s) {
    sort(s.begin(), s.end());
    do {
        cout << s << endl;
    } while (next_permutation(s.begin(), s.end()));
}

int main() {
    string s = "TKDKE";
    printAllPermutations(s);
}