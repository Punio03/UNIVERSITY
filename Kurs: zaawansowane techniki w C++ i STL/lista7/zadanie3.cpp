//
// Created by Jakub Malczak on 01/12/2023.
//
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

char generateRandomLetter(mt19937 &gen, const vector<double> &frequencies) {
    discrete_distribution<> dist(frequencies.begin(), frequencies.end());
    return char('a' + dist(gen));
}

int generateWordLength(mt19937 &gen, int max_length) {
    binomial_distribution<> dist(max_length-1, 0.5);
    return dist(gen)+1;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <text length> <output file>\n";
        return 1;
    }

    int textLength = stoi(argv[1]);
    string outputFile = argv[2];

    random_device rd;
    mt19937 gen(rd());

    vector<double> letterFrequencies = {
            8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03,
            5.92, 7.31, 0.10, 0.69, 3.98, 2.61,
            6.95, 7.68, 1.82, 0.11, 6.02, 6.28,
            9.10, 2.88, 1.11, 2.09, 0.17, 2.11, 0.07
    };

    ofstream file(outputFile);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu.\n";
        return 1;
    }

    int remainingLength = textLength;
    while (remainingLength > 0) {
        int wordLength = min(generateWordLength(gen, 12), remainingLength);
        for (int i = 0; i < wordLength; i++) {
            file << generateRandomLetter(gen, letterFrequencies);
        }
        remainingLength -= wordLength;
        if (remainingLength > 0) file << ' ';
        remainingLength--;
    }

    file.close();
    return 0;
}
