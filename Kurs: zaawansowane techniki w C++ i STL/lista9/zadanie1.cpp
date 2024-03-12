//
// Created by Jakub Malczak on 14/12/2023.
//
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

// 7.0 4.0 -2.0

int main() {
    auto begin = istream_iterator<double>(cin);
    auto end = istream_iterator<double>();
    vector<double> numbers(begin, end);

    double average = accumulate(numbers.begin(), numbers.end(), 0) / numbers.size();

    double deviation = 0;
    for_each(numbers.begin(), numbers.end(), [&](double number) {
        deviation += pow(number-average, 2);
    });
    deviation = sqrt(deviation / numbers.size());

    cout << fixed << setprecision(3);
    cout << "Średnia arytmetyczna: " << average << endl;
    cout << "Odchylenie standardowe: " << deviation << endl;
}