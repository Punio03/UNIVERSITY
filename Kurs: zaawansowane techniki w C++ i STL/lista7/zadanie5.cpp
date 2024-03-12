//
// Created by Jakub Malczak on 01/12/2023.
//
#include <complex>
#include <fstream>
#include <iostream>
using namespace std;

complex<double> riemannZeta(const complex<double>& z, int iterations = 1000) {
    complex<double> sum = 0.0;
    for (double n = 1; n <= iterations; n++) {
        sum += pow(1.0 / n, z);
    }
    return sum;
}

complex<double> dirchletSeries(const complex<double>& z, int iterations = 1000) {
    complex<double> res = 1.0 / (z - 1.0);
    complex<double> sum = 0.0;
    for (double n = 1; n <= iterations; n++) {
        sum += n / pow(n + 1.0, z) - (n - z) / pow(n, z);
    }
    res *= sum;
    return res;
}

void calculateAndSaveCriticalZetaValues(double start, double end, double step, int iterations, const string& filename) {
    ofstream file(filename);

    for (double y = start; y <= end; y += step) {
        complex<double> s(0.5, y);
        complex<double> zetaValue = dirchletSeries(s);
        double real = zetaValue.real();
        double img = zetaValue.imag();
        double intpart1{},inpart2{};
        double a1{modf(real,&intpart1)}, a2{modf(img,&inpart2)};

        file << (int)intpart1 << "," << abs((int)(a1*1e6))  << ";" << (int)inpart2 << "," << abs((int)(a2*1e6))  << "\n";
    }

    file.close();
}

int main() {
    int iterations = 1000; // Można dostosować dokładność
    calculateAndSaveCriticalZetaValues(-30.0, 30.0, 0.1, iterations, "/Users/jakubmalczak/CLionProjects/STLtasks/lista7/zadanie5.csv");

    cout << "Wygenerowano wartości funkcji dzeta Riemanna na prostej krytycznej z alternatywnego wzoru." << endl;
    return 0;
}
