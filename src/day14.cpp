#include <bits/stdc++.h>

int main() {

    std::ifstream infile("../inputs/day14.txt");
    std::string start;

    std::getline(infile, start);
    std::map<std::string, char> charmapping;

    char last = start.back();

    std::map<std::string, unsigned long long> paircounts;

    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            size_t pos = line.find(' ');
            std::string p1 = line.substr(0, pos);
            pos = line.find(' ', pos+1);
            std::string p2 = line.substr(pos+1, line.size());
            char p3 = p2[0];
            //p2 = p1[0] + p2 + p1[1];
            charmapping.insert(std::make_pair(p1, p3));
            std::cout << "Pair: " << p1 << "-" << p3 << std::endl;
        }
    }

    for (int i =0; i < start.size()-1; i++) {
        std::string temp = start.substr(i,2);
        if (paircounts.find(temp) == paircounts.end()) {
            paircounts.insert(std::make_pair(temp, 1));
        } else {
            paircounts[temp]++;
        }
    }


    for (int i=0; i < 40; i++) {
        std::map<std::string, unsigned long long> paircounts2;
        for (auto &el: paircounts) {
            char temp1 = el.first[0];
            char temp2 = charmapping[el.first];
            std::string temp;
            temp += temp1;
            temp += temp2;
            //temp1 += temp2;
            if (paircounts2.find(temp) == paircounts2.end()) {
                paircounts2.insert(std::make_pair(temp, el.second));
            } else {
                paircounts2[temp] += el.second;
            }
            char temp3 = el.first[1];
            std::string temp4;
            temp4 +=temp2;
            temp4 += temp3;
            //temp2 += temp3;
            if (paircounts2.find(temp4) == paircounts2.end()) {
                paircounts2.insert(std::make_pair(temp4, el.second));
            } else {
                paircounts2[temp4] += el.second;
            }

        }
        paircounts = paircounts2;
    }
    
    std::map<char, unsigned long long> charcounts;
    for (auto &el: paircounts) {
        char key = el.first[0];
        long long pcount = el.second;
        if (charcounts.find(key) == charcounts.end()) {
            charcounts.insert(std::make_pair(key, pcount));
        } else {
            charcounts[key] += pcount;
        }

    }

    charcounts[last]++;

    std::vector<long long> counts;

    for (auto &el: charcounts) {
        std::cout << el.first << " -> " << el.second << std::endl;
        counts.push_back(el.second);
    }
    
    unsigned long long max;
    unsigned long long min;

    auto it = std::max_element(counts.begin(), counts.end());
    max = (*it);
    auto it_ = std::min_element(counts.begin(), counts.end());
    min = (*it_);

    unsigned long long result = max - min;
    std::cout << "Result: " << result << std::endl;

    infile.close();
} 