#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

int sumOccurrences(const std::vector<std::string>& allergens, const std::map<std::string, int>& counts) {
    int sum = 0;

    for (auto it = counts.begin(); it != counts.end(); ++it) {
        sum += it->second;
    }

    for (std::string s : allergens) {
        sum -= counts.find(s)->second;
    }
    return sum;
}

bool removeFound(std::vector<std::string>& identified,\
std::set<std::string>& potentialSources) {
    for (std::string s : identified) {
        auto it = potentialSources.find(s);
        if (it != potentialSources.end()) {
            potentialSources.erase(it);
        }
    }

    if (potentialSources.size() == 1) {
        identified.push_back(*(potentialSources.begin()));
        return true;
    }
    return false;
}

void checkAllergen(std::set<std::string>& potentialSources,\
const std::set<std::string>& ingredients) {
    std::set<std::string> common;

    for (std::string s : potentialSources) {
        if (ingredients.find(s) != ingredients.end()) {
            common.insert(s);
        }
    }
    potentialSources = common;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Incorrect usage. Usage: ./main.out 'input'\n";
        exit(1);
    }

    std::ifstream istr(argv[1]);
    std::string input;

    std::map<std::string, std::set<std::string> > allergens;

    int delim, begin, end;
    std::string allergen;
    std::set<std::string> ingredients;
    std::map<std::string, int> counter;
    std::vector<std::string> identified;
    std::string ingredient;

    while (getline(istr, input)) {
        delim = input.find('(');

        for (begin = -1; begin < delim - 1; begin = end) {
            end = input.find(' ', begin + 1);
            ingredient = input.substr(begin + 1, end - begin - 1);
            auto it = counter.find(ingredient);
            if (it == counter.end()) {
                counter.insert(std::make_pair(ingredient, 1));
            } else {
                ++it->second;
            }
            ingredients.insert(ingredient);
        }

        end = input.find(' ', delim);

        while (end != -1) {
            begin = end;
            end = input.find(' ', begin + 1);
            if (end == -1) {
                allergen = input.substr(begin + 1);
                allergen.pop_back();
            } else {
                allergen = input.substr(begin + 1, end - begin - 2);
            }
            auto aitr = allergens.find(allergen);
            if (aitr == allergens.end()) {
                allergens.insert(std::make_pair(allergen, ingredients));
            } else {
                checkAllergen(aitr->second, ingredients);
                if (aitr->second.size() == 1) {
                    std::string word = *(aitr->second.begin());
                    bool found = false;
                    for (std::string s : identified) {
                        if (s == word) {
                            found = true;
                        }
                    }
                    if (!found) identified.push_back(word);
                }
            }
        }
        ingredients.clear();
    }

    for (auto it = allergens.begin(); it != allergens.end(); ++it) {
        if (it->second.size() == 1) continue;
        bool nIdentified = removeFound(identified, it->second);
        if (nIdentified == true) it = allergens.begin();
    }

    //std::cout << "The number of non-allergen occurrences is: " << sumOccurrences(identified, counter) << "\n"; PART 1

    for (auto it = allergens.begin(); it != allergens.end();) {
        std::cout << *(it->second.begin());
        if (++it != allergens.end()) {
            std::cout << ',';
        }
    }
    std::cout << "\n";
}