#include <iostream>
#include <vector>
#include <string>
#include "core_numeric.cpp"
using namespace std;
using namespace core_numeric;

int main() {
    // Casos que si compilan
    vector<int> v1{1, 2, 3};
    vector<double> v2{1.0, 2.0, 3.0};
    sum(v1);
    sum(v2);
    auto m = mean(v2);
    auto var = variance(v2);
    vector<double> v3{1, 2.7, 0.3};
    auto max_ = core_numeric::max(v3);
    auto r = transform_reduce<Square>(v2);
    auto s1 = sum_variadic(1,2,3,4);
    auto s2 = mean_variadic(0.1,2.0,3);
    auto s3 = variance_variadic(1,2,3.0,4);
    auto s4 = max_variadic(1.0,2,3.0,4);
    cout << m << endl;
    cout << var << endl;
    cout << r << endl;
    cout << max_ << endl;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;

    /*
    // Casos que no compilan
    vector<string> words{"Hola", "Mundo"};
    auto x = add("Hola", "Mundo"); //ERROR: const char* no cumple Addable
    sum(words); //ERROR: string cumple Addable pero la implementacion puede fallar en otros concepts
    variance(words); //ERROR: string no cumple Divisible / Addable correctamente
    max(words); //ERROR: según la tarea, string no debe cumplir Comparable
    int x = 5;
    sum(x); //ERROR: no cumple Iterable
    vector<Addable> vna{{1},{2}};
    sum(vna); // ERROR: no cumple Addable
    auto bad = sum_variadic(1, 2.5, 3); //ERROR: no cumple Multiple
    struct Func {
        string operator()(int x) { return "hola"; }
    };
    auto func2 = transform_reduce<Func>(v1); //ERROR: no cumple Reduccion

    */
    return 0;
}
