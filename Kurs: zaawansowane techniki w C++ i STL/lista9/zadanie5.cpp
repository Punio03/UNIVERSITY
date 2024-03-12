//
// Created by Jakub Malczak on 14/12/2023.
//
#include <iostream>
#include <filesystem>
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

    uintmax_t total_size = 0;

    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (fs::is_regular_file(entry.status())) {
            total_size += fs::file_size(entry);
        }
    }

    cout << "Całkowity rozmiar plików: " << total_size << " bajtów." << endl;
}
