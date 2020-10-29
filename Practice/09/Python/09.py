print("Введите два значения времени\n")
h1, m1 = map(int, input().split(':'))
h2, m2 = map(int, input().split(':'))

if h1 < 0 or h1 > 23:
    print("Введены некореректные данные.")
if h2 < 0 or h1=2 > 23:
    print("Введены некореректные данные.")
if m1 < 0 or m1 > 23:
    print("Введены некореректные данные.")
if m2 < 0 or m2 > 23:
    print("Введены некореректные данные.")
    
if m2 < m1 and h2 != h1 + 1:
    m2 += 60 + ((h2 - h1 - 1) * 60)

elif m2 < m1 or h2 != h1:
    if m2 < m1:
        m2 += 60
    elif h2 != h1:
        m2 += (h2 - h1) * 60

difference = m2 - m1

if difference <= 15:
    print( "Встреча состоится")
else:
    print( "Встреча не состоится")
