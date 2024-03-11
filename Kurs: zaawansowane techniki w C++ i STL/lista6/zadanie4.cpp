//
// Created by Jakub Malczak on 21/11/2023.
//
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <string>
#include <iterator>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Użycie: " << argv[0] << " <nazwa_pliku>\n";
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku: " << filename << "\n";
        return 1;
    }

    vector<char> fileContents((istreambuf_iterator<char>(file)),
                               istreambuf_iterator<char>());

    map<char, int> frequency;
    int totalLetters = 0;

    for (char ch : fileContents) {
        if (isalpha(ch)) {
            ch = (char)tolower(ch);
            frequency[ch]++;
            totalLetters++;
        }
    }

    file.close();

    for (const auto& [letter,number] : frequency) {
        double percentage = 100.0 * number / totalLetters;
        cout << letter << ": " << percentage << "%" << endl;
    }
}