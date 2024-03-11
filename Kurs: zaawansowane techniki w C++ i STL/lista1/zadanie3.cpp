//
// Created by Jakub Malczak on 12/10/2023.
//
#include <iostream>
#include <unordered_set>
using namespace std;

using USS = unordered_set<string>;

int main() {
    USS a{"kot", "pies", "lew", "tygrys"};
    for(const auto& b : a) cout << b << " ";
}