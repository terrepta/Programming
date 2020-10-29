ident=1
while ident == 1:
    i = 0
    import random
    numb = random.randint(0,100)
    print("\tПриветствую!\n Сейчас компьютер загадает число. У вас будет 5 попыток, чтобы его отгадать.\n Введите целое число.\n")
    while i < 5:
        answ = int(input())
        if answ < numb : 
            print("Загаданное число больше")
        elif answ > numb: 
            print("Загаданное число меньше")
        else:
            print("Поздравляю! Вы угадали!\n\nХотите начать сначала? (1-ДА)")
            ident = int(input())
            break
        i += 1
        if i == 5: 
            print("Вы проиграли. Было загадано:", numb, "\n\nХотите начать сначала? (1-ДА)")
            ident = int(input())
            break