//
// Created by Jakub Malczak on 22/12/2023.
//
#include <algorithm>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
using namespace std;

int main()
{
  locale polish("pl_PL.UTF-8");
  locale::global(polish);
  wcout.imbue(polish);

  vector<wstring> v{
          L"Słoń", L"Bąk", L"Bocian",
          L"Ryś", L"Żyrafa", L"Lew",
          L"Żuk", L"Bóbr", L"Anakonda",
          L"Łoś", L"Bażant", L"Czapla"
  };

  vector<wstring> w{
          L"Ąąą", L"ąąą", L"Ććć", L"ććć",
          L"Ęęę", L"ęęę", L"Łłł", L"łłł",
          L"Ńńń", L"ńńń", L"Óóó", L"óóó",
          L"Śśś", L"śśś", L"Źźź", L"źźź",
          L"Żżż", L"żżż"
  };

  cout << "Przed sortowaniem: ";
  for (const auto& s : v)
    wcout << s << " ";
  cout << endl;

  sort(v.begin(), v.end(), polish);

  cout << "Po sortowaniu: ";
  for (const auto& s : v)
    wcout << s << " ";
  cout << endl;
}