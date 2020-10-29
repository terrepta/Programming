#include <iostream>
using namespace std;
int main()
{
setlocale(LC_ALL, "russian");
int answ;
int ident=1;
while (ident == 1) {
	int i = 0;
	int numb = rand() % 101;
	cout << "\tПриветствую!\n Сейчас компьютер загадает число. У вас будет 5 попыток, чтобы его отгадать.\n Введите целое число.\n";
	while (i < 5) {
		cin >> answ;
		if (answ < numb) cout << "Загаданное число больше\n";
		else if (answ > numb) cout << "Загаданное число меньше\n";
		else {
			cout << "Поздравляю! Вы угадали!\n\nХотите начать сначала? (1-ДА)\n";
			cin >> ident;
			break;
		}
		i += 1;
		if (i == 5) {
			cout << "Вы проиграли. Было загадано:"<<numb<<"\n\nХотите начать сначала? (1-ДА)\n";
			cin >> ident;
			break;
		}
	}
}
}

