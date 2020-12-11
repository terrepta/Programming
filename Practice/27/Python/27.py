n = int(input("Введите количество поступивших сигналов\n"))
in_array = list(map(int, input("Запишите данные числа\n").split()))
out_array = []
counter = 0
for i in range(n):
    counter += 1
    out_array.append(in_array[i])
    out_array.sort(reverse = True)
    if counter <= 5:
        for j in range(counter):
            print(out_array[j], end=" ")
    else:
        for j in range(counter - 5, counter):
            print(out_array[j], end=" ")
    print()
