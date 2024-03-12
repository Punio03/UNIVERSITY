//
// Created by Jakub Malczak on 14/12/2023.
//
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <fstream>
using namespace std;

int phi(int n) {
    int result = 1;

    for (int i = 2; i < n; i++) {
        if (gcd(i, n) == 1) {
            result++;
        }
    }

    return result;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Użycie: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k = atoi(argv[1]);
    vector<int> phi_values(k);
    for (int i = 0; i < k; i++) {
        phi_values[i] = phi(i + 1);
    }

    ofstream file("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie2.txt");
    ostream_iterator<int> out_it(file, "; ");
    copy(phi_values.begin(), phi_values.end(), out_it);
}