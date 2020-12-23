#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//функция сортировки для одномерного массива
template<class T>
vector<T> BozoSort(vector<T>array, int num, bool b = 1) {
    bool check = 1;
    while (check) {
        check = 0;
        int a1 = rand() % num;      //выбираем рандомные элементы массива
        int a2 = rand() % num;
        swap(array[a1], array[a2]); //меняем элементы местами
        if (b) {                   //если b = true - сортировка по возрастанию
            for (int i = 0; i < num - 1; i++) {
                if (array[i] > array[i + 1]) {
                    check = 1;
                    break;
                }
            }
        }
    }
    return array;
}

struct Student {
    string name;
    int group;
    int math, phys, hist, prog;
    map<string, int> exams = { 
        {"Math", math},
        {"Phys", phys}, 
        {"Hist", hist}, 
        {"Prog", prog}
    };
};

//перегрузка << для вывода информации об одном студенте
ostream& operator << (ostream& out, Student stud) {
    out << "+-----------+-------+------+------+------+------+\n"
        << "| Name      | Group | Math | Phys | Hist | Prog |\n"
        << "+-----------+-------+------+------+------+------+\n"
        << "| " << stud.name << " | " << stud.group <<" "
        << "    | " << stud.exams.at("Math")
        << "    | " << stud.exams.at("Phys")
        << "    | " << stud.exams.at("Hist")
        << "    | " << stud.exams.at("Prog")
        << "    |\n"
        << "+-----------+-------+------+------+------+------+\n";
    return out;
}

//перегрузка << для вывода информации о нескольких студентов
ostream& operator << (ostream& out, vector<Student> stud_v) {
    out << "+-----------+-------+------+------+------+------+\n"
        << "| Name      | Group | Math | Phys | Hist | Prog |\n"
        << "+-----------+-------+------+------+------+------+\n";
    for (const auto& stud : stud_v) {
        out << "| " << stud.name << " | " << stud.group << " "
            << "    | " << stud.exams.at("Math")
            << "    | " << stud.exams.at("Phys")
            << "    | " << stud.exams.at("Hist")
            << "    | " << stud.exams.at("Prog")
            << "    |\n"
            << "+-----------+-------+------+------+------+------+\n";
    }
    return out;
}

//перегрузка > для сортировки
bool operator > (Student& a, Student& b) {
    return a.name > b.name;
}

int main() {
//создание вектора из 10 структур типа Student
    vector<Student> AllStudents = {
        Student{"Shima   T",  5,  3, 2, 3, 5},
        Student{"Dragon  M",  2,  5, 5, 5, 3},
        Student{"Tepes   A",  5,  4, 2, 2, 5},
        Student{"Uzumaki N",  2,  3, 4, 3, 4},
        Student{"Psycho  M",  4,  5, 5, 5, 5},
        Student{"Uchiha  I",  2,  4, 4, 5, 2},
        Student{"Elric   E",  2,  5, 4, 5, 3},
        Student{"Izuku   M",  3,  4, 4, 4, 3},
        Student{"Zoldyck K",  1,  3, 4, 4, 5},
        Student{"Saitama S",  4,  4, 5, 3, 2},
    };

    /* проверка работы перегрузки << для одного студента
    Student only_one_student { "Uzumaki N", 2, 3, 4, 3, 4 };
    cout << only_one_student; */

//запись всех студентов, получивших оценку 2 в новый вектор
    vector<Student> WhoHavePair;
    for (int i = 0; i < 10; i++) {
        if (AllStudents[i].exams.at("Math") == 2 or 
            AllStudents[i].exams.at("Phys") == 2 or
            AllStudents[i].exams.at("Hist") == 2 or
            AllStudents[i].exams.at("Prog") == 2) {
            WhoHavePair.push_back(AllStudents[i]);
        }
    }

/*если вектор со студентами, получившими 2, не пуст,
    то сортируем его и выводим, иначе - выводим фразу "Not found"*/
    if (!WhoHavePair.empty()) {
        cout << BozoSort(WhoHavePair, WhoHavePair.size());
    }
    else {
        cout << "Not found\n";
        return 0;
    }

//вывод информации о рандомном студенте-двоичнике
    cout << endl << "Expulsion\n\n";
    int i = rand() % WhoHavePair.size();
    cout << WhoHavePair[i];
}
