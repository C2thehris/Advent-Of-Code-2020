#include <fstream>
#include <iostream>

int main() {
  std::ifstream istr("input.txt");
  std::string current = "";
  char c = ' ';
  int min = 0;
  int max = 0;
  int valid = 0;
  while (istr >> current) {
  	std::string mistr = "";
  	std::string mastr = "";
  	bool dash = false;
  	for (uint i = 0; i < current.size(); ++i) {
  		if (isdigit(current[i]) && !dash) mistr += current[i];
  		else if (isdigit(current[i])) mastr += current[i];
  		else dash = true;  
  	}

  	min = std::stoi(mistr);
  	max = std::stoi(mastr);
  	istr >> current;
  	c = current[0];
  	istr >> current;
  	bool first = false;
  	bool second = false;
  	if (current[min-1] == c) first = true;
  	if (current[max-1] == c) second = true;
  	if (first ^ second) ++valid;
  }
  std::cout << valid << std::endl;
}