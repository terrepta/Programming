
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    double x, y;
    cout << " Введите координаты x и y точки\n";
    cin >> x >> y;
    if ((((x - 1) * (x - 1) + y * y) <= 1) ||( (y <= x) && (y >= -0.5)) {
        cout << "Точка принадлежит заданной области.";
    }
    else {
        cout << "Точка не принадлежит заданной области.";
    }

}



