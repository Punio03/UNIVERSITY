//
// Created by Jakub Malczak on 09/11/2023.
//
#include <iostream>
#include <tuple>
#include <numbers>
#include <map>
#include <vector>
#include <sstream>
#include <optional>
#include <forward_list>
#include <stack>
#include <unordered_set>
using namespace std;

const map<string,double> constants = {
        {"e",numbers::e_v<double>},
        {"pi", numbers::pi_v<double>},
        {"phi", numbers::phi_v<double>}
};

const vector<string> operators = {
        "^",
        "*",
        "/",
        "%",
        "+",
        "-"
};

const vector<string> functions = {
        "abs",
        "sgn",
        "log",
        "ceil",
        "frac",
        "sin",
        "cos",
        "atan",
        "acot",
        "ln",
        "exp",
        "min",
        "max",
        "floor"
};

bool is_double(const string& str) {
    auto result = double();
    auto i = istringstream(str);
    i >> result;
    return !i.fail() && i.eof();
}

int priority(const string& op) {
    if (op == "^") return 4;
    if (op == "+" || op == "-") return 2;
    return 3;
}

struct pair_hash {
    size_t operator () (const pair<string, int>& p) const {
        auto hash1 = hash<string>{}(p.first);
        auto hash2 = hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

enum class SymbolType {
    Number,
    Operator,
    Function,
    Parenthesis,
    Comma
};

class Symbol {
private:
    tuple<SymbolType, optional<double>, optional<string>, int> data;

public:
    Symbol(SymbolType type, optional<double> value, const optional<string>& name, int priority = 0)
            : data(type, value, name, priority) {}

    [[nodiscard]] SymbolType get_type() const { return get<0>(data); }
    [[nodiscard]] optional<double> get_value() const { return get<1>(data); }
    [[nodiscard]] optional<string> get_name() const { return get<2>(data); }
    [[nodiscard]] int get_priority() const { return get<3>(data); }
};

forward_list<Symbol> parse(const string& expression, const unordered_set<pair<string,double>,pair_hash>& variables) {
    forward_list<Symbol> infix;
    stringstream ss(expression);
    string symbol;

    while (ss >> symbol) {
        if (is_double(symbol)) {
            infix.emplace_front(SymbolType::Number, stod(symbol), nullopt);
        }
        else if (find(operators.begin(), operators.end(),symbol) != end(operators)) {
            infix.emplace_front(SymbolType::Operator, nullopt, symbol, priority(symbol));
        }
        else if (find(functions.begin(),functions.end(),symbol) != end(functions)) {
            infix.emplace_front(SymbolType::Function, nullopt, symbol);
        }
        else if (symbol == "(" || symbol == ")") {
            infix.emplace_front(SymbolType::Parenthesis, nullopt, symbol);
        }
        else if (symbol == ",") {
            infix.emplace_front(SymbolType::Comma, nullopt, symbol);
        }
        else if (symbol == "e" || symbol == "pi" || symbol == "phi") {
            infix.emplace_front(SymbolType::Number, constants.at(symbol), nullopt);
        }
        else {
            bool found = false;

            for (const auto& [name,value] : variables) {
                if (name == symbol) {
                    infix.emplace_front(SymbolType::Number, value, nullopt);
                    found = true;
                    break;
                }
            }

            if (!found) throw "Błąd parsowania!!!";
        }
    }

    infix.reverse();
    return infix;
}

forward_list<Symbol> infix_to_postfix(const forward_list<Symbol>& infix) {
    forward_list<Symbol> postfix;
    stack<Symbol> stack;

    for (const Symbol& symbol : infix) {
        SymbolType type = symbol.get_type();
        optional<double> value = symbol.get_value();
        optional<string> name = symbol.get_name();
        int prio = symbol.get_priority();

        if (type == SymbolType::Number) {
            postfix.push_front(symbol);
        }
        else if (type == SymbolType::Function || (type == SymbolType::Parenthesis && name.value() == "(")) {
            stack.push(symbol);
        }
        else if (type == SymbolType::Operator) {
            while (!stack.empty() &&
                   stack.top().get_name().value() != "(" &&
                   (stack.top().get_priority() > prio ||
                   (stack.top().get_priority() == prio && name.value() != "^"))) {
                postfix.push_front(stack.top());
                stack.pop();
            }

            stack.push(symbol);
        }
        else if (type == SymbolType::Comma){
            while (!stack.empty() && stack.top().get_name().value() != "(") {
                postfix.push_front(stack.top());
                stack.pop();
            }
        }
        else {
            while (!stack.empty() && stack.top().get_name().value() != "(") {
                postfix.push_front(stack.top());
                stack.pop();
            }

            if (!stack.empty()) {
                stack.pop();
            }

            if (!stack.empty() && stack.top().get_type() == SymbolType::Function) {
                postfix.push_front(stack.top());
                stack.pop();
            }
        }
    }

    while (!stack.empty()) {
        postfix.push_front(stack.top());
        stack.pop();
    }

    postfix.reverse();
    return postfix;
}

ostream& operator<<(ostream& os, const forward_list<Symbol>& postfix) {
    for (const Symbol& symbol : postfix) {
        if (symbol.get_value().has_value()) {
            cout << symbol.get_value().value() << " ";
        }
        else {
            cout << symbol.get_name().value() << " ";
        }
    }

    return os;
}

int main() {
    unordered_set<pair<string,double>,pair_hash> s{make_pair("x",3), make_pair("y",2)};
    string a = "3 + 4 * 2 / ( 1 - 5 ) ^ y ^ x";
    string b = "sin ( max ( y , x ) / 3 * pi )";

    cout << a << " = " << infix_to_postfix(parse(a,s)) << endl;
    cout << b << " = " << infix_to_postfix(parse(b,s)) << endl;
}