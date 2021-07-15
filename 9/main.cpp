#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

bool check(const std::vector<long int>& nums, long int n) {
	for (uint i = 0; i < nums.size()-1; ++i) {
		for (uint j = i+1; j < nums.size(); ++j) {
			if (nums[i] + nums[j] == n)
				return true;
		}
	}
	return false;
}

/* PART1
int main() {
	std::vector<long int> nums;
	std::ifstream istr("input.txt");

	std::string input;
	
	int i = 0;
	for (; i < 25; ++i) {
		istr >> input;
		nums.push_back(std::stol(input));
	}

	i = 0;

	while (istr >> input) {
		if (i >= 25)
			i = 0;

		long int n = std::stol(input);

		if (check(nums, n))
			nums[i] = n;
		else {
			std::cout << n << std::endl;
			break;
		}
		++i;
	}
}
*/

//PART 2
int main() {
	std::vector<unsigned long long int> nums;
	std::ifstream istr("input.txt");

	std::string input;

	while (istr >> input) {
		unsigned long long int n = std::stol(input);

		nums.push_back(n);
	}

	long long int sum = 0;
	int first;
	int last;
	bool found = false;

	for (int i = 0; i < nums.size()-1 && !found; ++i, sum = 0) {
		first = i;
		sum += nums[i];
		for (int j = i+1; j < nums.size(); ++j) {
			last = j;
			sum += nums[j];
			if (sum == 776203571) {
				found = true;
				break;
			}
		}
	}

	std::vector<unsigned long long int>::iterator begin = nums.begin() + first;
	std::vector<unsigned long long int>::iterator end = nums.begin() + last + 1;

	std::vector<unsigned long long int> cont(begin, end);

	std::sort(cont.begin(), cont.end());

	std::cout << cont[0] + cont[cont.size() - 1] << std::endl;
}