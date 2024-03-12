//
// Created by Jakub Malczak on 22/12/2023.
//
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>
using namespace std;

int main()
{
  ifstream utf8_file("/Users/jakubmalczak/CLionProjects/STLtasks/lista10/zadanie3_input.txt", ios::binary);
  wstring_convert<codecvt_utf8_utf16<char32_t>, char32_t> conv_utf32;
  wstring_convert<codecvt_utf8_utf16<wchar_t>> conv_utf16;

  string utf8_content((istreambuf_iterator<char>(utf8_file)), istreambuf_iterator<char>());
  utf8_file.close();

  auto utf32_content = conv_utf32.from_bytes(utf8_content);
  ofstream utf32_file("/Users/jakubmalczak/CLionProjects/STLtasks/lista10/zadanie3_output_utf32.txt", ios::binary);
  for (auto ch : utf32_content)
    utf32_file.write(reinterpret_cast<const char*>(&ch), sizeof(char32_t));
  utf32_file.close();

  auto wide_content = conv_utf16.from_bytes(utf8_content);
  string iso_content;
  for (wchar_t wc : wide_content)
  {
    if (wc <= 0xFF)
      iso_content += static_cast<char>(wc);
    else
      iso_content += '?';
  }

  ofstream iso_file("/Users/jakubmalczak/CLionProjects/STLtasks/lista10/zadanie3_output_iso_8859_2.txt", ios::binary);
  iso_file.write(iso_content.c_str(), iso_content.size());
  iso_file.close();
}