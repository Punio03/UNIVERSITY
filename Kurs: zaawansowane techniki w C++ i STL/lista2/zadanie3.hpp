//
// Created by Jakub Malczak on 14/10/2023.
//

#ifndef STLTASKS_ZADANIE3_HPP
#define STLTASKS_ZADANIE3_HPP
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <set>
#include <algorithm>
using namespace std;

enum class Gender {
    Male,
    Female
};

class llama : public enable_shared_from_this<llama> {
    string name;
    Gender gender;
    shared_ptr<llama> mother;
    shared_ptr<llama> father;
    vector<weak_ptr<llama>> children;

public:
    llama(string  _name, Gender _gender, shared_ptr<llama> _mother = nullptr, shared_ptr<llama> _father = nullptr)
        : name(std::move(_name)), gender(_gender), mother(std::move(_mother)),father(std::move(_father)) {
        if (name != "noname") {
            cout << "LLama " << name << " została dodana!" << endl;
            if (!mother) mother = make_shared<llama>("noname", Gender::Female);
            if (!father) father = make_shared<llama>("noname", Gender::Male);
        }
    }
    ~llama() { if (name != "noname") cout << "Llama " << name << " została usunięta!" << endl; }
    [[nodiscard]] string get_name() const { return name; }
    Gender get_gender() { return gender; }
    vector<weak_ptr<llama>> get_children() { return children; }
    void postInitialize() {
        if (mother->get_name() != "noname") mother->children.push_back(shared_from_this());
        if (father->get_name() != "noname") father->children.push_back(shared_from_this());
    }
    bool operator<(const llama& other) const { return name < other.name; }
};

class herd {
public:
    set<shared_ptr<llama>> llamas;
    void buy(const string& name, Gender gender) {
        if (name == "noname") throw logic_error("Kupiona llama nie może mieć na imię noname!");
        for (const auto& l : llamas) if (name == l->get_name()) throw logic_error("Kupiona llama nie ma unikatowego imienia!");
        llamas.insert(make_shared<llama>(name,gender));
    }
    void sell(const string& name) {
        auto it = find_if(llamas.begin(), llamas.end(), [&name](const shared_ptr<llama>& l) { return l->get_name() == name; });
        if (it != llamas.end()) { llamas.erase(it); }
    }
    void birth(const string& name, Gender gender, const string& name_mother, const string& name_father) {
        if (name == "noname") throw logic_error("Urodzona llama nie może mieć na imię noname!");
        for (const auto& l : llamas) if (name == l->get_name()) throw logic_error("Urodzona llama nie ma unikatowego imienia!");
        shared_ptr<llama> mother = nullptr, father = nullptr;
        for (const auto& l : llamas) {
            if (name_mother == l->get_name()) mother = l;
            if (name_father == l->get_name()) father = l;
        }
        if (!mother) throw logic_error("Urodzona llama musi mieć matkę!");
        else if (mother->get_gender() == Gender::Male) throw logic_error("Matka nie może być samcem!");
        if (!father && father->get_gender() == Gender::Female) throw logic_error("Ojciec nie może być samicą!");
        auto newllama = make_shared<llama>(name,gender,mother,father);
        newllama->postInitialize();
        llamas.insert(newllama);

    }
};


#endif //STLTASKS_ZADANIE3_HPP
