#include <iostream>

int main()
{
    setlocale(LC_ALL, "russian");

    double a, b;
    char sign;
    std::cin >> a >> sign >> b;

    if (b == 0 && sign == '/') {
        std::cout << "Ошибка. Деление на ноль невозможно.\n Введите новые значения.\n";
    }

    switch (sign) {
    case '+':
        std::cout << a + b;
        break;
    case '-':
        std::cout << a - b;
        break;
    case '*':
        std::cout << a * b;
        break;
    case '/':
        std::cout << a / b;
        break;
    default:
        break;
    }
    return 0;
}
