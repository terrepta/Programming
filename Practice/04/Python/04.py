c = 0                     #Ввод третьей переменной
print ("a= ", end="")
a = float(input())
print ("b= ", end="")
b = float(input())
c = a                     #Присвоение новой переменной значения а
a = b                     #Замена значения a на значение b
b = c                     #Замена значения b на значение a
print ("a= ", a ,"b= ", b) 


print ("a= ", end="")
a = float(input())
print ("b= ", end="")
b = float(input())
a = a + b                  #Нахождение сумммы чисел
b = a - b                  #Замена значения b на значение а
a = a - b                  #Замена значения a на значение b
print ("a= ", a ,"b= ", b) 