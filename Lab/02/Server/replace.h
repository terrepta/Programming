#pragma once

#include <string>
using namespace std;

string replace(string& sentence, const string& a, const string& b, size_t pose = 0) {
	pose = sentence.find(a);
	while (pose != string::npos) {
		sentence.replace(pose, a.length(), b);
		pose += b.length();
	}
	return sentence;
}