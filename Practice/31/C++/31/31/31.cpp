﻿#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ostream& operator << (ostream& out, const vector<int>& vector) {
	out << vector.size() << "\t| ";

	for (int i = 0; i < vector.size(); i++) {
		out << &vector[i] << " ";
	}
	out << "\n";
	return out;
}

// III часть задания
/*ostream& operator << (ostream& out, const vector<int> vector) {
	out << vector.size() << "\t| ";

	for (int i = 0; i < vector.size(); i++) {
		out << &vector[i] << " ";
	}
	out << "\n";
	return out;
}*/

int main() {
	vector<int> empty;
	ofstream out_file("data.txt");

	for (int i = 0; i < 64; i++) {
		empty.push_back(i);
		out_file << empty;
	}
	// II часть задания
	for (int i = 63; i > 0; i--) {
		empty.pop_back();
		out_file << empty;
	}
	out_file.close();
}
/*
1) Замеченная закономерность: 
У первых четырех строк адреса попарно не совпадают, далее встречаются повторения 
адресов элементов для нескольких строк, после чего адреса вновь обновляются. Так, например,
0-4 элементы пятой и шестой строки попарно совпали, далее адреса элементов изменились
и в 7-9 строках попарно соответствовали элементы с совершенно другими адресами. Количество 
строк с одинаковыми адресами постепенно растет: сначала соответствие просматривалось только
в двух строках подряд (5-6), к концу выполнения программы - в 21 (43-63 строки). Адреса 
64 строки вновь обновляются.

Почему  адреса обновляются с такой переодичностью я не поняла, но поняла, что это
происходит из-за того, что оператор передает данные аргумента по ссылке: при таком раскладе
копия передаваемого аргумента создаваться не будет, соответственно, адреса элементов будут 
меняться только тогда, когда для добавления нового элемента места в памяти будет недостаточно.
В таком случае вектор будет копироваться с новыми адресами, а предыдущий участок памяти будет
очищаться.

2)

3) Адреса элементов изменяться не будут, так как элементы удаляются из уже созданного вектора,
на который была выделена определенная память.

4) Адреса одного и того же элемента в разных строках при его удалении теперь не совпадают. 
Это происходит из-за того, что теперь оператор передает аргументы по значению, а не по 
ссылке: создается копия имеющегося вектора, а элементы копии не могут иметь такие же адреса,
как у изначального.
*/