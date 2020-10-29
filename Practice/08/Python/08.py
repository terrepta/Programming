a, sign, b = input().split()
a = float(a) 
b = float(b)

if b == 0 and sign == "/":
    print("Ошибка. Деление на ноль невозможно. Введите новые значения.")
else:
    if sign =="+" :
        print(a + b)
    elif sign =="-" :
        print(a - b)
    elif sign =="*" :
        print(a * b)
    elif sign =="/" :
        print(a / b)
        