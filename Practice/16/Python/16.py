n = int(input("Введите количество билетов\n"))
t = []

for i in range(n):
    t.append(input("Введите номера данных билетов").split())

all_tickets = []
is_existed = 0

for i in range(n):
    if t[i][0] == 'a' and t[i][4] == '5' and arr[i][5] == '5' and arr[i][6] == '6' and arr[i][7] == '6' and arr[i][8] == '1':
        all_tickets.append(t[i])
        is_existed = 1

if is_existed:
    for i in range(len(all_tickets)):
        print(all_tickets[i])
else:
    print("-1\n")