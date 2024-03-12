//
// Created by Jakub Malczak on 18/01/2024.
//
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>
using namespace std;

class Buffer {
public:
    explicit Buffer(int size) : max_size(size) {}

    void add(int element) {
      unique_lock<mutex> lock(mtx);
      cond.wait(lock, [this]() { return buffer.size() < max_size; });
      buffer.push_back(element);
      cond.notify_all();
    }

    int remove() {
      unique_lock<mutex> lock(mtx);
      cond.wait(lock, [this]() { return buffer.size() > 0; });
      int element = buffer.back();
      buffer.pop_back();
      cond.notify_all();
      return element;
    }

private:
    vector<int> buffer;
    mutex mtx;
    condition_variable cond;
    int max_size;
};

void producer(Buffer& buffer, const string& name, int begin, int end) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(500, 1000);
  for (int i = begin; i < end; ++i) {
    buffer.add(i);
    cout << name << " produced: " << i << endl;
    this_thread::sleep_for(chrono::milliseconds(distr(gen)));
  }
}

void consumer(Buffer& buffer, const string& name) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(500, 1000);
  for (int i = 0; i < 10; i++) {
    int element = buffer.remove();
    cout << name << " consumed: " << element << endl;
    this_thread::sleep_for(chrono::milliseconds(distr(gen)));
  }
}

int main() {
  Buffer buffer(3);

  thread producer_thread(producer, ref(buffer), "Producent", 0, 10);
  thread producer1_thread(producer, ref(buffer), "Producent1", 10, 20);
  thread producer2_thread(producer, ref(buffer), "Producent2",20,30);
  thread producer3_thread(producer, ref(buffer), "Producent3",30,40);
  thread consumer_thread(consumer, ref(buffer), "Konsument");
  thread consumer1_thread(consumer, ref(buffer), "Konsument1");
  thread consumer2_thread(consumer, ref(buffer), "Konsument2");
  thread consumer3_thread(consumer, ref(buffer), "Konsument3");


  producer_thread.join();
  producer1_thread.join();
  producer2_thread.join();
  producer3_thread.join();
  consumer_thread.join();
  consumer1_thread.join();
  consumer2_thread.join();
  consumer3_thread.join();
}