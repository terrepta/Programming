i = 1 
ex = 0
all_tickets = ''
numb = int(input("Введите количество билетов\n"))

print( "Через пробел ведите номера данных ", numb, " билетов")
ticket=input().split()
for i in range(len(ticket)):
    if (ticket[i][0] == 'a' and ticket[i][4] == '5' and ticket[i][5] == '5' and ticket[i][6] == '6' and ticket[i][7] == '6' and ticket[i][8] == '1'):
        one = [ticket[i]]
        all_tickets += one[0] + ' '
    else: ex += 1
if ex == numb: print( "-1")
else: print(all_tickets)
