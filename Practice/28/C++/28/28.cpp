#include <iostream>
using namespace std;

void print_factorization(unsigned int n) {
    int count = 0;
    if (n > 1) {
        for (int i = 2; i <= n; i++) {
            while (n % i == 0) {
                count++;
                n = n / i;
            }
            if (count > 0) {
                cout << i;
                if (count > 1) cout << "^" << count;
                if (n > 1) cout << "*";
            }
            count = 0;
        }
    }
    else if (n == 1) cout << "-";
}

int main()
{
    setlocale(LC_ALL, "russian");
    int n;
    cout << "Введите число для факторизации\n";
    cin >> n;
    print_factorization(n);
}

