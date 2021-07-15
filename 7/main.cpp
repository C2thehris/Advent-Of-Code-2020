#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

bool check(std::vector<std::string> &valids, std::string &bag) {
	for (uint i = 0; i < valids.size(); ++i) {
		if (valids[i] == bag) return true; 
	}
	return false;
}

int main() {
	std::ifstream istr("input.txt");

	std::vector<std::string> valid;
	std::vector<uint> nums;
	valid.push_back("shiny gold");
	nums.push_back(0);

	std::string input = "";

	for (int i = 0; i < signed(valid.size()); ++i) {
		uint total = 0;
		while (getline(istr, input)) {
			std::string current = "";
			uint first = input.find(' ', 0);
			uint second = input.find(' ', first+1);
			current += input.substr(0, second);

			if (current != valid[i]) {
				continue;
			}

			uint c = second+14;
			std::string sbag = "";
			for (uint j = c; j < input.size(); j += second-j+7, sbag = "") {
				if (input[j] == ' ')
					j -= 1;
				std::string n = input.substr(j, 1);
				if (isalpha(n[0]))
					break;
				int in = std::stoi(n);
				total += in;
				j += 2;
				
				first = input.find(' ', j);
				second = input.find(' ', first+1);
				sbag += input.substr(j, second-j);

				if (sbag[sbag.size()-1] == '\r') {
					sbag.pop_back();
					sbag.pop_back();
				}

				uint pos = std::find(valid.begin(), valid.end(), sbag) - valid.begin();
				if (pos == valid.size()) {
					valid.push_back(sbag);
					nums.push_back(0);
				} else {
					total += in*nums[pos];
				}
			}
			break;
		}
		if (total != nums[i]) {
			nums[i] = total;
			i = -1;
		}
		istr.clear();
		istr.seekg(0);
	}

	//while (getline(istr, input)) {
		//std::string current = "";
		/*
		int first = input.find(' ', 0);
		int second = input.find(' ', first+1);
		current += input.substr(0, second);
	
		if (check(valid, current)) {
			continue;
		}


		int c = second+16;
		std::string sbag = "";
		for (int i = c; i < input.size(); i +=(second-i)+9) {
			first = input.find(' ', i);
			second = input.find(' ', first+1);
			sbag += input.substr(i, second-i);
			if (sbag[sbag.size()-1] == '\r') {
				sbag.pop_back();
				sbag.pop_back();
			}

			if (check(valid, sbag)) {
				istr.clear();
				istr.seekg(0);
				valid.push_back(current);
				++answer;
				break;
			}
			sbag = "";
			if (input.find("bag,", i) < second + 9)
				second -= 1;
		}
		*/
	//}

	std::cout << nums[0] << std::endl;
}