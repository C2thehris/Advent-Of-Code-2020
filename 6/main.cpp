#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int count(std::vector<bool>& answers) {
	int count = 0;
	for (int i = 0; i < answers.size(); ++i) {
		if (answers[i])
			++count;
	}
	return count;
}

void check(std::vector<bool> &answers, std::vector<bool> &current) {
	for (int i = 0; i < answers.size(); ++i) {
		if (answers[i] && !current[i])
			answers[i] = false;
	}
}

void reset(std::vector<bool> &answers) {
	for (int i = 0; i < 26; ++i) {
		answers[i] = false;
	}
}

int main() {
	long int answer = 0;
	std::ifstream istr("input.txt");

	std::string input;
	std::vector<bool> answers;
	std::vector<bool> current;

	bool one = false;

	for (int i = 0; i < 26; ++i) {
		answers.push_back(false);
		current.push_back(false);
	}


	while (getline(istr, input)) {
		if (input == "\r") {
			answer += count(answers);
			reset(answers);
			one = false;
			continue;
		}
		reset(current);

		if (one) {
			for (int i = 0; i < input.size(); ++i) {
				if(input[i] == '\r') {
					break;
				}
				current[input[i] - 'a'] = true;
			}
			check(answers, current);

		}
		if (!one) {
			one = true;
			for (int i = 0; i < input.size(); ++i) {
				if (input[i] == '\r') {
					break;
				}
				answers[input[i] - 'a'] = true;
			}
		}
	}

	answer += count(answers);

	std::cout << answer << std::endl;
}