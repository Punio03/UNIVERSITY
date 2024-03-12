//
// Created by Jakub Malczak on 01/12/2023.
//
#include <fstream>
#include <random>
#include <functional>
#include <cmath>
using namespace std;

void generateAndSaveData(const string& filename, const function<double()>& distFunction) {
    ofstream file(filename);
    for (int i = 0; i < 1000; i++) {
        double a = distFunction();
        double intpart{};
        double realpart = modf(a, &intpart);
        file << (int)intpart << "," << abs((int)(realpart*1e6)) << "\n";
    }
    file.close();
}

int main() {
    random_device rd;
    mt19937 gen(rd());

    //a
    uniform_real_distribution<> uniformDist(0.0, 1.0);
    generateAndSaveData("/Users/jakubmalczak/CLionProjects/STLtasks/lista7/zadanie2a.csv", [&]() { return uniformDist(gen); });

    //b
    binomial_distribution<> binomialDist(10, 0.5);
    generateAndSaveData("/Users/jakubmalczak/CLionProjects/STLtasks/lista7/zadanie2b.csv", [&]() { return binomialDist(gen); });

    //c
    normal_distribution<> normalDist(10);
    generateAndSaveData("/Users/jakubmalczak/CLionProjects/STLtasks/lista7/zadanie2c.csv", [&]() { return normalDist(gen); });
}
