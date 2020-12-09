#include <iostream>
#include <vector>
using namespace std;

//функция сортировки для одномерного массива
vector<int> BozoSort(vector<int>array, int num, bool b = 1) {
    bool check = 1;
    while (check) {
        check = 0;
        int a1 = rand() % num;      //выбираем рандомные элементы массива
        int a2 = rand() % num;
        int temp = array[a1];
        array[a1] = array[a2];      //меняем элементы местами
        array[a2] = temp;
        if (b) {                    //если b = true - сортировка по возрастанию
            for (int i = 0; i < num - 1; i++) {
                if (array[i] > array[i + 1]) {
                    check = 1;
                    break;
                }
            }
        }
        else {                      //иначе - сортировка по убыванию
            for (int i = 0; i < num - 1; i++) {
                if (array[i] < array[i + 1]) {
                    check = 1;
                    break;
                }
            }
        }
    }
    return array;
}

//функция вывода массива с num количеством эл.
void out(vector<int>array, int num) {
    for (int i = 0; i < num; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}
int main() {
    int num;
    int a;
    vector<int>array;
    setlocale(LC_ALL, "russian");
    cout << "Введите количество чисел, требующих сортировки: ";
    cin >> num;
    cout << "Задайте числа для сортировки\n";
    for (int i = 0; i < num; i++) {
        cin >> a;
        array.push_back(a);
    }
    out((BozoSort(array, num)), num);
    out((BozoSort(array, num, false)), num);
}