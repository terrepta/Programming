#include <iostream>
#include <string>

using namespace std;

struct IntArray {
    int* data;
    int size;
};

/** Создаёт динамический массив размера size и сохраняет его в поле data переменной arr. Поле size структуры arr становится равным параметру size */
void create(IntArray* arr, int size);
void create(IntArray& arr, int size);

/** Возвращает элемент массива с индексом index, при этом проверяет выход за границы массива. Если index лежит за пределами массива, вывести сообщение об ошибке и прервать работу программы */
int get(IntArray* arr, int index);
int get(IntArray& arr, int index);

/** Изменяет значение элемента массива с индексом index на значение параметра value, при этом проверяет выход за границы массива. Если index лежит за пределами массива, вывести сообщение об ошибке и прервать работу программы */
void set(IntArray* arr, int index, int value);
void set(IntArray& arr, int index, int value);

/** Выводит на экран содержимое массива в формате: [1, 2, 3] */
void print(IntArray* arr);
void print(IntArray& arr);

/** Изменяет размер массива с сохранением элементов. Если новый размер меньше, хвостовые элементы обрезаются, если больше, то дополнительные элементы инициализируются нулём */
void resize(IntArray* arr, int newSize);
void resize(IntArray& arr, int newSize);

/** Освобождает память занятую массивом. Поле data становится равным nullptr, поле size становится равным нулю. Предусмотреть случай попытки удаления уже удалённого массива */
void destroy(IntArray* arr);
void destroy(IntArray& arr);


void create(IntArray& arr, int size) {
    arr.data = new int[size];
    arr.size = size;
}
void create(IntArray* arr, int size) {
    create(*arr, size);
}

int get(IntArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cout << "index out of range";
        return 0;
    }
    return arr.data[index];
}
int get(IntArray* arr, int index) {
    return get(*arr, index);
}

void set(IntArray& arr, int index, int value) {
    if (index < 0 || index >= arr.size) {
        cout << "index out of range";
    }
    arr.data[index] = value;
}
void set(IntArray* arr, int index, int value) {
    set(*arr, index, value);
}

void print(IntArray& arr) {
    int l = arr.size;
    cout << "[";
    for (int i = 0; i < l - 1; i++)
        cout << arr.data[i] << ", ";
    cout << arr.data[l - 1] << "]" <<endl;
}
void print(IntArray* arr) {
    print(*arr);
}

void resize(IntArray& arr, int newSize) {
    if (newSize == arr.size)
        return;

    int* new_a = new int[newSize];
    if (newSize > arr.size) {
        memcpy(new_a, arr.data, sizeof(int) * arr.size);

        int i = arr.size;
        for (i; i < newSize; ++i)
            new_a[i] = 0;
    }
    else memcpy(new_a, arr.data, sizeof(int) * newSize);

    delete[] arr.data;
    arr.data = new_a;
    arr.size = newSize;
}
void resize(IntArray* arr, int newSize) {
    resize(*arr, newSize);
}

void destroy(IntArray& arr) {
    if (!arr.data) {
        delete[] arr.data;
        arr.data = nullptr;
    }
    arr.size = 0;
}
void destroy(IntArray* arr) {
    destroy(*arr);
}

int main(int argc, char* argv[])
{
    int size = 30;
    IntArray arr;

    create(arr, size);
    for (int i = 0; i < size; ++i)
        set(arr, i, i + 1);
    print(arr);

    resize(arr, 50);
    print(arr);

    resize(arr, 10);
    print(arr);

    destroy(arr);
}
