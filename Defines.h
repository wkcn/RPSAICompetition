#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

enum state { rock = 0, paper = 1, scissors = 2, blank = 3 };
struct player
{
	virtual ~player() { }
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history) = 0;
};

#endif