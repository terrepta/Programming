#include <iostream>
#include <vector>
using namespace std;

vector<int> sort(vector<int>array, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] < array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
    return array;
}

int main()
{
    setlocale(LC_ALL, "russian");
    int n, a;
    vector<int> in_array;
    cout << "Введите количество поступивших сигналов\n";
    cin >> n;
    cout << "Запишите данные числа\n";
    for (int i = 0; i < n; i++) {
        cin >> a;
        in_array.push_back(a);
    }
    vector<int> temp;
    vector<int> out_array;
    for (int i = 1; i < n+1; i++) {
        out_array = sort(in_array, i);
        if (i <= 5) {
            for (int j = 0; j < i; j++) {
                cout << out_array[j] << " ";
            }
            cout << endl;
        }
        else {
            for (int j = i - 5; j < i; j++)
            {
                cout << out_array[j] << " ";
            }
            cout << endl;
        }
    }
}
