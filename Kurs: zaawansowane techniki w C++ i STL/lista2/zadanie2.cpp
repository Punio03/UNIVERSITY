//
// Created by Jakub Malczak on 14/10/2023.
//
#include "zadanie2.hpp"

int main() {
    shared_ptr<line_writer> writer1 = make_shared<line_writer>("zadanie2.txt");
    shared_ptr<line_writer> writer2 = writer1;
    shared_ptr<line_writer> writer3 = writer1;
    writer1->write_line("Dane z pierwszego wskaźnika!");
    //writer1.reset();
    writer2->write_line("Dane z drugiego wskaźnika!");
    //writer2.reset();
    writer3->write_line("Dane z trzeciego wskaźnika!");
    //writer3.reset();
}
