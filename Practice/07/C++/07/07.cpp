#include <iostream>

int main()
{
    setlocale(LC_ALL, "russian");
    int num;
    std::cin >> num;

    if (num == 1) {
        double a, b, c;
        std::cin >> a >> b >> c;
        double p = (a + b + c) / 2;
        if (a > 0 && b > 0 && c > 0) {
            std::cout << "S = " << sqrt(p * (p - a) * (p - b) * (p - c));
        }
        else {
            std::cout << " Введены некорректные данные.\n Длины сторон треугольника не могут быть отрицательными или равняться нулю.\n Введите новые данные." << '\n';
            return 1;
        }
    }
    else if (num == 2) {
        double ax, ay, bx, by, cx, cy;
        std::cin >> ax >> ay;
        std::cin >> bx >> by;
        std::cin >> cx >> cy;
        if ((ax == bx && ay == by) || (ax == cx && ay == cy) || (bx == cx && by == cy)) {
            std::cout << " Введены некорректные данные.\n Длины сторон треугольника не могут быть отрицательными или равняться нулю.\n Введите новые данные." << '\n';
            return 1;
        }
        else {
            double ab = sqrt(pow((bx - ax), 2) + pow((by - ay), 2));
            double ac = sqrt(pow((cx - ax), 2) + pow((cy - ay), 2));
            double bc = sqrt(pow((cx - bx), 2) + pow((cy - by), 2));
            double p = (ab + ac + bc) / 2;
            std::cout << "S = " << sqrt(p * (p - ab) * (p - ac) * (p - bc));
        }
    }
    return 0;
}