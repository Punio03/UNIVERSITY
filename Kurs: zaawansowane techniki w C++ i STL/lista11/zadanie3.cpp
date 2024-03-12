//
// Created by Jakub Malczak on 03/01/2024.
//
#include <iostream>
using namespace std;

template<unsigned long long a, unsigned long long b>
struct NWD
{
    static_assert(a > 0 && b > 0, "a i b muszą być większe od 0!");
    static constexpr unsigned long long result = NWD<b, a % b>::result;
};

template<unsigned long long a>
struct NWD<a, 0>
{
    static constexpr unsigned long long result = a;
};

template<unsigned long long a, unsigned long long b>
inline unsigned long long nwd()
{
  return NWD<a, b>::result;
}

int main()
{
  cout << "NWD<7, 11> = " << nwd<7, 11>() << endl;
  cout << "NWD<135, 75> = " << nwd<135, 75>() << endl;
  cout << "NWD<210, 462> = " << nwd<210, 462>() << endl;
}