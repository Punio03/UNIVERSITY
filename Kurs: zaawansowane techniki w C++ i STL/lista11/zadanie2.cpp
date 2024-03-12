//
// Created by Jakub Malczak on 03/01/2024.
//
#include <iostream>
using namespace std;

template<unsigned long long n, unsigned long long k>
struct Binomial
{
    static_assert(k <= n, "k musi być mniejsze równe n!");
    static constexpr unsigned long long result = Binomial<n - 1, k - 1>::result * n / k;
};

template<unsigned long long n>
struct Binomial<n, n>
{
    static constexpr unsigned long long result = 1;
};

template<unsigned long long n>
struct Binomial<n, 0>
{
    static constexpr unsigned long long result = 1;
};

template<unsigned long long n, unsigned long long k>
inline unsigned long long binomial()
{
  return Binomial<n, k>::result;
}

int main()
{
  cout << "Binomial<3, 2> = " << binomial<3, 2>() << endl;
  cout << "Binomial<5, 1> = " << binomial<5, 1>() << endl;
  cout << "Binomial<9, 4> = " << binomial<9, 4>() << endl;
}