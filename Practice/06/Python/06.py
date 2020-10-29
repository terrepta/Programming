from math import sqrt
print ("Введите значения a, b и с")    
a = float(input())
b = float(input())
c = float(input())
if a == 0:
    print("x= ", -c / b)
else:
    if (pow(b, 2) - 4 * a * c > 0):
        print ("x1=", (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a))
        print ("x2=", (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a))
    elif (pow(b, 2) - 4 * a * c == 0):
        print ("x= ", (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a))
    else: print("Уравнение не имеет вещественных корней");