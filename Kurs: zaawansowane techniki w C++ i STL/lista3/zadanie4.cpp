//
// Created by Jakub Malczak on 22/10/2023.
//
#include <type_traits>
#include <iostream>
using namespace std;

template <typename Source, typename Target>
void transferValue(const Source& source, Target& target) {
    if constexpr (is_pointer_v<Source>) {
        if constexpr (is_convertible_v<remove_pointer_t<Source>, Target>) target = *source;
        else if constexpr (is_convertible_v<Source, Target>) target = source;
        else cerr << "Nie można przenieść wartości: niekompatybilne typy." << endl;
    }
    else {
        if constexpr (is_convertible_v<Source, Target>) target = source;
        else cerr << "Nie można przenieść wartości: niekompatybilne typy." << endl;
    }
}

int main() {
    int a = 5;
    int* pA = &a;
    double b = 0;
    char c = 'c';
    char* d = new char[10];
    for (int i = 0; i < 10; i++) d[i] = (char)(97+i);
    string e;
    bool f = true;
    transferValue(a,b);
    cout << "b = " << b << endl;
    b = 0;
    transferValue(pA,b);
    cout << "b = " << b << endl;
    transferValue(c, a);
    cout << "a = " << a << endl;
    transferValue(d,e);
    cout << "e = " << e << endl;
    transferValue(f,a);
    cout << "a = " << a << endl;
    transferValue(c,e);
}
