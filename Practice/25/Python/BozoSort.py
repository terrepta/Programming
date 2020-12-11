import random
import math

# функция сортировки для одномерного массива
def BozoSortA(array:list , b = True):
    check = True
    while check:
        num = int(len(array))
        check = False
        a1 = int(random.randint(0, (num-1))) # выбираем рандомные элементы массива
        a2 = int(random.randint(0, (num-1)))
        array[a1], array[a2] = array[a2], array[a1] # меняем элементы местами
        if b: # если b = true - сортировка по возрастанию
            for i in range (0, num - 1):
                if array[i] > array[i + 1]:
                    check = True
                    break
        else: # иначе - сортировка по убыванию
            for i in range(0, num - 1):
                if array[i] < array[i + 1]:
                    check = True
                    break
    return array

def BozoSortM(matrix:list,b = True):
    num = int(len(matrix))
    array = []
    for i in range(num):
         for j in range(num):
             array.append(matrix[i][j])
    return BozoSortA(array, b)

def BozoSortN(a1:int, a2:int, a3:int, b = True):
    return BozoSortA([a1,a2,a3], b)

def out(array:list,num):
    for i in range(0, num):
        print(array[i], ' ', end='')
    print()

num = int(input("Введите количество чисел, требующих сортировки: "))
array = list(map(int, input("Задайте числа для сортировки:\n").split()))
print()

n = int(math.sqrt(num))
matrix = []
temp_arr=[]
k=0
for i in range(num):
    temp_arr.append(array[i])
    k+=1
    if k % n == 0:
        matrix.append(temp_arr)
        temp_arr = []

a1 = array[0]
a2 = array[1]
a3 = array[2]

out((BozoSortA(array)), num);
out((BozoSortA(array, False)), num);
out((BozoSortM(matrix)), num);
out((BozoSortM(matrix, False)), num);
out((BozoSortN(a1, a2, a3)), 3);
out((BozoSortN(a1, a2, a3, False)), 3);