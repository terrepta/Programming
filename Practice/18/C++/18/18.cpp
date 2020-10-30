#include <iostream>
#include <string>
using namespace std;

/*void changewords(string newwords) {

}*/

int lenght(string words) {
    int counter = 0;
    while (words[counter] != '\0') counter++;
        return counter;
}

int main()
{
    setlocale(LC_ALL, "russian");
   /* int ident;
    cout << "Вы знаете слова hallo, klempner, das, ist, fantastisch, fluggegecheimen.\n Хотите заменить эти слова на новые? (1-Да)\n";
    cin >> ident;
    if (ident==1)  */

    const int n = 6;
    string words[n] = { "hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen" };
  

}

