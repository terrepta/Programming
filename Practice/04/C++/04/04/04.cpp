#include <iostream>

int main()
{
    double a, b;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;

    int c = a;                 //Ввод третьей переменной, равной а.
    a = b;                     //Замена значения a на значение b.
    b = c;                     //Замена значения b на значение а.
    std::cout << "a = " << a << '\n' << "b = " << b << '\n';


    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;

    a += b;                     //Нахождение сумммы чисел
    b = a - b;                  //Замена значения b на значение а
    a -= b;                     //Замена значения a на значение b
    std::cout << "a = " << a << '\n' << "b = " << b;

    return 0;
}