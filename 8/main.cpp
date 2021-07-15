#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

bool check(const std::vector<std::streampos>& visted, const std::streampos& streampos) {
	for (uint i = 0; i < visted.size(); ++i) {
		if (visted[i] == streampos)
			return true;
	}
	return false;
}

bool changeJMP(const std::vector<std::streampos>& begs, std::ifstream& istr, uint index) {
	int temp = index;
	std::string input;
	std::vector<std::streampos> visted;
	istr >> input;
	++index;

	for (; index < begs.size(); ++index) {
		if (check(visted, istr.tellg()))
			break;
		visted.push_back(istr.tellg());		
		istr >> input;
		if (input == "jmp") {
			istr >> input;
			int val = std::stoi(input.substr(1, input.size()-1));
			if (input[0] == '+')
				index += val;
			else
				index -= val;
			istr.clear();
			istr.seekg(begs[index-1]);
			index -= 1;
		} else if (input == "acc") {
			istr >> input;
		} else {
			istr >> input;
		}
	}
	if (index >= begs.size()-1) {
		std::cout << temp << std::endl;
		return true;
	}
	return false;
}

bool changeNOP(const std::vector<std::streampos>& begs, std::ifstream& istr, uint index) {
	std::vector<std::streampos> visted;
	int temp = index;
	std::string input;
	visted.push_back(istr.tellg());
	istr >> input;
	int val = std::stoi(input.substr(1, input.size()-1));
	if (input[0] == '+')
		index += val;
	else
		index -= val;
	istr.clear();
	istr.seekg(begs[index-1]);

	for (; index < begs.size(); ++index) {
		if (check(visted, istr.tellg()))
			break;
		visted.push_back(istr.tellg());
		istr >> input;	
		if (input == "jmp") {
			istr >> input;
			int val = std::stoi(input.substr(1, input.size()-1));
			if (input[0] == '+')
				index += val;
			else
				index -= val;
			istr.clear();
			istr.seekg(begs[index-1]);
			index -= 1;
		} else if (input == "acc") {
			istr >> input;
		} else {
			istr >> input;
		}
	}
	if (index >= begs.size()-1) {
		std::cout << temp << std::endl;
		return true;
	}
	return false;
}


int main() {
	long int ans = 0;
	std::ifstream istr("input.txt");

	std::string input;

	std::vector<std::streampos> begs;
	begs.push_back(istr.tellg());

	while(getline(istr, input)) {
		begs.push_back(istr.tellg());
	}

	istr.clear();
	istr.seekg(0);

	uint index = 1;
	std::vector<std::streampos> visted;
	std::vector<uint> ivisted;

	for (; index <= begs.size(); ++index) {
		/*if (check(visted, istr.tellg()))
			break;*/
		visted.push_back(istr.tellg());
		ivisted.push_back(index);
		std::sort(ivisted.begin(), ivisted.end());
		istr >> input;
		if (input == "jmp") {
			/*std::streampos pos = istr.tellg();
			if (changeJMP(begs, istr, index))
				break;
			istr.clear();
			istr.seekg(pos);*/
			istr >> input;
			int val = std::stoi(input.substr(1, input.size()-1));
			if (input[0] == '+')
				index += val;
			else
				index -= val;
			istr.clear();
			istr.seekg(begs[index-1]);
			index -= 1;
		} else if (input == "acc") {
			istr >> input;
			int val = std::stoi(input.substr(1, input.size()-1));
			if (input[0] == '+')
				ans += val;
			else
				ans -= val;
		} else {
			/*std::streampos pos = istr.tellg();
			if (changeNOP(begs, istr, index))
				break;
			istr.clear();
			istr.seekg(pos);*/
			istr >> input;
		}
	}
	std::cout << ans << std::endl;
}