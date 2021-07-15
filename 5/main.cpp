#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>

int main() {
	std::ifstream istr("input.txt");
	std::string current = "";



	std::vector<int> sids;
	//int seat = -1;
	while (std::getline(istr, current)) {
	int maxr = 127;
	int minr = 0;
	int maxc = 7;
	int minc = 0;
		for (uint i = 0; i < current.size(); ++i) {
			if (current[i] == 'F') {
				if ((maxr-minr) % 2 == 1)
					--maxr;
				maxr -= (maxr-minr)/2;
			}
			if (current[i] == 'B') {
				if ((maxr-minr) % 2 == 1)
					++minr;
				minr += (maxr-minr)/2;
			}
			if (current[i] == 'L') {
				if ((maxc-minc) % 2 == 1)
					--maxc;
				maxc -= (maxc-minc)/2;
			}
			if (current[i] == 'R') {
				if ((maxc-minc) % 2 == 1)
					++minc;
				minc += (maxc-minc)/2;
			}
		}
		assert(maxr==minr);
		assert(maxc==minc);
		sids.push_back(maxr*8 + maxc);
	}

	std::sort(sids.begin(), sids.end());
	int last = sids[0];
	for (uint i = 1; i < sids.size(); ++i) {
		if (i == 470)
			std::cout << "HELLO" << std::endl;
		if (sids[i] != last + 1) {
			std::cout << sids[i] << std::endl;
		}
		last = sids[i];
	}

	//std::cout << sids[sids.size()-1] << std::endl;
}