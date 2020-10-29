#include <iostream>
using namespace std;

int factorial(int numb) {
	if (numb == 0) {
		return 0;
	}
	else if (numb == 1) {
		return 1;
	}
	else {
		return numb * factorial(numb - 1);
	}
}

int main() {
	setlocale(LC_ALL, "russian");
	int numb;
	cout << "Введите число, факториал которого предстоит найти\n";
	cin >> numb;
	cout << "Результат:" << factorial(numb);
	return 0;
}
