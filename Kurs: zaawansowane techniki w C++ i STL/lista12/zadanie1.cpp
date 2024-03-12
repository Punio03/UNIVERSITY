//
// Created by Jakub Malczak on 18/01/2024.
//
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <atomic>
using namespace std;

void thread_function(const string& name, atomic<bool>& running) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(500, 1000);

  while (running) {
    this_thread::sleep_for(chrono::milliseconds(distr(gen)));
    cout << "I'm " << name << endl;
  }
}


int main() {
  atomic<bool> running(true);
  vector<string> names{"foo", "bar", "baz", "qux"};

  vector<thread> threads;
  for (const string& name : names) {
    threads.emplace_back(thread_function, name, ref(running));
  }

  this_thread::sleep_for(chrono::seconds(5));
  running = false;

  for (auto& thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}