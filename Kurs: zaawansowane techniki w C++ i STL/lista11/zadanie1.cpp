//
// Created by Jakub Malczak on 03/01/2024.
//
#include <iostream>
using namespace std;

template<unsigned long long n>
struct Lucas
{
    static_assert(n < 93, "n musi być mniejsze od 93!");
    static constexpr unsigned long long prev = Lucas<n - 1>::curr;
    static constexpr unsigned long long curr = Lucas<n - 1>::curr + Lucas<n - 1>::prev;
};

template<>
struct Lucas<1>
{
    static constexpr int prev = 2;
    static constexpr int curr = 1;
};

template<>
struct Lucas<0>
{
    static constexpr int prev = 2;
    static constexpr int curr = 2;
};

template<unsigned long long n>
inline unsigned long long lucas()
{
  return Lucas<n>::curr;
}

int main()
{
  cout << "Lucas<7> = " << lucas<7>() << endl;
  cout << "Lucas<38> = " << lucas<38>() << endl;
  cout << "Lucas<92> = " << lucas<92>() << endl;
}

/*
 * strona do sprawdzenia poprawności
 * https://dqydj.com/lucas-series-calculator/
 */