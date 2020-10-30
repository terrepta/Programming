#include <iostream>
using namespace std;

double bmi(double weight, double height) {
    double BMI;
    height = height / 100;
    BMI = weight / (height * height);
    return BMI;
}

void printBMI(double BMI){
    double bmi(double weight, double height);
    if (BMI < 18.5) cout << "Underweight";
    else if (BMI >= 18.5 && BMI < 25.0) cout << "Normal weight";
    else if (BMI >= 25.0 && BMI < 30.0) cout << "Overweight";
    else if (30.0 <= BMI) cout << "Obesity";
}
int main()
{
    double weight, height;
    cout << "Put your weight and height\n";
    cin >> weight >> height;
    printBMI(bmi(weight, height));

    return 0;
}
