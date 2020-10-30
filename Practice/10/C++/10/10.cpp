#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "russian");
	long int s, l1,r1, l2, r2, x1, x2, lr2, dist;
	cout << "Введите значения s, l1, r1, l2, r2\n";
	cin >> s >> l1 >> r1 >> l2 >> r2;
	lr2 = r2 - l2;

	x1 = l1;          //т. к. х1 должен быть наименьшим возможным из своего промежутка
	x2 = s - x1;

	if (x2 < l2) {
		dist = l2 - x2;
		if (dist < lr2) {
			x2 += dist;
			x1 -= dist;
			cout << x1 << " " << x2;
		}
		else {
			cout << "-1";
			return 0;
		}
	}
	else if (x2 > r2) {
		dist = x2 - r2;
		if (dist < lr2) {
			x2 -= dist;
			x1 += dist;
			cout << x1 << " " << x2;
		}
		else {
			cout << "-1";
			return 0;
		}
	}
	else cout << x1 << " " << x2;

return 0;
}
