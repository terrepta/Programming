#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	int n[37], numb, red = 0, black = 0, a = 0;					//в массиве всего 37 элементов, т.к. на поле числа от 0 до 36 
	int r[18] = { 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };
	int b[18] = { 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35 };

	for (int i = 0; i < 37; i++) n[i] = 0;						//всем числам присваивается нулевое значение

	while (1) {
		cout << "Введите число\n";
		cin >> numb;
		if (numb < 0 || numb > 36) break;
		else {
			n[numb]++;
			for (int color=0; color < 18; color++) {
				if (numb == r[color])   red+=1;					//подсчёт красных и черных фишек
				else if(numb==b[color])   black+=1;
			}
		}
		for (int s = 0; s < 37; s++) {
			if (n[s] > a)   a = n[s];							//a принимает введенное значение
		}
		for (int s = 0; s < 37; s++) {							//вывод чисел, поаторяющихся чаще всего
			if (n[s] == a)   cout << s << " ";
		}
		cout << "\n";
		for (int s = 0; s < 37; s++) {
			if (n[s] == 0)   cout << s << " ";					//вывод чисел, не выпавших за последние игры
		}
		cout << "\n" << red << " " << black <<"\n";
		
	}
	return 0;
}