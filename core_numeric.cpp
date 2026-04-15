#include <iostream>
#include <concepts>
#include <iterator>
#include <cmath>
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

// para los variadic
template<typename... Ts>
concept AddableVariadic = requires(Ts... args) {
    (... + args);
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
        for (const auto& x : c) { s = s + (x-m) * (x-m); }
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
    template<typename... Ts>
    requires AddableVariadic<Ts...>
    auto sum_variadic(Ts... args) {
        using Common = std::common_type_t<Ts...>;
        return (Common{} + ... + static_cast<Common>(args));
    }
    template<typename... Ts>
    requires AddableVariadic<Ts...>
    auto mean_variadic(Ts... args) {
        using Common = std::common_type_t<Ts...>;
        Common sum = (Common{} + ... + static_cast<Common>(args));
        return sum / sizeof...(args);
    }
    template<typename... Ts>
    requires AddableVariadic<Ts...>
    auto variance_variadic(Ts... args) {
        using Common = std::common_type_t<Ts...>;
        Common m = mean_variadic(args...);
        Common sum = (pow((Common(args) - m),2) + ...);
        return sum / sizeof...(args);
    }
    template<typename T, typename... Ts>
    auto max_variadic(T first, Ts... rest) {
        using Common = std::common_type_t<T, Ts...>;
        Common max_val = first;
        ((max_val = max_val < rest ? rest : max_val), ...);
        return max_val;
    }
}