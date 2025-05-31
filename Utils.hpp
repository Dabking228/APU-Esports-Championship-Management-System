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

bool isPowerOfTwo(int n) {
	return n > 0 && (n & (n - 1)) == 0;
}

string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos) return ""; // all spaces
	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first, last - first + 1);
}