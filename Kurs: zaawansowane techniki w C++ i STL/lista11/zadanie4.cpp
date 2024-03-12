//
// Created by Jakub Malczak on 03/01/2024.
//
#include <iostream>
using namespace std;

template<size_t N>
double inner(double *x, double *y)
{
  return x[0] * y[0] + inner<N - 1>(x + 1, y + 1);
}

template<>
double inner<0>(double *x, double *y)
{
  return 0.0;
}

template<size_t N, typename T = double>
T inner(T *x, T *y)
{
  if constexpr (N > 0) {
    return x[0] * y[0] + inner<N - 1, T>(x + 1, y + 1);
  }

  return T();
}

int main()
{
  double x[] = {1.0, 2.0, 3.0};
  double y[] = {4.0, 5.0, 6.0};

  cout << "Inner product (double): " << inner<3>(x, y) << endl;

  int xi[] = {1, 2, 3};
  int yi[] = {8, 10, 12};

  cout << "Inner product (int): " << inner<3, int>(xi, yi) << endl;
}