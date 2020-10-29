#include <iostream>
#include <string>
using namespace std;

int main()
{
setlocale(LC_ALL, "russian");
int numb;
string tickets;
string t="";

cout << "Введите количество билетов\n";
cin >> numb;
cout << " Через пробел введите номера данных " << numb << " билетов\n";
while (numb > 0) {
	getline(cin, t);
	numb -= 1;
}
if (t[0] == 'a' && t[4] == 5 && t[5] == 5 && t[6] == 6 && t[7] == 6 && t[8] == 1)
		tickets += t;

cout << tickets;
return 0;
}
