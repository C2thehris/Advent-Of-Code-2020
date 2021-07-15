#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::ifstream istr("input.txt");
	int x = 0;
	int y = 0;
	std::string current;
	int count = 0;
	long int product = 1;
	std::vector<std::string> lines;

	while (istr >> current) {
		lines.push_back(current);
	}

	int right = 1;
	int down = 1;

	for (; y < lines.size(); ) {
		if (x >= lines[0].size()) x %= lines[0].size();
		if (lines[y][x] == '#') ++count;
		x += right;
		y += down;
	} 

	product *= count;
	count = 0;
	x = 0;
	y = 0;
	right = 3;
	for (; y < lines.size(); ) {
		if (x >= lines[0].size()) x %= lines[0].size();
		if (lines[y][x] == '#') ++count;
		x += right;
		y += down;
	} 
	product *= count;
	count = 0;
	x = 0;
	y = 0;
	right = 5;

	for (; y < lines.size(); ) {
		if (x >= lines[0].size()) x %= lines[0].size();
		if (lines[y][x] == '#') ++count;
		x += right;
		y += down;
	} 
	product *= count;
	count = 0;
	x = 0;
	y = 0;
	right = 7;

	for (; y < lines.size(); ) {
		if (x >= lines[0].size()) x %= lines[0].size();
		if (lines[y][x] == '#') ++count;
		x += right;
		y += down;
	} 
	product *= count;
	count = 0;
	x = 0;
	y = 0;
	right = 1;
	down = 2;

	for (; y < lines.size(); ) {
		if (x >= lines[0].size()) x %= lines[0].size();
		if (lines[y][x] == '#') ++count;
		x += right;
		y += down;
	} 

	product *= count;



	std::cout << product << std::endl;
}