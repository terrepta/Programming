
def bmi(weight:float, height:float):
    height = height / 100
    bmi = weight / (height * height)
    return bmi

def print_bmi(bmi:float):
    if (bmi < 18.5): print("Underweight")
    elif (bmi >= 18.5 and bmi < 25.0): print("Normal weight")
    elif (bmi >= 25.0 and bmi < 30.0): print("Overweight")
    elif (30.0 <= bmi): print("Obesity")

weight,height = map(float, input("Put your weight and height\n").split())
print_bmi(bmi(weight, height))


