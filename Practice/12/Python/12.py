def factorial(numb):
	if numb == 0:
		return 0
	elif numb == 1:
		return 1
	else:
		return numb * factorial(numb - 1)
        
numb = int(input("Введите число, факториал которого предстоит найти\n"))
print("Результат: ", factorial(numb))
