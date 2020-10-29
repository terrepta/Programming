#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "russian");
    int pow, i=0;
    double numb, result = 1.0;

    cout << "Ведите число, возводимое в степень\n";
    cin >> numb;
    cout << "Введите степень числа\n";
    cin >> pow;

    if (pow >= 0) {
        while (i < pow) {
            result *= numb;
            i += 1;
        }
    }
    else if (pow < 0) {
        while (pow < i) {
            result = result * (1 / numb);
            i -= 1;
        }
    }
    
    cout << "Результат вычислений:" << result;
    return 0;
}
