//
// Created by Jakub Malczak on 07/12/2023.
//
#include <iostream>
#include <regex>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <nazwa_pliku>\n";
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku: " << filename << "\n";
        return 1;
    }

    string html_content;
    string line;

    while (getline(file, line)) {
        html_content += line + "\n";
    }

    regex href_regex("<a[^>]*href=\"([^\"]*)\"");

    auto begin = sregex_iterator(html_content.begin(), html_content.end(), href_regex);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        string match_str = match[1].str();
        cout << match_str << endl;
    }

}