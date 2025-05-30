#pragma once
#define UTILS
#define NOMINMAX
#include <iostream>
#include <sstream>
#include <windows.h>
#include <psapi.h>
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

inline SIZE_T getCurrentMemoryUsage() {
	PROCESS_MEMORY_COUNTERS_EX pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
		return pmc.PrivateUsage; // Or pmc.PrivateUsage for more accuracy // returns in bytes
	}
	return 0;
}