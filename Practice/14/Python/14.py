def recf(n):
    counter = 1
    factor = 2
   
    while factor<=n:
        factor *= 2
        counter +=1
    return counter;
   

n = int(input("Введите число\n"))
if n==0: print("Количество степеней двойки: 0")
elif n<0: print ("Неверные данные.")
else: print( "Количество степеней двойки: ", recf(n))