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