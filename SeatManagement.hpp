#pragma once
#include <iostream>

using namespace std;

class Seat {
public:
	int streamerMaxSize = 5;
	string streamerSeats[5] = { "[]", "[]", "[]", "[]", "[]" };

	int vipMaxSize = 10;
	string vipSeats[2][5] = {
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" }
	};

	int normalMaxSize = 20;
	string normalSeats[7][5] = {
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" }
	};
};