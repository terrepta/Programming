from math import sqrt
num = int(input())

if num == 1:
    a = float(input())
    b = float(input())
    c = float(input())
    p = (a + b + c) / 2
    if a > 0 and b > 0 and c > 0 :
        print( "S = ", sqrt(p * (p - a) * (p - b) * (p - c)))
    else:
        print(" Введены некорректные данные.\n Длины сторон треугольника не могут быть отрицательными или равняться нулю.\n Введите новые данные.")
       

elif num == 2:
    ax,ay = map(float, input().split())
    bx,by = map(float, input().split())
    cx,cy = map(float, input().split())
    if (ax==bx and ay==by)or(ax==cx and ay==cy)or(bx==cx and by==cy) :
        print(" Введены некорректные данные.\n Длины сторон треугольника не могут быть отрицательными или равняться нулю.\n Введите новые данные.")
    else :
        ab = sqrt(pow((bx - ax), 2) + pow((by - ay), 2))
        ac = sqrt(pow((cx - ax), 2) + pow((cy - ay), 2))
        bc = sqrt(pow((cx - bx), 2) + pow((cy - by), 2))
        p = (ab + ac + bc) / 2
        print( "S = ", sqrt(p * (p - ab) * (p - ac) * (p - bc)))