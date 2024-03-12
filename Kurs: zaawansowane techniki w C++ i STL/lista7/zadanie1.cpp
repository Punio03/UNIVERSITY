//
// Created by Jakub Malczak on 01/12/2023.
//
#include <iostream>
#include <random>
#include <cmath>
using namespace std;

template <typename T>
class custom_distribution {
    T a;
    T b;
public:
    custom_distribution(T a, T b) : a(a), b(b) {}

    T operator()(mt19937& gen) {
        uniform_real_distribution<> dist(0.0,1.0);
        double x = dist(gen);
        return a + 0.5 * (b - a) + 0.5 * (b - a) * cos(2 * x * M_PI);
    }
};

int main() {
    std::random_device rd;
    std::mt19937 gen;
    custom_distribution<int> dist(5,10);

    vector<int> frequency(5, 0);
    for (int i = 0; i < 1000; i++) frequency[dist(gen) - 5]++;
    for (int i = 0; i < 5; i++) {
        cout << i+5 << " : " << frequency[i] << endl;
    }
}
