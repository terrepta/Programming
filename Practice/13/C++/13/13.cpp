#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "russian");

	int n, i = 2;
	cout << "Введите число для проверки\n";
	cin >> n;

	if ((n <= 0) || (n == 1)) {             //ноль не явл. натуральным числом, а единица не относится ни к простым, ни к составным числам.
		cout << "Не является ни простым, ни составным.";
		return 0;
	}
	else {
		while (sqrt(n) >= i) {             //делители любого числа a не превосходят число, равное корню из данного числа а.
			if ((sqrt(n) >= i) && ((n % i == 0) || (n % 5 == 0))) {
				cout << "Составное";
				return 0;
			}
			else if ((sqrt(n > i)) && (n % i != 0)) {
				cout << "Простое";
				return 0;
			}
			i += 1;
		}
	}
return 0;
}
