//считывание csv файла
#pragma once
#include <string>
#include <vector>
using namespace std;

vector<vector<string>> read_file(istream& in) {
	vector<string> line;
	vector<vector<string>> vec;
	string str;
	string temp;

	while (getline(in, str, '\r')) {
		char num = 0;
		for (auto sign : str) {
			if (sign == '"') {
				switch (num) {
				case 0:
					num = 1;
					continue;
				case 1:
					num = 2;
					continue;
				case 2:
					temp.push_back('"');
					num = 1;
					continue;
				}
			}
			if (sign == ',') {
				switch (num) {
				case 0:
					line.push_back(temp);
					temp.clear();
					continue;
				case 2:
					line.push_back(temp);
					temp.clear();
					num = 0;
					continue;
				}
			}
			temp.push_back(sign);
		}
		line.push_back(temp);
		vec.push_back(line);

		temp.clear();
		line.clear();
	}
	return vec;
}