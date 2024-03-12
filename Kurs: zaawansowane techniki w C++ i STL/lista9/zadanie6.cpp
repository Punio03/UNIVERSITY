//
// Created by Jakub Malczak on 14/12/2023.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <type_traits>
using namespace std;

// podpunkt 1.
template <typename T>
void serialize(ostream& out, const T& value)
{
    out.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
void deserialize(istream& in, T& value)
{
    in.read(reinterpret_cast<char*>(&value), sizeof(T));
}

// podpunkt 2.
template <>
void serialize(ostream& out, const string& s)
{
    size_t length = s.length();
    out.write(reinterpret_cast<const char*>(&length), sizeof(length));
    out.write(s.c_str(), length);
}

template<>
void deserialize(istream& in, string& s)
{
    size_t length;
    in.read(reinterpret_cast<char*>(&length), sizeof(length));
    s.resize(length);
    in.read(&s[0], length);
}

// podpunkt 3.
template <typename T>
typename enable_if<is_arithmetic_v<T> || is_same_v<T, std::string>, void>::type
serialize_array(ostream& out, const T* array, size_t size)
{
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        serialize(out, array[i]);
    }
}

template <typename T>
typename enable_if<is_arithmetic_v<T> || is_same_v<T, std::string>, pair<T*, size_t>>::type
deserialize_array(istream& in)
{
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    T* array = new T[size];
    for (size_t i = 0; i < size; ++i) {
        deserialize<T>(in, array[i]);
    }
    return make_pair(array,size);
}

// podpunkt 4.
class Serializable {
public:
    virtual void serialize(ostream& out) const = 0;
    virtual void deserialize(istream& in) = 0;
};

class Color : public Serializable {
    int red, green, blue;
public:
    Color(int r = 0, int g = 0, int b = 0) : red(r), green(g), blue(b) {}

    void serialize(ostream& out) const override {
        ::serialize(out, red);
        ::serialize(out, green);
        ::serialize(out, blue);
    }

    void deserialize(istream& in) override {
        ::deserialize(in, red);
        ::deserialize(in, green);
        ::deserialize(in, blue);
    }

    friend ostream& operator<<(ostream& os, const Color& c) {
        os << "(" << c.red << "," <<  c.green << "," << c.blue << ")";
        return os;
    }
};

class Person : public Serializable {
    string name, surname;
    int weight;
    double height;
    Color eye_color;
public:
    Person(string n = "", string s = "", int w = 0, double h = 0, Color ec = Color())
        : name(n), surname(s), weight(w), height(h), eye_color(ec) {}

    void serialize(ostream& out) const override {
        ::serialize(out, name);
        ::serialize(out, surname);
        ::serialize(out, weight);
        ::serialize(out, height);
        eye_color.serialize(out);
    }

    void deserialize(istream& in) override {
        ::deserialize(in, name);
        ::deserialize(in, surname);
        ::deserialize(in, weight);
        ::deserialize(in, height);
        eye_color.deserialize(in);
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.name << " " << p.surname << " " << p.weight << "kg "
           << p.height << "cm " << p.eye_color;
        return os;
    }
};

//podpunkt 5.
template <typename T>
typename enable_if<std::is_base_of_v<Serializable, T>, void>::type
serialize_array(ostream& out, const T* array, size_t size)
{
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        array[i].serialize(out);
    }
}

template <typename T>
typename enable_if<std::is_base_of_v<Serializable, T>, pair<T*, size_t>>::type
deserialize_array(istream& in)
{
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    T* array = new T[size];
    for (size_t i = 0; i < size; ++i) {
        array[i] = T();
        array[i].deserialize(in);
    }
    return make_pair(array,size);
}



int main() {

    {
        bool my_bool = true;
        char my_char = 'x';
        short my_short = 123;
        int my_int = 123456;
        long long my_long_long = 123456789;
        float my_float = 1.23;
        double my_double = 1.23456;
        long double my_long_double = 1.23456789;

        ofstream out("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        serialize(out, my_bool);
        serialize(out, my_char);
        serialize(out, my_short);
        serialize(out, my_int);
        serialize(out, my_long_long);
        serialize(out, my_float);
        serialize(out, my_double);
        serialize(out, my_long_double);
        out.close();

        bool read_bool;
        char read_char;
        short read_short;
        int read_int;
        long long read_long_long;
        float read_float;
        double read_double;
        long double read_long_double;

        ifstream in("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        deserialize(in, read_bool);
        deserialize(in, read_char);
        deserialize(in, read_short);
        deserialize(in, read_int);
        deserialize(in, read_long_long);
        deserialize(in, read_float);
        deserialize(in, read_double);
        deserialize(in, read_long_double);
        in.close();

        cout << "Test podpunktu pierwszego: " << endl;
        cout << boolalpha << fixed << setprecision(10);
        cout << my_bool << " == " << read_bool << endl;
        cout << my_char << " == " << read_char << endl;
        cout << my_short << " == " << read_short << endl;
        cout << my_int << " == " << read_int << endl;
        cout << my_long_long << " == " << read_long_long << endl;
        cout << my_float << " == " << read_float << endl;
        cout << my_double << " == " << read_double << endl;
        cout << my_long_double << " == " << read_long_double << endl;
        cout << endl;
    }

    {
        string my_string = "serializacja i deserializacja";

        ofstream out("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        serialize(out, my_string);
        out.close();

        string read_string;

        ifstream in("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        deserialize<string>(in, read_string);
        in.close();

        cout << "Test podpunktu drugiego: " << endl;
        cout << my_string << " == " << read_string << endl;
        cout << endl;
    }

    {
        size_t ints_size = 3;
        int ints[] = {1,2,3};

        ofstream out("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        serialize_array(out, ints, ints_size);
        out.close();

        ifstream in("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        auto [read_array, read_size] = deserialize_array<int>(in);
        in.close();

        cout << "Test podpunktu trzeciego: " << endl;
        cout << ints_size << " == " << read_size << endl;
        cout << "{" << ints[0] << "," << ints[1] << "," << ints[2] << "} == " <<
                "{" << read_array[0] << "," << read_array[1] << "," << read_array[2] << "}" << endl;
        cout << endl;
    }

    {
        Person p1("Jakub", "Malczak", 83, 187.5, {128,123,240});

        ofstream out("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        p1.serialize(out);
        out.close();

        Person p2;

        ifstream in("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        p2.deserialize(in);
        in.close();

        cout << "Test podpunktu czwartego: " << endl;
        cout << fixed << setprecision(2);
        cout << p1 << " == " << p2 << endl;
        cout << endl;
    }

    {
        size_t persons_size = 3;
        Person persons[] = {Person("Jan","Kowalski",80,189.99, {136,234,244}),
                            Person("Jakub", "Malczak", 83, 187.5, {128,123,240}),
                            Person("Emilia", "Nowak", 55, 160.44, {99,89,2})};

        ofstream out("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        serialize_array(out, persons, persons_size);
        out.close();

        ifstream in("/Users/jakubmalczak/CLionProjects/STLtasks/lista9/zadanie6.bin", ios::binary);
        auto [read_array, read_size] = deserialize_array<Person>(in);
        in.close();

        cout << "Test podpunktu piątego: " << endl;
        cout << persons_size << " == " << read_size << endl;
        cout << "{" << persons[0] << "," << persons[1] << "," << persons[2] << "} == " <<
                "{" << read_array[0] << "," << read_array[1] << "," << read_array[2] << "}" << endl;
        cout << endl;
    }
}
