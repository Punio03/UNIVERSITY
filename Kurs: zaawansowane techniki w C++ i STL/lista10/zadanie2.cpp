//
// Created by Jakub Malczak on 22/12/2023.
//
#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
using namespace std;

void print_data_for_locale(const locale& loc)
{
  cout.imbue(loc);
  cout << loc.name() << endl;

  cout << "Liczby całkowite: " << endl;
  cout << 1000 << endl;
  cout << 2143432 << endl;
  cout << 442 << endl;

  cout << "Liczby zmiennopozycyjne: " << endl;
  cout << 3.14 << endl;
  cout << 123.456 << endl;
  cout << 9876.54321 << endl;

  cout << "Wartości pieniężne: " << showbase << endl;
  cout << put_money(3434353) << endl;
  cout << put_money(123456789, true) << endl;
  cout << put_money(271) << endl;

  auto now = chrono::system_clock::now();
  auto in_time_t = chrono::system_clock::to_time_t(now);
  cout << "Data i godzina: " << put_time(localtime(&in_time_t), "%c") << endl;

  cout << "---------------------" << endl;
}

int main()
{
  print_data_for_locale(locale("pl_PL.UTF-8"));
  print_data_for_locale(locale("en_US.UTF-8"));
  print_data_for_locale(locale("fr_FR.UTF-8"));
}