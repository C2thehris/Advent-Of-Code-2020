//NOTE: The solution for part 2 of this has a ton of things in the image class that don't make sense being in a class
//TODO (after other challenges completed):
//Combine Image and Tile, implement accessors so neccesary functions in image can be brought out
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "image.h"

#define infile "input.txt"

void computeLines(Tile &t)
{
	std::string front, back, top, bottom;
	top = t.grid[0];

	bottom = t.grid[t.grid.size() - 1];
	std::vector<std::string> grid;
	for (unsigned int i = 1; i < t.grid.size() - 1; ++i)
	{
		grid.push_back(t.grid[i]);
	}
	t.grid = grid;

	front.push_back(top[0]);
	back.push_back(top[top.size() - 1]);
	for (std::string &str : t.grid)
	{
		front.push_back(str[0]);
		back.push_back(str[str.length() - 1]);
		str = str.substr(1, str.length() - 2);
	}
	front.push_back(bottom[0]);
	back.push_back(bottom[bottom.size() - 1]);

	t.lines.push_back(front);
	t.lines.push_back(top);
	t.lines.push_back(back);
	t.lines.push_back(bottom);
}

Tile *findNeighbors(const std::string &str, std::vector<Tile> &tiles, int current)
{
	for (Tile &t : tiles)
	{
		if (t.id == current)
			continue;
		for (std::string line : t.lines)
		{
			if (str == line)
				return &t;
			std::reverse(line.begin(), line.end());
			if (str == line)
				return &t;
		}
	}
	return nullptr;
}

int parseNum(const std::string &tile)
{
	std::string num;
	for (unsigned int i = 0; i < tile.length(); ++i)
	{
		if (isdigit(tile[i]))
		{
			num += tile[i];
		}
	}
	return std::stoi(num);
}

int main()
{
	std::ifstream istr(infile);
	std::string input;
	int current;
	std::vector<std::string> grid;
	std::vector<Tile> tiles;

	while (getline(istr, input))
	{
		if (input[0] == 'T')
		{
			current = parseNum(input);
		}
		else if (input[0] == '.' || input[0] == '#')
		{
			if (input[input.length() - 1] == '\r')
			{
				input = input.substr(0, input.length() - 1);
			}
			grid.push_back(input);
		}
		else
		{
			Tile t;
			t.grid = grid;
			t.id = current;
			grid.clear();
			tiles.push_back(t);
		}
	}

	for (Tile &t : tiles)
	{
		computeLines(t);
	}

	//long long answer = 1; PART 1
	Tile *neighbor;
	Tile corner;
	for (Tile &t : tiles)
	{
		current = t.id;
		for (unsigned int i = 0; i < 4; ++i)
		{
			if (t.borders[i] == nullptr)
			{
				neighbor = findNeighbors(t.lines[i], tiles, current);
				if (neighbor != nullptr)
				{
					++t.count;
				}
				t.borders[i] = neighbor;
			}
			else
			{
				++t.count;
			}
		}
		if (t.count == 2)
		{
			std::cout << "Corner Tile Found! ID: " << t.id << "\n";
			corner = t;
			//answer *= t.id; PART 1
		}
		else if (t.count < 2)
		{
			std::cerr << "Error: Tile has fewer than 2 neighbors, ID: " << t.id << "\n";
			exit(1);
		}
	}
	Image img(corner);
	int answer = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (answer != 0)
		{
			answer = std::min(answer, img.countP());
		}
		else
		{
			answer = img.countP();
		}
		img.rotateCW();
	}
	img.mirrorX();
	for (int i = 0; i < 4; ++i)
	{
		answer = std::min(answer, img.countP());
		img.rotateCW();
	}
	img.mirrorY();
	for (int i = 0; i < 4; ++i)
	{
		answer = std::min(answer, img.countP());
		img.rotateCW();
	}
	img.mirrorX();
	for (int i = 0; i < 4; ++i)
	{
		answer = std::min(answer, img.countP());
		img.rotateCW();
	}
	std::cout << "The answer is: " << answer << std::endl;
}
