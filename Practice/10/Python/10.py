
s, l1, r1, l2, r2 = map(int, input("Введите значения s, l1, r1, l2, r2\n").split())
lr2 = r2 - l2

x1 = l1          #т. к. х1 должен быть наименьшим возможным из своего промежутка
x2 = s - x1

if x2 < l2:
    dist = l2 - x2
    if dist < lr2 :
        x2 += dist
        x1 -= dist
        print(x1,x2)
    else:
        print("-1")
elif x2 > r2:
    dist = x2 - r2
    if dist < lr2:
        x2 -= dist
        x1 += dist
        print(x1,x2)
    else:
        print("-1")
else:print(x1,x2)
