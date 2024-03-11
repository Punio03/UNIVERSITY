//
// Created by Jakub Malczak on 31/10/2023.
//
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;

template<typename T>
class PrintInRange {
    T a, b;
public:
    PrintInRange(T a, T b) : a(a), b(b) {}
    void operator()(const T& value) { if (value > a && value < b) cout << value << " "; }
};

template<typename T>
class PrintEveryKth {
    int k, p, count = 0;
public:
    PrintEveryKth(int k, int p) : k(k), p(p) {}
    void operator()(const T& value) { if (++count >= p && (count - p) % k == 0) cout << value << " "; }
};

class Average {
    double sum = 0;
    int count = 0;
public:
    void operator()(double value) {
        sum += value;
        count++;
    }
    [[nodiscard]] double getAverage() const { return count > 0 ? sum / count : 0; }
};

template<typename T>
class MinMax {
    pair<T,T> min_max;
    bool initialized = false;
public:
    void operator()(const T& value) {
        if (!initialized) {
            min_max = {value, value};
            initialized = true;
        }
        else if (value < min_max.first) min_max.first = value;
        else if (value > min_max.second) min_max.second = value;
    }
    [[nodiscard]] pair<T,T> getMinMax() const { return min_max; }
};

template<typename T>
class SumOrConcatenated {
    T sum{};
public:
    void operator()(const T& value) { sum += value; }
    [[nodiscard]] T getSumOrConcatenated() const { return sum; }
};

int main() {
    vector<double> v = {1.5, 2.3, 3.7, 4.6, 5.9, 6.2};
    list<string> l = {"apple", "banana", "cherry", "date", "elderberry", "fig"};
    set<int> s = {1, 2, 3, 4, 5, 6};

    cout << "Values in range (for vector): ";
    for_each(v.begin(), v.end(), PrintInRange<double>(2.0, 5.0));
    cout << endl;

    cout << "Every k-th value from p-th (for list): ";
    for_each(l.begin(), l.end(), PrintEveryKth<string>(2, 1));
    cout << endl;

    Average avg;
    for_each(v.begin(), v.end(), ref(avg));
    cout << "Average (for vector): " << avg.getAverage() << endl;

    MinMax<int> minmax;
    for_each(s.begin(), s.end(), ref(minmax));
    auto [min_value, max_value] = minmax.getMinMax();
    cout << "Min and Max (for set): " << min_value << " " << max_value << endl;

    SumOrConcatenated<int> sum;
    for_each(s.begin(), s.end(), ref(sum));
    cout << "Sum (for set): " << sum.getSumOrConcatenated() << endl;

    SumOrConcatenated<string> concatenate;
    for_each(l.begin(), l.end(), ref(concatenate));
    cout << "Concatenated strings (for list): " << concatenate.getSumOrConcatenated() << endl;
}