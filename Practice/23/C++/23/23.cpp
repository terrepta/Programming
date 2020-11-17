#include <iostream>
#include <iomanip> 
#include "fact_n.h"
#include "sin_x.h"
#include "comb_n.h"
using namespace std;

int main()
{
    cout << "n\tn!\n";
    for (int n = 1; n <= 10; n++) {
        cout << n << "\t" << fact_n(n) << "\n"; //вывод таблицы факториалов
    }

    const double pi = 3.14159265358979323;
    cout <<"\n" << "x\tsin(x)\n";
    for (double x = 0; x <= pi / 4; x += pi / 180) {
        cout << x << "\t" << setprecision(4) << sin_x(x, 5) << "\n"; //вывод таблицы синусов
    }

    cout << "\n" << "k\tC(k,10)\n";
    for (int k = 1; k <= 10; k++) {
        cout << k << "\t" << comb_n(k, 10) << "\n"; //вывод таблицы сочетаний
    }
}
