//
// Created by Jakub Malczak on 21/10/2023.
//
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;

using M = vector<vector<double>>;

//https://stackoverflow.com/a/35687575
template<typename Numeric, typename Generator = mt19937>
Numeric random(Numeric from, Numeric to) {
    thread_local static Generator gen(random_device{}());
    using dist_type = typename conditional<is_integral<Numeric>::value, uniform_int_distribution<Numeric>, uniform_real_distribution<Numeric>>::type;
    thread_local static dist_type dist;
    return dist(gen, typename dist_type::param_type{from, to});
}

M generate_random_matrix(int n) {
    M matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) matrix[i][j] = random<double>(0.5,2.0);
    return matrix;
}

M square_matrix(const M& matrix) {
    int n = (int)matrix.size();
    M res(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double s = 0;
            for (int k = 0; k < n; k++) s += matrix[i][k]*matrix[k][j];
            res[i][j] = s;
        }
    }
    return res;
}

int main() {
    M matrix10x10 = generate_random_matrix(10), matrix100x100 = generate_random_matrix(100), matrix1000x1000 = generate_random_matrix(1000);
    int repetitions = 10000;

    auto start10 = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) matrix10x10 = square_matrix(matrix10x10);
    auto stop10 = high_resolution_clock::now();
    cout << "Czas dla macierzy 10x10: " << (double)duration_cast<microseconds>(stop10-start10).count()/(double)repetitions << " mikrosekund." << endl;

    repetitions = 100;
    auto start100 = high_resolution_clock::now();
    for (int i = 0; i < repetitions; ++i) matrix100x100 = square_matrix(matrix100x100);
    auto stop100 = high_resolution_clock::now();
    cout << "Czas dla macierzy 100x100: " << (double)duration_cast<milliseconds>(stop100-start100).count() / (double)(repetitions) << " milisekund." << endl;

    auto start1000 = high_resolution_clock::now();
    matrix1000x1000 = square_matrix(matrix1000x1000);
    auto stop1000 = high_resolution_clock::now();
    cout << "Czas dla macierzy 1000x1000: " << duration_cast<seconds>(stop1000-start1000).count() << " sekund." << endl;
}