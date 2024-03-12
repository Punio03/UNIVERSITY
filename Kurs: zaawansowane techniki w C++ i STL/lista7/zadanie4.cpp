//
// Created by Jakub Malczak on 01/12/2023.
//
#include <complex>
#include <iostream>
using namespace std;

const complex<double> EulerGamma = 0.5772156649;

complex<double> gammaFunction(const complex<double>& z, int iterations = 1000) {
    complex<double> result = 1.0 / z;
    for (double n = 1.0; n <= iterations; n++) {
        result *= pow(1.0 + 1.0 / n, z) / (1.0 + z / n);
    }
    return result;
}

complex<double> inverseGammaFunction(const complex<double>& z, int iterations = 1000) {
    complex<double> result = z * exp(EulerGamma * z);
    for (double n = 1.0; n <= iterations; n++) {
        result *= (1.0 + z / n) * exp(-z / n);
    }
    return result;
}

int main() {
    complex<double> z(0.5, 0.5);

    cout << "Gamma(" << z << ") = " << gammaFunction(z) << endl;
    cout << "1/Gamma(" << z << ") = " << inverseGammaFunction(z) << endl;

    return 0;
}
