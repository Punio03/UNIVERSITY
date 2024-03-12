//
// Created by Jakub Malczak on 03/01/2024.
//
#include <iostream>
#include <fstream>
#include <type_traits>
using namespace std;

template <typename T>
void serialize(fstream& out, const T& value)
{
  out.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
void deserialize(fstream& in, T& value)
{
  in.read(reinterpret_cast<char*>(&value), sizeof(T));
}


template<typename T>
struct obj_holder
{
    struct on_stack {
    private:
        T obj;
    public:
        on_stack() {}
        on_stack(const on_stack&) = delete;
        on_stack& operator=(const on_stack&) = delete;

        T& operator*() { return obj; }
        T* operator->() { return &obj; }
    };

    struct on_heap {
    private:
        T* obj;
    public:
        on_heap() : obj(new T) {}
        ~on_heap() { delete obj; }
        on_heap(const on_heap&) = delete;
        on_heap& operator=(const on_heap&) = delete;

        T& operator*() { return *obj; }
        T* operator->() { return obj; }
    };

    using type = conditional<
            sizeof(T) <= sizeof(string) && !is_array_v<T>,
            on_stack,
            on_heap
    >::type;
};

template<typename T, size_t N>
struct arr_holder
{
    struct array_on_heap {
    private:
        T* array;
        size_t size;
    public:
        array_on_heap() : size(N), array(new T[N]) {}
        ~array_on_heap() { delete[] array; }
        array_on_heap(const array_on_heap&) = delete;
        array_on_heap& operator=(const array_on_heap&) = delete;

        T& operator[](size_t index) { return array[index]; }

        size_t length() const { return size; }
    };

    struct array_in_file {
    private:
        fstream file;
        size_t size;
    public:
        array_in_file() : size(N)
        {
          file.open("/Users/jakubmalczak/CLionProjects/STLtasks/lista11/zadanie5.bin", ios::in | ios::out | ios::binary | ios::trunc);

          T value = T();
          for (size_t i = 0; i < N; ++i)
          {
            serialize(file, value);
          }
        }
        ~array_in_file() { file.close(); }
        array_in_file(const array_in_file&) = delete;
        array_in_file& operator=(const array_in_file&) = delete;

        T operator[](size_t index)
        {
          T value;
          file.seekg(index * sizeof(T));
          deserialize(file, value);
          return value;
        }

        void set(size_t index, const T& value)
        {
          file.seekp(index * sizeof(T));
          serialize(file, value);
        }

        size_t length() const { return size; }
    };

    using type = std::conditional<
            sizeof(T) * N <= 1024 || !is_arithmetic_v<T>,
            array_on_heap,
            array_in_file
    >::type;
};

int main()
{
  // on_stack
  obj_holder<int>::type myIntHolder;
  *myIntHolder = 10;
  cout << "Wartość: " << *myIntHolder << endl;

  // on_heap
  struct BigObject { int data[1000]; };
  obj_holder<BigObject>::type myBigObjectHolder;
  (*myBigObjectHolder).data[0] = 5;
  cout << "Wartość: " << (*myBigObjectHolder).data[0] << endl;

  // array_on_heap
  arr_holder<int, 10>::type myArray;
  for (size_t i = 0; i < myArray.length(); ++i)
  {
    myArray[i] = i;
  }

  for (size_t i = 0; i < myArray.length(); ++i)
  {
    cout << myArray[i] << " ";
  }
  cout << endl;

  // array_in_file
  arr_holder<int, 300>::type myLargeArray;
  for (size_t i = 0; i < myLargeArray.length(); ++i)
  {
    myLargeArray.set(i, i);
  }

  for (size_t i = 0; i < myLargeArray.length(); ++i)
  {
    cout << myLargeArray[i] << " ";
  }
  cout << endl;
}


