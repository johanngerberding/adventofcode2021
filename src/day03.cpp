#include <bits/stdc++.h>

int binaryStringToDecimal(std::string str) {
    long long binary = std::stoll(str);
    int dec = 0;
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

void reduceVector(std::vector<std::string> &lines, 
                                      int mode) {
    // mode 1 -> keep bigger count 
    // mode 0 -> keep smaller count 
    for (size_t i = 0; i < lines[0].size(); i++) {
        size_t count = 0;
        for (auto el: lines) {
            if (mode == 1) {
                if (el[i] == '1') {
                    count++;
                }
            } else {
                if (el[i] == '0') {
                    count++;
                }
            }
        }
        std::stack<int> del_idxs;
        char comp;
        if (mode == 1) {
            comp = '1';
        } else {
            comp = '0';
        }
    
        if (count >= (lines.size() / 2)) {
            for (size_t j = 0; j < lines.size(); j++) {
                if (lines[j][i] != comp) {
                    del_idxs.push(j);
                }
            }
            
        } else {
            for (size_t j = 0; j < lines.size(); j++) {
                if (lines[j][i] == comp) {
                    del_idxs.push(j);
                }
            }
        }

        while (!del_idxs.empty()) {
            lines.erase(lines.begin() + del_idxs.top());
            del_idxs.pop();
        }

        if (lines.size() == 1) {
            return;
        }
    }
}

int main() {

    std::ifstream infile("../inputs/day03.txt");
    std::string line;
    std::vector<std::string> lines;
    while(getline(infile, line)) {
        lines.push_back(line);
    }

    //std::string gamma;
    //std::string epsilon;

    std::string oxygen_generator;
    std::string co_scrubber; 

    std::cout << lines.size() << std::endl;
    std::vector<std::string> lines_copy;
    lines_copy = lines;

    reduceVector(lines, 1);
    reduceVector(lines_copy, 0);

    std::cout << lines.size() << std::endl;
    std::cout << lines_copy.size() << std::endl;
    
    oxygen_generator = lines[0];
    co_scrubber = lines_copy[0];

    int oxygen = binaryStringToDecimal(oxygen_generator);
    std::cout << oxygen << std::endl;
    int co = binaryStringToDecimal(co_scrubber);
    std::cout << co << std::endl;
    int result = oxygen * co;
    std::cout << result << std::endl;
    
    //int gammaRate = binaryStringToDecimal(gamma);
    //int epsilonRate = binaryStringToDecimal(epsilon);
    //int result = gammaRate * epsilonRate;
    //std::cout << result << std::endl;
    infile.close();
    return 0;
}
