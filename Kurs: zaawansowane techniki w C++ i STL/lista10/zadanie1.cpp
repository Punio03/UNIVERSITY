//
// Created by Jakub Malczak on 22/12/2023.
//
#include <iostream>
#include <locale>
using namespace std;

int main()
{
  locale polish("pl_PL.UTF-8");
  wcout.imbue(polish);

  wstring text = L"Zażółć gęślą jaźń.";
  wcout << text << endl;
}
