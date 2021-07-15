#include <fstream>
#include <iostream>
#include <string>
#include <vector> //USED FOR PART 2 ONLY
/*
void compute(long long& lhs, long long rhs, char op) {
    if (op == '+') {
        lhs += rhs;
    } else {
        lhs *= rhs;
    }
}

long long calculate(std::string l) {
    long long ans = 0;
    char operation = '+';
    for (unsigned int i = 0; i < l.size(); i += 2) {
        if (l[i] == '(') {
            int closeCount = 0;
            int openCount = 1;
            ++i;
            int end = i;
            for (; openCount > closeCount; ++end) {
                if (l[end] == '(') ++openCount;
                else if (l[end] == ')') ++closeCount;
            }
            compute(ans,calculate(l.substr(i, end-i)), operation);
            i = end-1;
        } else {
            if (!isdigit(l[i])) {
                operation = l[i];
            } else {
                compute(ans, l[i] - '0', operation);
            }
        }
    }
    return ans;
}
*/
//PART 2
void compute(long long& lhs, long long rhs, char op) {
    if (op == '+') {
        lhs += rhs;
    } else {
        lhs *= rhs;
    }
}

long long calculate(std::string l) {
    long long ans = 1;
    long long current = 0;
    std::vector<long long> terms;
    for (unsigned int i = 0; i < l.size(); i += 2) {
        if (l[i] == '(') {
            int closeCount = 0;
            int openCount = 1;
            ++i;
            int end = i;
            for (; openCount > closeCount; ++end) {
                if (l[end] == '(') ++openCount;
                else if (l[end] == ')') ++closeCount;
            }

            current += calculate(l.substr(i, end-i));
            i = end-1;
        } else {
            if (!isdigit(l[i])) {
                if (l[i] == '*') {
                    terms.push_back(current);
                    current = 0;
                }
            } else {
                current += l[i] - '0';
            }
        }
    }
    terms.push_back(current);
    for (unsigned int i = 0; i < terms.size(); ++i) {
        ans *= terms[i];
    }
    return ans;
}

int main() {
    std::ifstream istr("input.txt");
    std::string input;
    long long ans = 0;

    while (getline(istr, input)) {
        long long sum = calculate(input);
        std::cout << sum << std::endl;
        ans += sum;
    }

    std::cout << ans << std::endl;
}