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
    { a / n };
};

//para usarlo en el max
template <typename T>
concept Comparable = requires (T a, T b) {
    { a > b } -> same_as<bool>;
};

template<typename F, typename T>
concept Reduccion = requires(F f, T x) {
    { f(x) } -> std::convertible_to<T>;
};

//para poder usarlo como parametro template
struct Square {
    double operator()(double x) const {
        return x * x;
    }
};

template <typename T, typename... Mt>
concept Multiple = (std::same_as<T, Mt> && ...);

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
        typename C::value_type m = *begin(c);
        for (const auto& x : c) {
            if (m < x) m = x;
        }
        return m;
    }
    template <typename F, Iterable C>
    requires Reduccion<F, typename C::value_type> && Addable<typename C::value_type>
    auto transform_reduce(const C& c) {
        typename C::value_type result{};
        F f; // instancia de la funcion
        for (const auto& x : c) {
            result += f(x);
        }
        return result;
    }
    //funciones que aceptan las multiples variables
    template<typename T, typename... Mt>
    requires Multiple<T, Mt...> && Addable<T>
    auto sum_variadic(T init, Mt... fin) {
        return (init + ... + fin);
    }
    template<typename T, typename... Mt>
    requires Multiple<T, Mt...> && Addable<T>
    auto mean_variadic(T init, Mt... fin) {
        auto sum = (init + ... + fin);
        auto tam =sizeof...(fin) + 1;
        if constexpr (std::is_integral_v<T>) {
            return static_cast<double>(sum) / tam; //convertir para evitar truncamiento
        } else {
            return sum / tam; //ya es flotante
        }
    }
    template<typename T, typename... Mt>
    requires Multiple<T, Mt...> && Addable<T>
    auto variance_variadic(T init, Mt... rest) {
        auto m = mean_variadic(init, rest...);
        auto tam = 1 + sizeof...(rest);
        auto sumvar = (((init - m) * (init - m) )+ ... + (((rest - m) * (rest - m))));
        return sumvar / tam;
    }
    template<typename T, typename... Mt>
    requires Multiple<T, Mt...> && Comparable<T>
    auto max_variadic(T init, Mt... rest) {
        T max_val = init;
        ((max_val = (max_val < rest ? rest : max_val)), ...);
        return max_val;
    }
}