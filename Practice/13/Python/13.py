from math import sqrt
i = 2
n = int(input("Введите число для проверки\n"))

if (n <= 0) or (n == 1):
    print("Не является ни простым, ни составным.")
else:
	while sqrt(n) >= i:            
		if sqrt(n) >= i and ((n % i == 0) or (n % 5 == 0)):
			print("Составное"); exit(0)
		elif (sqrt(n) > i) and (n % i != 0):
			print("Простое"); exit(0)
		i += 1;