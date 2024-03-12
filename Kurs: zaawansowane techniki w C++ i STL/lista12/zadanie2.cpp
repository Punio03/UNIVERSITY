//
// Created by Jakub Malczak on 18/01/2024.
//
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void timer(int seconds, const string& message) {
  this_thread::sleep_for(chrono::seconds(seconds));
  cout << message << endl;
}

int main() {
  thread t1(timer, 5, "Program zakończy się za 5 sekund!");
  thread t2(timer, 7, "Program zakończy się za 3 sekundy!");
  thread t3(timer, 9, "Program zakończy się za 1 sekundę!");

  this_thread::sleep_for(chrono::seconds(10));

  t1.join();
  t2.join();
  t3.join();

  cout << "Program zakończył działanie!" << endl;
}