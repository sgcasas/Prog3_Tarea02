#include <iostream>
#include <concepts>
#include <iterator>
using namespace std;

template <typename C>
concept Iterable = requires (C c) {
    begin(c);
    end(c);
};

template <typename T>
concept Addable = requires (T a, T b) {
    { a + b } -> same_as<T>;
};

template <typename T>
concept Divisible = requires (T a, size_t n) {
    { a / n } -> same_as<T>;
};

//para usarlo en el max
template <typename T>
concept Comparable = requires (T a, T b) {
    { a > b } -> same_as<bool>;
};

namespace core_numeric {
    //funcion para sumar todos los elementos de un container
    template<Iterable C>
    requires Addable<typename C::value_type>
    auto sum(const C& c) {
        typename C::value_type s = 0;
        for (const auto& x : c) { s += x; }
        return s;
    }
    template <Iterable C>
    requires Divisible<typename C::value_type> && Addable<typename C::value_type>
    auto mean(const C& c) {
        typename C::value_type p = sum(c);
        auto t = size(c);
        return p / t;
    }
    template<Iterable C>
    requires Divisible<typename C::value_type> && Addable<typename C::value_type>
    auto variance(const C& c) {
        typename C::value_type m = mean(c);
        auto t = size(c);
        typename C::value_type s = 0;
        for (int i = 0; i < t; i++) { s += pow(c[i] - m, 2); }
        return s / t;
    }
    template <Iterable C>
    requires Comparable<typename C::value_type>
    auto max(const C& c) {
        typename C::value_type m = begin(c);
        for (const auto& x : c) {
            if (m < x) m = x;
        }
        return m;
    }
}

int main() {

    return 0;
}