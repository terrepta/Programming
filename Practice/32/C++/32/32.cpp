#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "replacer.h"
#include "csv_parser.h"
using namespace std;

struct Passenger {
	bool survival;
	int pclass;
	string name;
	string sex;
	int age;
	int sibsp;
	int parch;
	string ticket;
	double fare;
	string cabin;
	string embarked;
};

//перегрузка операторов с помощью передачи значений по ссылке
istream& operator >> (istream& in, vector<Passenger>& all_pass)  {
	auto data = read_file(in);
	data.erase(data.begin());
	for (auto element : data) {
		Passenger passanger;
		passanger.survival = stoi(element[1]);
		passanger.pclass = stoi(element[2]);
		passanger.name = element[3];
		passanger.sex = element[4];
		passanger.age = element[5] == "" ? 0 : stoi(element[5]);
		passanger.sibsp = stoi(element[6]);
		passanger.parch = stoi(element[7]);
		passanger.ticket = element[8];
		passanger.fare = stoi(element[9]);
		passanger.cabin = element[10];
		passanger.embarked = element[11][0];

		all_pass.push_back(passanger);
	}
	return in;
}

ostream& operator << (ostream& out, vector <Passenger>& all_pass) {
	//для красивой таблицы:
	vector<string> titles = { "Survived", "Pclass", "Name", "Sex", "Age", "SibSp", "Parch", "Ticket", "Fare", "Cabin", "Embarked"};
	out << titles[0];
	for (int i = 1; i < titles.size(); i++) {
		out << ',' << titles[i];
	}
	out << '\r';

	for (auto& pass : all_pass) {
		string name = pass.name;
		string ch1 = "\"";
		string ch2 = "\"\"";
		name = replacer(name, ch1, ch2);

		out << bool(pass.survival) << ','
			<< int(pass.pclass) << ',' 
			<< '"' << name << '"' << ','
			<< pass.sex << ','
			<< int(pass.age) << ','
			<< int(pass.sibsp) << ','
			<< int(pass.parch) << ','
			<< pass.ticket << ','
			<< double(pass.fare) << ','
			<< pass.cabin << ','
			<< pass.embarked
			<< '\r' << flush;
	}
	return out;
}

int main() {
	vector<Passenger> all_pass;
	vector<Passenger> sought_w;
	ifstream input("train.csv"); 
	input >> all_pass;				//считывание

	ofstream output("out.csv");
	for (auto& pass : all_pass) {
		if (pass.pclass == 1 and pass.survival == true and pass.sex == "female") {
			sought_w.push_back(pass);
		}
	}
	sort(sought_w.begin(), sought_w.end(), [&](Passenger a, Passenger b) {return a.age < b.age; }); //сортировка
	output << sought_w;		//сохранение в файл
	
	input.close();
	output.close();

	return 0;
}