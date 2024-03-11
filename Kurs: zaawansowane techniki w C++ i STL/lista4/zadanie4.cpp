//
// Created by Jakub Malczak on 31/10/2023.
//
#include <iostream>
#include <functional>
using namespace std;

int main() {
    const function<int(int,int)> binomial = [&binomial] (int n, int k) {
        return n == k || k == 0 ? 1 : binomial(n - 1, k - 1) + binomial(n - 1, k);
    };

    vector<pair<int,int>> values({{4,2},{6,3},{8,4},{9,5},{-10,3}});
    for (const auto& [n,k] : values) cout << "Binomial(" << n << "," << k << ") = " << binomial(n, k) << endl;
}