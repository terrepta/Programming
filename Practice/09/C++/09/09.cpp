#include <iostream>
using namespace std;

int main()
{
setlocale(LC_ALL, "russian");
int h1, m1, h2, m2, difference;
char sym;

cout << "Введите два значения времени\n";
cin >> h1 >> sym >> m1;
cin >> h2 >> sym >> m2;

if (h1 < 0 || h1 > 23) {
    return 1;
}
if (h2 < 0 || h2 > 23) {
    return 1;
}
if (m1 < 0 || m1 > 59) {
    return 1;
}
if (m2 < 0 || m2 > 59) {
    return 1;
}

if ((m2 < m1) && (h2 != h1 + 1)) {
    m2 += 60 + ((h2 - h1 - 1) * 60);
}

else if ((m2 < m1) || (h2 != h1)) {
    if (m2 < m1) {
        m2 += 60;
    }
    else if (h2 != h1) {
        m2 += (h2 - h1) * 60;
    }
}

difference = m2 - m1;

if (difference <= 15) {
    cout << "Встреча состоится";
}
else {
    cout << "Встреча не состоится";
}
return 0;
}