//
// Created by Jakub Malczak on 14/12/2023.
//
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Użycie: " << argv[0] << " <ścieżka do pliku/folderu>..." << endl;
    return 1;
  }

  for (int i = 1; i < argc; ++i) {
    fs::path path(argv[i]);
    if (fs::exists(path)) {
      auto canonical_path = fs::canonical(path);
      cout << "Ścieżka kanoniczna: " << canonical_path << endl;

      auto ftime = fs::last_write_time(path);
      auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
              ftime - fs::file_time_type::clock::now() + chrono::system_clock::now()
      );
      time_t cftime = chrono::system_clock::to_time_t(sctp);
      cout << "Data ostatniej modyfikacji: " << put_time(localtime(&cftime), "%Y-%m-%d %H:%M:%S") << endl;


      if (fs::is_regular_file(path)) {
        cout << "Rozmiar: " << fs::file_size(path) << " bajtów" << endl;
      }
      cout << endl;
    }
    else {
      cout << "Plik/folder nie istnieje: " << path << endl << endl;
    }
  }


}