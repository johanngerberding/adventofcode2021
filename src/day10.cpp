#include <bits/stdc++.h>


int main() {
    std::ifstream infile("../inputs/day10.txt");
    std::string line;

    std::vector<char> openers {'(', '{', '[', '<'};
    std::vector<char> closers {')', '}', ']', '>'};

    std::map<char, char> comps {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
        {'<', '>'}
    };

    std::map<char, int> points {
        {')', 3},
        {']', 57},
        {'}', 1197},
        {'>', 25137}
    };

    std::map<char, int> p2points {
        {')', 1},
        {']', 2},
        {'}', 3},
        {'>', 4}
    };

    std::vector<char> illegals;
    std::vector<std::string> valids;

    while(std::getline(infile, line)) {
        std::stack<char> opened;
        bool valid = true;
        for (auto &c: line) {
            auto chr = std::find(openers.begin(), openers.end(), c);
            if (chr != openers.end()) {
                opened.push((*chr));
            } else {
                auto chr = std::find(closers.begin(), closers.end(), c);
                if (chr != closers.end()) {
                    char start = opened.top();
                    opened.pop();
                    char counter = comps[start];
                    if (c != counter) {
                        illegals.push_back(c);
                        valid = false;
                        break;
                    }
                }
            }
        }
        if (valid) {
            valids.push_back(line);
        }
        while (!opened.empty()) {
            std::cout << opened.top() << " ";
            opened.pop();
        }
        std::cout << std::endl;
    }

    std::cout << "Number of valid lines: " << valids.size() << std::endl;
    std::cout << "Illegal characters:" << std::endl;

    int sum = 0;
    for (auto el: illegals) {
        sum += points[el];
    }

    std::cout << "Sum of points: " << sum << std::endl;

    std::cout << "======== PART 2 ========" << std::endl;

    std::vector<long long> scores;
    
    for (auto &val: valids) {
        std::stack<char> opened;
        bool valid = true;
        for (auto &c: val) {
            auto chr = std::find(openers.begin(), openers.end(), c);
            if (chr != openers.end()) {
                opened.push((*chr));
            } else {
                auto chr = std::find(closers.begin(), closers.end(), c);
                if (chr != closers.end()) {
                    char start = opened.top();
                    opened.pop();
                    char counter = comps[start];
                    if (c != counter) {
                        //illegals.push_back(c);
                        valid = false;
                        break;
                    }
                }
            }
        }

        long long score = 0;
        std::vector<char> missing;
        while (!opened.empty()) {
            auto top = opened.top();
            opened.pop();
            missing.push_back(comps[top]);
        }

        for (size_t i=0; i < missing.size(); i++) {
            score *= 5;
            score += p2points[missing.at(i)];
        }
        scores.push_back(score);
    }

    std::sort(scores.begin(), scores.end());

    for (auto score: scores) {
        std::cout << score << std::endl;
    }

    int pos = (int)(scores.size() / 2);
    std::cout << scores.size() << std::endl;
    std::cout << pos << std::endl;

    std::cout << "middle: " << scores[pos] << std::endl;

    infile.close();

    return 0;
}