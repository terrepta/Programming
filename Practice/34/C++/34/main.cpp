#include <iostream>
#include <string>

using namespace std;

int* create(int*& output_arr, int l, int initial = 0, int step = 0) {
    int* array = new int[l];

    array[0] = initial;
    for (int i = 1; i < l; i++) {
        array[i] = array[i - 1] + step;
    }
    return array;
}

void sort(int* array, int l) {
    for (int i = 1; i < l; i++) {
        int buff = array[i];
        int j = i - 1;

        while (j >= 0 && buff < array[j]) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = buff;
    }
}

string print(int* const array, int l) {
    string out = "[";
    for (int i = 0; i < l - 1; i++) {
        out += to_string(array[i]) + ", ";
    }
    out += to_string(array[l - 1]) + "]";
    return out;
}

void destroy(int*& array) {
    if (array != nullptr) {
        delete[] array;
        array = nullptr;
    }
}

int main() {
    int l, initial, step;
    cin >> l >> initial >> step;

    int* array = create(array, l, initial, step);
    sort(array, l);
    string out = print(array, l);
    cout << out;
    destroy(array);
}
