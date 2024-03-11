//
// Created by Jakub Malczak on 14/10/2023.
//

#include "zadanie3.hpp"

int main() {
    herd myHerd;
    myHerd.buy("Llama1", Gender::Male);
    myHerd.buy("Llama2", Gender::Female);
    myHerd.birth("BabyLlama", Gender::Male, "Llama2", "Llama1");
    myHerd.sell("BabyLlama");
    cout << "." << endl;
    return 0;
}

