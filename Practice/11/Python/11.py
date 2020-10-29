i=0
result = 1.0

numb = float(input("Ведите число, возводимое в степень\n"))
step = int(input("Введите степень числа\n"))
if step >= 0:
    while i < step:
        result *= numb
        i += 1
        
elif step < 0:
    while step < i:
        result = result * (1 / numb)
        i -= 1

print("Результат вычислений:",result)