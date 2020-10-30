#include <iostream>
#include <string>
using namespace std;

int main() {
	setlocale(LC_ALL, "russian");
	int numb, exit = 0, i = 1; 

	cout << "Введите количество билетов\n";
	cin >> numb;
	cout << "Через пробел ведите номера данных " << numb << " билетов\n";

	string ticket{};
	for (i ; i <= numb; i++)
	{
		cin >> ticket;
		if (ticket[0] == 'a' && ticket[4] == '5' && ticket[5] == '5' && ticket[6] == '6' && ticket[7] == '6' && ticket[8] == '1') 
			cout << ticket << ' ';
		else exit += 1;
	}
	if (exit == numb) cout << "-1";

	return 0;
}
