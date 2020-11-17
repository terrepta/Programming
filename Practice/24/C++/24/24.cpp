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
	json temporary_storage;		//временное хранилище данных
	ifstream read("in.json");			//чтение файла in.json
	read >> in_file;
	int sum_of_users = 0;		

	for (int i = 0; i < in_file.size(); i++) {		//подсчет количества юзеров
		if (in_file[i]["userId"] >= sum_of_users)
			sum_of_users = in_file[i]["userId"];
	}
	int* number_of_completed_tasks = new int [sum_of_users] { 0 };		//создание динамического массива c кол-вом элементов равном кол-ву юзеров
	for (int i = 0; i < in_file.size(); i++) {							//условие, проверяющее каждый элемент in.json
		for (int u = 1; u <= sum_of_users; u++)							//условие, проверяющее кадого юзера по очереди
		{
			if (in_file[i]["completed"] == true && in_file[i]["userId"] == u)
				number_of_completed_tasks[u-1]++;						//подсчет количества выполненных заданий для каждого юзера
		}
	}
	for (int i = 1; i <= sum_of_users; i++) {							//заносим все данные во временное хранилище данных temporary_storage
		temporary_storage[i]["task_completed"] = number_of_completed_tasks[i-1];
		temporary_storage[i]["userId"] = i;
	}
	out_file.push_back(temporary_storage);			//добавление элементов в массив 
	ofstream add("out.json");		
	add << setw(2) << out_file;		//запись данных из out_file в файл out.json
	}
