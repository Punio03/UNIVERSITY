//
// Created by Jakub Malczak on 21/11/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
using namespace std;

vector<pair<int, int>> mostFrequentElements(const vector<int>& data) {
    unordered_map<int, int> frequencyMap;

    for_each(data.begin(), data.end(), [&frequencyMap](const int& num) {
        frequencyMap[num]++;
    });

    int maxFrequency = max_element(frequencyMap.begin(),frequencyMap.end(), [](const auto& p1, const auto& p2) {
        return p1.second <= p2.second;
    })->second;

    vector<pair<int, int>> result;
    copy_if(frequencyMap.begin(), frequencyMap.end(), back_inserter(result), [&maxFrequency](const auto& p) {
        return p.second == maxFrequency;
    });

    return result;
}

int main() {
    vector<int> data = {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};

    auto result = mostFrequentElements(data);

    for (const auto& [value, frequency] : result) {
        cout << "{" << value << ", " << frequency << "} ";
    }
}
