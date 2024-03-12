//
// Created by Jakub Malczak on 14/12/2023.
//
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
using namespace std;

namespace fs = filesystem;

// /Users/jakubmalczak/CLionProjects/STLtasks

int main() {
    string path;
    cout << "Podaj ścieżkę do katalogu: ";
    getline(cin, path);

    if (!fs::exists(path) || !fs::is_directory(path)) {
        cerr << "Katalog nie istnieje." << endl;
        return 1;
    }

    fs::path p = fs::canonical(path);
    cout << "Kanoniczna ścieżka: " << p << endl;

    vector<string> directories;
    vector<string> files;

    for (const auto& entry : fs::directory_iterator(p)) {
        if (fs::is_directory(entry.status())) {
            directories.push_back(entry.path().filename().string());
        }
        else if (fs::is_regular_file(entry.status())) {
            files.push_back(entry.path().filename().string());
        }
    }

    sort(directories.begin(), directories.end());
    sort(files.begin(), files.end());

    cout << "\nKatalogi:" << endl;
    for (const auto& dir : directories) {
        cout << dir << endl;
    }

    cout << "\nPliki:" << endl;
    for (const auto& file : files) {
        cout << file << endl;
    }
}