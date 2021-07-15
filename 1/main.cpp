#include <fstream>
#include <iostream>

int main() {
  std::ifstream istr("input.txt");
  int a[200];
  for (int i = 0; i < 200; ++i) {
  	std::string temp = "";
  	istr >> temp;
  	a[i] = std::stoi(temp);
  }
  int first;
  int second;
  int third;
  bool found = false;
  for (int i = 0; i < 198; ++i) {
  	for (int j = i+1; j < 199; ++j) {
  		for (int k = j+1; k < 200; ++k) {
  			if (a[i] + a[j] + a[k] == 2020) {
  			first = a[i];
  			second = a[j];
  			third = a[k];
  			found = true;
  			}
  			if (found)
  				break;
  		}
  		if (found)
  			break;
  	}
  	if (found)
  		break;
  }
  int product = first * second * third;
  std::cout << product << std::endl;
}