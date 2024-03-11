//
// Created by Jakub Malczak on 31/10/2023.
//
#include <iostream>
using namespace std;

template<typename F1, typename F2>
class po_kolei {
    F1 _f1;
    F2 _f2;
public:
    po_kolei(F1 f1, F2 f2) : _f1(f1), _f2(f2) {}
    void operator()(const auto& x) {
        _f1(x);
        _f2(x);
    }
};

struct F1 { void operator()(int x) const { cout << "F1: " << x << endl; } };

struct F2 { void operator()(int x) const { cout << "F2: " << x * x << endl; } };

struct F3 { void operator()(int x) const { cout << "F3: " << x - 1 << endl; } };


int main() {
    F1 f1;
    F2 f2;
    F3 f3;
    po_kolei<F1,F2> po_kolei_f1_f2(f1,f2);
    po_kolei<po_kolei<F1,F2>,F3> po_kolei_all(po_kolei_f1_f2, f3);
    cout << "Wykonanie po_kolei(f1, f2)(5):" << endl;
    po_kolei_f1_f2(5);
    cout << "Wykonanie po_kolei(po_kolei(f1, f2), f3)(5):" << endl;
    po_kolei_all(5);
}