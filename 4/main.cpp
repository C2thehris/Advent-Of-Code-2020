#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void reset(std::vector<bool> &fields) {
	for (int i = 0; i < fields.size(); ++i) {
		fields[i] = false;
	}
}

bool found(std::vector<bool> &fields) {
	for (int i = 0; i < fields.size(); ++i) {
		if (!(fields[i])) {
			return false;
		}
	}
	return true;
}

bool checkcolor(std::string &color, std::vector<std::string> &colors) {
	for (int i = 0; i < colors.size(); ++i) {
		if (colors[i] == color)
			return true;
	}
	return false;
}

bool checkPID(std::string &pid) {
	if (pid.size() != 9)
		return false;
	for (int i = 0; i < pid.size(); ++i) {
		if (!isdigit(pid[i]))
			return false;
	}
	return true;
}

bool checkHair(std::string &hair) {
	for (int i = 1; i < hair.size(); ++i) {
		if (!isdigit(hair[i]) && (hair[i] < 'a' && hair[i] > 'f'))
			return false;
	}
	return true;
}

bool checkHeight(std::string &height) {
	std::string num = "";
	std::string units = "";
	bool letter = false;
	for (int i = 0; i < height.size(); ++i) {
		if (isdigit(height[i]) && !letter) {
			num += height[i];
		} else if (isalpha(height[i]) && !letter)
			letter = true;
		else if (!letter)
			return false;
		if (isalpha(height[i]) && letter)
			units += height[i];
		else if (letter)
			return false;
	}
	int hgt = std::stoi(num);
	if (units == "cm" && hgt >= 150 && hgt <= 193) {
		return true;
	} else if (units == "in" && hgt >= 59 && hgt <= 76)
		return true;
	return false;
}

int main() {
	std::ifstream istr("input.txt");
	std::string input = "";
	int answer = 0;

	std::vector<std::string> colors;

	colors.push_back("amb");
	colors.push_back("blu");
	colors.push_back("brn");
	colors.push_back("gry");
	colors.push_back("grn");
	colors.push_back("hzl");
	colors.push_back("oth");

	std::vector<bool> rfields;

	for (int i = 0; i < 7; ++i) {
		rfields.push_back(false);
	}

	while (std::getline(istr, input)) {
		if (input.find('\r',0) == 0)  {
			if (found(rfields))
				++answer;
			reset(rfields);
		}
		
		if (input.find("ecl",0) != -1) {
			int begin = input.find("ecl", 0);
			std::string color = input.substr(begin + 4, 3);
			if (color[color.size()-1] == '\r')
				color.pop_back();
			else if (checkcolor(color, colors))
				rfields[0] = true;
		}
		if (input.find("pid",0) != -1) {
			int begin = input.find("pid", 0);
			int end = input.find(' ', begin);
			if (end == -1)
				end = input.size() - 1;
			std::string pid = input.substr(begin+4, end-begin-4);

			if (pid[pid.size()-1] == '\r')
				pid.pop_back();
			if (checkPID(pid))
				rfields[1] = true;
		}
		if (input.find("eyr",0) != -1) {
			std::string eyr = input.substr(input.find("eyr",0)+4, 4);
			int ey = std::stoi(eyr);
			if (ey >= 2020 && ey <= 2030)
				rfields[2] = true;
		}
		if (input.find("hcl",0) != -1) {
			int begin = input.find("hcl")+4;
			int end = input.find(' ', begin);
			if (end == -1)
				end = input.size() - 1;
			std::string hcl = input.substr(begin, end-begin-4);

			if (hcl[hcl.size()-1] == '\r')
				hcl.pop_back();			
			if (hcl[0] == '#' && checkHair(hcl))
				rfields[3] = true;
		} 
		if (input.find("byr",0) != -1) {
			int begin = input.find("byr") + 4;
			std::string year = input.substr(begin, 4);
			int yr = std::stoi(year);

			if (yr >= 1920 && yr <= 2002)
				rfields[4] = true;
		}
		if (input.find("iyr",0) != -1) {
			int begin = input.find("iyr") + 4;
			std::string year = input.substr(begin, 4);
			int yr = std::stoi(year);

			if (yr >= 2010 && yr <= 2020)
				rfields[5] = true;			
		} 
		if (input.find("hgt",0) != -1) {
			int begin = input.find("hgt")+4;
			std::string hgt = input.substr(begin, 5);

			if (hgt[hgt.size()-1] == '\r' || hgt[hgt.size()-1] == ' ')
				hgt.pop_back();

			if (checkHeight(hgt)) {


				rfields[6] = true;
			}
		}
	}

	if (found(rfields)) {
		++answer;
	}

	std::cout << answer << std::endl;
}