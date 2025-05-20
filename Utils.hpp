#pragma once
#include <iostream>
#include <sstream>
using namespace std;

string tolower(string input) {
	stringstream ss;

	for (auto x : input) {
		ss << (char)tolower(x);
	}

	return ss.str();
}