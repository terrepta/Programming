def create(l, initial = 0, step = 0):
    array = [0]*l
    array[0] = initial
    for i in range(1, l):
        array[i] = array[i - 1] + step
    return array

def sort(array, l):
    for i in range (l):
        for j in range(i, 0, -1):
            if array[j] < array[j - 1]:
                array[j], array[j - 1] = array[j - 1], array[j]
    return array

def to_print(array, l):
    print('[', sep='', end='')
    for i in range(l - 1):
        print(array[i], ', ', sep='', end='')
    print(array[l-1] , ']', sep='', end='')
    return array
     

l = int(input())
initial = int(input())
step = int(input())
array = create(l, initial, step)
sort(array, l)
to_print(array, l)
