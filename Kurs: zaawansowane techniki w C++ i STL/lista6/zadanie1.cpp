//
// Created by Jakub Malczak on 21/11/2023.
//
#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <random>
#include <iomanip>
using namespace std;

class Person {
public:
    string first_name;
    string last_name;
    int age;
    double weight;
    double height;

    Person(string first_name, string last_name, int age, double weight, double height)
            : first_name(std::move(first_name)), last_name(std::move(last_name)), age(age), weight(weight), height(height) {}

    [[nodiscard]] double bmi() const { return weight / (height * height); }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "Name: " << person.first_name << " " << person.last_name
           << ", Age: " << person.age
           << ", Weight: " << person.weight << " kg"
           << ", Height: " << fixed << setprecision(2) << person.height << " m"
           << ", BMI: " << fixed << setprecision(2) << person.bmi();
        return os;
    }
};

ostream& operator<<(ostream& os, const deque<Person>& people) {
    for (const auto& person : people) {
        os << person << endl;
    }
    return os;
}

//a
void sortByBMI(deque<Person>& people) {
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.bmi() < b.bmi();
    });

    cout << people;
}

//b
void reduceWeight(deque<Person>& people) {
    for_each(people.begin(), people.end(), [](Person& person) {
        person.weight = person.weight * 0.9;
    });

    cout << people;
}

//c
void divide(const deque<Person>& people) {
    deque<Person> heavy, light;
    partition_copy(people.begin(), people.end(), back_inserter(heavy), back_inserter(light),
                        [](const Person& person) { return person.weight > 100; });

    cout << "Heavy Group:\n";
    cout << heavy;
    cout << "\nLight Group:\n";
    cout << light;
}

//d
void setMiddleHeightAtFive(deque<Person>& people) {
    nth_element(people.begin(), people.begin()+5, people.end(),
                     [](const Person& a, const Person& b) { return a.height < b.height; });

    cout << people;
}

//e
void shuffleFirstAndLastFive(deque<Person>& people) {
    random_device rd;
    mt19937 g(rd());

    shuffle(people.begin(), people.begin() + 5, g);
    shuffle(people.end() - 5, people.end(), g);

    cout << people;
}

//f
void printOldestAndYoungest(const deque<Person>& people) {
    auto [youngest,oldest] = minmax_element(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.age < b.age;
    });

    cout << "Oldest: " << oldest->first_name << " " << oldest->last_name << ", Age: " << oldest->age << "\n";
    cout << "Youngest: " << youngest->first_name << " " << youngest->last_name << ", Age: " << youngest->age << "\n";
}




int main() {
    deque<Person> people;

    people.emplace_back("John", "Doe", 30, 70.0, 1.80);
    people.emplace_back("Jane", "Doe", 28, 65.0, 1.70);
    people.emplace_back("Alice", "Smith", 35, 117.0, 1.65);
    people.emplace_back("Bob", "Brown", 40, 80.0, 1.75);
    people.emplace_back("Charlie", "Davis", 25, 90.0, 1.85);
    people.emplace_back("Diana", "Evans", 32, 115.0, 1.60);
    people.emplace_back("Eve", "Williams", 29, 58.0, 1.70);
    people.emplace_back("Frank", "Miller", 45, 150.0, 1.78);
    people.emplace_back("Grace", "Wilson", 31, 62.0, 1.68);
    people.emplace_back("Henry", "Taylor", 36, 77.0, 1.95);
    people.emplace_back("Ivy", "Moore", 33, 70.0, 1.73);
    people.emplace_back("Jake", "Jackson", 38, 88.0, 1.82);

    cout << "A:" << endl;
    sortByBMI(people);
    cout << endl;

    cout << "B:"  << endl;
    reduceWeight(people);
    cout << endl;

    cout << "C:" << endl;
    divide(people);
    cout << endl;

    cout << "D:" << endl;
    setMiddleHeightAtFive(people);
    cout << endl;

    cout << "E:" << endl;
    shuffleFirstAndLastFive(people);
    cout << endl;

    cout << "F:" << endl;
    printOldestAndYoungest(people);
    cout << endl;
}