//
// Created by Jakub Malczak on 12/10/2023.
//
#include <iostream>
using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    if (double delta{b*b-4*a*c}; delta > 0) {
        cout << (-b+sqrt(delta))/2*a << " " <<
             (-b-sqrt(delta))/2*a;
    }
    else if (delta == 0) cout << -b/2*a;
    else cout << "Brak miejsc zerowych!";
}
