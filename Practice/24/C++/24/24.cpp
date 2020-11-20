#include <iostream>
#include "json.hpp"
#include <fstream>	//ifstream, ofstream
#include <string>
#include <iomanip>	//setw
using namespace std;
using json = nlohmann::json;

int main()
{
	json in_file;	//данные из файла in.json
	json out_file = json::array();		//данные, которые будут записаны в out.json
	json temp_s;		//временное хранилище данных
	ifstream read("in.json");			//чтение файла in.json
	read >> in_file;
	int all_u = 0;		

	for (int i = 0; i < in_file.size(); i++) {		//подсчет количества юзеров
		if (in_file[i]["userId"] >= all_u)
			all_u = in_file[i]["userId"];
	}
	int* n_task_comp = new int [all_u] { 0 };		//создание динамического массива c кол-вом элементов равном кол-ву юзеров
	for (int i = 0; i < in_file.size(); i++) {							//условие, проверяющее каждый элемент in.json
		for (int u = 1; u <= all_u; u++)							//условие, проверяющее кадого юзера по очереди
		{
			if (in_file[i]["completed"] && in_file[i]["userId"] == u)
				n_task_comp[u-1]++;						//подсчет количества выполненных заданий для каждого юзера
		}
	}
	for (int i = 1; i <= all_u; i++) {							//заносим все данные во временное хранилище данных temp_s
		temp_s[i]["task_completed"] = n_task_comp[i-1];
		temp_s[i]["userId"] = i;
	}
	out_file.push_back(temp_s);			//добавление элементов в массив 
	ofstream add("out.json");		
	add << setw(2) << out_file;		//запись данных из out_file в файл out.json
	delete[] n_task_comp;
	}
