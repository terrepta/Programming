#include <iostream>
#include <string>
using namespace std;

int main()
{
setlocale(LC_ALL, "russian");
int numb, i=0;
cout << "Введите количество билетов\n";
cin >> numb;
cout << " Через пробел введите номера данных " << numb << " билетов\n";
string tickets = "";
while (numb > i) {
	string t;
	cin >> t;
	if (t[0] == 'a' && t[4] == 5 && t[5] == 5 && t[6] == 6 && t[7] == 6 && t[8] == 1)
		tickets += t;
	numb -= 1;
}
//cout << tickets;
if (tickets == "") cout << "-1";
else cout << tickets;
return 0;
}
