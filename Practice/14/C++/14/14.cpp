#include <iostream>
using namespace std;

int recf(int n)
{
	int counter = 1;
	int factor = 2;

	if (n == 0) return 0;

	while (factor <= n) {
		factor *= 2;
		counter +=1;
	}
	return counter;
}

int main()
{
	setlocale(LC_ALL, "russian");
	int n;

	cout << "Введите число\n";
	cin >> n;
	if (n < 0) cout << "Неверные данные.";
	else cout << "Количество степеней двойки: "<< recf(n) << '\n';

	return 0;
}