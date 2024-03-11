//
// Created by Jakub Malczak on 14/10/2023.
//

#ifndef STLTASKS_ZADANIE2_HPP
#define STLTASKS_ZADANIE2_HPP
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

class line_writer {
private:
    ofstream ofs;
public:
    explicit line_writer(const string& filename) : ofs(filename) { if (!ofs.is_open()) throw runtime_error("Nie można otworzyć pliku!"); }
    ~line_writer() { ofs.close(); }
    void write_line(const string& line) { ofs << line << endl; }
};


#endif //STLTASKS_ZADANIE2_HPP
