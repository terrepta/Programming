def print_factorization(n):
    count = 0
    if n > 1:
        for i in range(2, n):
            while n % i == 0:
                count += 1
                n = n / i
            if count > 0:
                print(i, end='')
                if count > 1:
                    print("^", count, end="", sep="")
                if n > 1:
                    print("*", end="", sep="")
            count = 0
    elif n == 1:
        print("-")
n = int(input("Введите число для факторизации\n"))
print_factorization(n)
