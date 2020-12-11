#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//функция сортировки для одномерного массива
template<class T>
 vector<T> BozoSort(vector<T>array, int num, bool b = 1) {
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
template<class T>
vector<T> BozoSort(vector<vector<T>> matrix, int n, bool b = 1) {
    int num = pow(n,2);
    int k = 0;
    vector<T>array(num);
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
template<class T>
vector<T> BozoSort(vector<T> array, T a1, T a2, T a3, bool b = 1) {
    array.resize(3);
    array[0] = a1;
    array[1] = a2;
    array[2] = a3;
   
    if (b) return BozoSort(array, 3);
    else return BozoSort(array, 3, false);
}

//функция вывода массива с num количеством эл.
template<class T>
void out(vector<T>array, int num) {
    for (int i = 0; i < num; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "russian");
    int d_num, str_num;
    //целые числa
    double d_a;
    cout << "Введите количество элементов массива чисел, требующих сортировки: ";
    cin >> d_num;
    int n = sqrt(d_num);

    vector<double>d_array;

    cout << "Задайте числа для сортировки\n";
    for (int i = 0; i < d_num; i++) {
        cin >> d_a;
        d_array.push_back(d_a);
    }

    vector<vector<double>>d_matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            d_matrix[i][j] = d_array[i * n + j];
        }
    //строки
    string str_a;
    cout << "Введите количество элементов массива сктрок, требующих сортировки: ";
    cin >> str_num;
    n = sqrt(str_num);

    vector<string>str_array;
    
    cout << "Задайте числа для сортировки\n";
    for (int i = 0; i < str_num; i++) {
        cin >> str_a;
        str_array.push_back(str_a);
    }

    vector<vector<string>>str_matrix(n, vector<string>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            str_matrix[i][j] = str_array[i * n + j];
        }

    cout << endl;
    out((BozoSort(d_array, d_num)), d_num);
    out((BozoSort(d_array, d_num, false)), d_num);
    out((BozoSort(d_matrix, n)), d_num);
    out((BozoSort(d_matrix, n, false)), d_num);
    out((BozoSort(d_array, d_array[0], d_array[1], d_array[2])), 3);
    out((BozoSort(d_array, d_array[0], d_array[1], d_array[2], false)), 3);

    out((BozoSort(str_array, d_num)), d_num);
    out((BozoSort(str_array, d_num, false)), d_num);
    out((BozoSort(str_matrix, n)), d_num);
    out((BozoSort(str_matrix, n, false)), d_num);
    out((BozoSort(str_array, str_array[0], str_array[1], str_array[2])), 3);
    out((BozoSort(str_array, str_array[0], str_array[1], str_array[2], false)), 3);

}