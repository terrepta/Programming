#include <iostream>
#include "fact_n.h"
#include "sin_x.h"
#include "comb_n.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    cout << "n\tn!\n";
    for (int n = 1; n <= 10; n++) {
        cout << n << "\t" << fact_n(n) << "\n";
    }
}
