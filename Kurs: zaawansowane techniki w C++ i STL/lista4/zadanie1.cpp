//
// Created by Jakub Malczak on 31/10/2023.
//
#include <iostream>
using namespace std;

template<typename F, typename G, typename H>
class compose_f_gx_hx {
    F _f;
    G _g;
    H _h;
public:
    compose_f_gx_hx(F f, G g, H h) : _f(f), _g(g), _h(h) {}
    auto operator()(const auto& x) { return _f(_g(x), _h(x)); }
};

struct F { double operator()(double x, double y) const { return x - y; } };

struct G { double operator()(double x) const { return 2 * x; } };

struct H { double operator()(double x) const { return x + 1; } };

int main() {
    F f;
    G g;
    H h;
    compose_f_gx_hx<F,G,H> composer(f,g,h);
    cout << "Rezultat złożenia f(g(3),h(3)) = " << composer(3) << endl;
    //f(g(3), h(3)) = f(6, 4) = 6 - 4 = 2
}