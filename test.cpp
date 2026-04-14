#include <iostream>
#include <vector>
#include <string>
#include "main.cpp"
using namespace std;
using namespace core_numeric;

int main() {

    vector<int> v1 = {1, 2, 3, 4};
    cout << "Sum int: " << sum(v1) << endl;
    cout << "Mean int: " << mean(v1) << endl;
    vector<double> v2 = {1.5, 2.5, 3.5};
    cout << "Variance double: " << variance(v2) << endl;
    cout << "Max int: " << max(v1) << endl;
    cout << "Transform reduce: " << transform_reduce<Square>(v2) << endl;

    cout << "Sum variadic: " << sum_variadic(1, 2, 3, 4) << endl;
    cout << "Mean variadic: " << mean_variadic(1.0, 2.0, 3.0) << endl;
    cout << "Max variadic: " << max_variadic(5, 10, 3, 8) << endl;
    return 0;
}
