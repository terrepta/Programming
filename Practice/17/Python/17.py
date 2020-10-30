all=37
n=[]*i
red = 0
black = 0
a = 0				            #в массиве всего 37 элементов, т.к. на поле числа от 0 до 36 
r = [ 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 ]
b = [2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35 ]

for i in range (all): 
    n[i] = 0					#всем числам присваивается нулевое значение
    
    while (1):
        numb=int(input("Введите число\n"))
        if numb < 0 or numb > 36: break
        else:
            n[numb]+=1
            for color in range (18):
                    if (numb == r[color]):
                    red = red + 1					#подсчёт красных и черных фишек
                else if (numb == b[color]):
                    black = black + 1
        for s in range(all):
            if (n[s] > a):
                a = n[s]			         #a принимает введенное значение
        for s in range(all):				 #вывод чисел, поаторяющихся чаще всего
			if (n[s] == a):   
            print(s, end='')
        for s in range(all):
            if (n[s] == 0):
                print(s, end='')			  #вывод чисел, не выпавших за последние игры
        print(red,black)
	