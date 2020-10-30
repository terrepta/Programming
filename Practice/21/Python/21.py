
def bmi(weight:float, height:float):
    height = height / 100
    BMI = weight / (height * height)
    return BMI

def print_bmi(bmi:float):
    bmi(weight, height)
    if (BMI < 18.5): print("Underweight")
    elif (BMI >= 18.5 and BMI < 25.0): print("Normal weight")
    elif (BMI >= 25.0 and BMI < 30.0): print("Overweight")
    elif (30.0 <= BMI): print("Obesity")

weight,height = map(float, input("Put your weight and height\n").split())
print_bmi(bmi(weight, height))


