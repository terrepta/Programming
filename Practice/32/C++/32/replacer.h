//замена одного элемента строки на другой
#pragma once
#include <string>
using namespace std;

string replacer(string result, const string& from, const string& to) {
	size_t pos = 0;
	while ((pos = result.find(from, pos)) != string::npos) {
		result.replace(pos, from.length(), to);
		pos += to.length();
	}
	return result;
}