#include <bits/stdc++.h>

long long binaryStringToDecimal(std::string str) {
    long long binary = std::stoll(str);
    long long dec = 0;
    int base = 1;
    long long temp = binary;
    while(temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec += last_digit * base;
        base = base * 2;
    }
    return dec;
}


std::string reduce(std::vector<std::string> &lines, int mode) {
    
    for (size_t i = 0; i < lines[0].size(); i++) {
        // count occurences
        int oneCount {0};
        int zeroCount {0};
        for (auto line: lines) {
            if (line[i] == '1') {
                oneCount++;
            } else {
                zeroCount++;
            }
        }
        std::stack<int> delIdxs;
        if (mode == 1) {
            // if more 1's -> del 0's
            if (oneCount >= zeroCount) {
                for (size_t j = 0; j < lines.size(); j++) {
                    if (lines[j][i] == '0') {
                        delIdxs.push(j);
                    }
                }
            } else {
                for (size_t j = 0; j < lines.size(); j++) {
                    if (lines[j][i] == '1') {
                        delIdxs.push(j);
                    }
                }
            }
        } else {
            // if less or equal 0's -> del 1's
            if (zeroCount <= oneCount) {
                for (size_t j = 0; j < lines.size(); j++) {
                    if (lines[j][i] == '1') {
                        delIdxs.push(j);
                    }
                }
            } else {
                for (size_t j = 0; j < lines.size(); j++) {
                    if (lines[j][i] == '0') {
                        delIdxs.push(j);
                    }
                }
            }
        }

        while (!delIdxs.empty() && !lines.empty()) {
            lines.erase(lines.begin() + delIdxs.top());
            delIdxs.pop();
        }

        if (lines.size() == 1)
            return lines[0];

    }
    
    return lines[0];

}


int main() {

    std::ifstream infile("../inputs/day03.txt");
    std::string line;
    std::vector<std::string> lines;
    while(getline(infile, line)) {
        lines.push_back(line);
    }

    std::string oxygen_generator;
    std::string co_scrubber; 

    std::vector<std::string> lines_copy;
    for (size_t k=0; k<lines.size(); k++)
        lines_copy.push_back(lines[k]);

    oxygen_generator = reduce(lines, 1);
    co_scrubber = reduce(lines_copy, 0);
    std::cout << oxygen_generator << std::endl;
    std::cout << co_scrubber << std::endl;

    long long oxygen = binaryStringToDecimal(oxygen_generator);
    std::cout << oxygen << std::endl;
    long long co = binaryStringToDecimal(co_scrubber);
    std::cout << co << std::endl;
    long long result = oxygen * co;
    std::cout << result << std::endl;
    
    //int gammaRate = binaryStringToDecimal(gamma);
    //int epsilonRate = binaryStringToDecimal(epsilon);
    //int result = gammaRate * epsilonRate;
    //std::cout << result << std::endl;
    infile.close();
    return 0;
}
