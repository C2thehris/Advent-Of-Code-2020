#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

enum State {active, inactive};
typedef std::vector<State> Line;
typedef std::vector<Line> Grid;
typedef std::unordered_map<int, Grid> Space;
typedef std::unordered_map<int, Space> FDSpace;

int count(Space map) {
    int total = 0;
    for (Space::iterator itr = map.begin(); itr != map.end(); ++itr) {
        for (Grid::iterator gitr = itr->second.begin(); gitr != itr->second.end(); ++gitr) {
            for (Line::iterator litr = gitr->begin(); litr != gitr->end(); ++litr) {
                if (*litr == active) ++total;
            } 
        }
    }
    return total;
}

int count_surrounding(Space map, int x, int y, int z) {
    int mSize = map.size()/2;
    int count = 0;
    for (int i = z-1; i < z+2; ++i) {
        if (i < mSize*-1 || i > mSize) continue;
        for (int j = y-1; j < y+2; ++j) {
            if (j < 0 || j >= signed(map[z].size())) continue;
            for (int k = x-1; k < x+2; ++k) {
                if (k < 0 || k >= signed(map[z].size())) continue;
                if (k == x && j == y && i == z) continue;
                if (map[i][j][k] == active) ++count;
            }
        }
    }
    return count;
}

void expand_Space(Space& map, int index) {
    Line l;
    Space::iterator itr = map.begin();
    for (unsigned int i = 0; i < itr->second.size(); ++i) {
        l.push_back(inactive);
    }
    Grid empty;
    for (unsigned int i = 0; i < itr->second.size(); ++i) {
        empty.push_back(l);
    }
    itr = map.begin();


    map.insert(std::make_pair(index, empty));
    map.insert(std::make_pair(-1*index, empty));
    for (itr = map.begin(); itr != map.end(); ++itr) {
        itr->second.insert(itr->second.begin(), l);
        itr->second.push_back(l);
        for (Grid::iterator gitr = itr->second.begin(); gitr != itr->second.end(); ++gitr) {
            gitr->insert(gitr->begin(), inactive);
            gitr->push_back(inactive);
        }
    }
}

Space update(const Space& map) {
    Space space;
    for (Space::const_iterator sitr = map.begin(); sitr != map.end(); ++sitr) {
        Grid g;
        for (int i = 0; i < signed(sitr->second.size()); ++i) {
            Line l;
            for (int j = 0; j < signed(sitr->second.size()); ++j) {
                int total = count_surrounding(map, j, i, sitr->first);
                if ((sitr->second)[i][j] == active){
                    if (total == 2 || total == 3) l.push_back(active);
                    else l.push_back(inactive);
                } else {
                    if (total == 3) l.push_back(active);
                    else l.push_back(inactive);
                }
            }
            g.push_back(l);
        }
        space.insert(std::make_pair(sitr->first, g));
    }
    return space;
}

int main() {

    Space map;

    std::ifstream istr("input.txt");
    int ans = 0;

    std::string input;

    Grid z0;

    while (istr >> input) {
        Line l;
        for (unsigned int i = 0; i < input.size(); ++i) {
            if (input[i] == '#') l.push_back(active);
            else l.push_back(inactive);
        }
        z0.push_back(l);
    }

    map.insert(std::make_pair(0, z0));

    for (int i = 1; i < 7; ++i) {
        expand_Space(map, i);
        map = update(map);
    }
    ans = count(map);
    std::cout << ans << std::endl;
}