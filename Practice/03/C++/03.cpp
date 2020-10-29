#include <iostream>

int main()
{
    setlocale(LC_ALL, "russian");

    int a_int, b_int;
    std::cin >> a_int >> b_int;
    std::cout << "Результат сложения = " << a_int + b_int << '\n';
    std::cout << "Результат вычитания = " << a_int - b_int << '\n';
    std::cout << "Результат умножения = " << a_int * b_int << '\n';
    std::cout << "Результат деления = " << a_int / b_int << '\n';

    /* При операциях над двумя переменными типа int все результаты являются целочисленными.
    В отличии от Python, если при делении получается дробная часть, то она отбрасывается.

    В остальных случаях результат может быть как целым, так и не целым*/

    double a_double, b_double;
    std::cin >> a_double >> b_double;
    std::cout << "Результат сложения = " << a_double + b_double << '\n';
    std::cout << "Результат вычитания = " << a_double - b_double << '\n';
    std::cout << "Результат умножения = " << a_double * b_double << '\n';
    std::cout << "Результат деления = " << a_double / b_double << '\n';
   
    int c_int;
    double c_double;
    std::cin >> c_int >> c_double;
    std::cout << "Результат сложения = " << c_int + c_double << '\n';
    std::cout << "Результат вычитания = " << c_int - c_double << '\n';
    std::cout << "Результат умножения = " << c_int * c_double << '\n';
    std::cout << "Результат деления = " << c_int / c_double << '\n';

    double d_double;
    int d_int;
    std::cin >> d_double >> d_int;
    std::cout << "Результат сложения = " << d_double + d_int << '\n';
    std::cout << "Результат вычитания = " << d_double - d_int << '\n';
    std::cout << "Результат умножения = " << d_double * d_int << '\n';
    std::cout << "Результат деления = " << d_double / d_int << '\n';

    return 0;
}
