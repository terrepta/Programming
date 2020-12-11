#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//функция сортировки для одномерного массива
 vector<int> BozoSort(vector<int>array, int num, bool b = 1) {
    bool check = 1;
    while (check) {
        check = 0;
        int a1 = rand() % num;      //выбираем рандомные элементы массива
        int a2 = rand() % num;
        swap(array[a1],array[a2]); //меняем элементы местами
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

//функция сортировки для двумерного массива
vector<int> BozoSort(vector<vector<int>> matrix, int n, bool b = 1) {
    int num = pow(n,2);
    int k = 0;
    vector<int>array(num);
    while (k < num) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    array[k] = matrix[i][j];
                    k++;
            }
        }
    }
    if (b) return BozoSort(array,num);
    else return BozoSort(array,num, false);
}

//функция сортировки первых трех элементов
vector<int> BozoSort(vector<int> array, int a1, int a2, int a3, bool b = 1) {
    array.resize(3);
    array[0] = a1;
    array[1] = a2;
    array[2] = a3;
   
    if (b) return BozoSort(array, 3);
    else return BozoSort(array, 3, false);
}

//функция вывода массива с num количеством эл.
void out(vector<int>array, int num) {
    for (int i = 0; i < num; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}
int main() {
    setlocale(LC_ALL, "russian");
    int num;
    int a;
    cout << "Введите количество чисел, требующих сортировки: ";
    cin >> num;

    vector<int>array;

    cout << "Задайте числа для сортировки\n";
    for (int i = 0; i < num; i++) {
        cin >> a;
        array.push_back(a);
    }

    int n = sqrt(num);
    vector<vector<int>>matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = array[i * n + j];
        }

    int a1 = array[0];
    int a2 = array[1];
    int a3 = array[2];

    out((BozoSort(array, num)), num);
    out((BozoSort(array, num, false)), num);
    out((BozoSort(matrix, n)), num);
    out((BozoSort(matrix, n, false)), num);
    out((BozoSort(array, a1, a2, a3)), 3);
    out((BozoSort(array, a1, a2, a3, false)), 3);
}