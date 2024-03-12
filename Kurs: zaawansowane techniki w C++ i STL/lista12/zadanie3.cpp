//
// Created by Jakub Malczak on 18/01/2024.
//
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  vector<int> L(n1), R(n2);
  for (int i = 0; i < n1; ++i) {
    L[i] = arr[l + i];
  }
  for (int j = 0; j < n2; ++j) {
    R[j] = arr[m + 1 + j];
  }

  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void merge_sort(vector<int>& arr, int l, int r) {
  if (l >= r) {
    return;
  }

  int m = l + (r - l) / 2;

  thread left_thread(merge_sort, ref(arr), l, m);
  thread right_thread(merge_sort, ref(arr), m + 1, r);

  left_thread.join();
  right_thread.join();

  merge(arr, l, m, r);
}

int main() {
  vector<int> arr = {12, 11, 13, 5, 6, 7,34543,32,24,63,6,35,3223,76523};

  cout << "Oryginalna tablica: ";
  for (int i : arr) {
    cout << i << " ";
  }
  cout << endl;

  merge_sort(arr, 0, arr.size() - 1);

  cout << "Posortowana tablica: ";
  for (int i : arr) {
    cout << i << " ";
  }
  cout << endl;
}