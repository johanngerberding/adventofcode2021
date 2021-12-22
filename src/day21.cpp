#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <map>
#include <utility>


struct Player {
    uint64_t id;
    uint64_t pos;
    uint64_t moves;
    uint64_t score;

    void move(uint64_t n) {
        moves++;

        if (n >= 10) {
            int steps = n % 10;
            pos = pos + steps;
            if (pos > 10) {
                pos -= 10;
            }
        } else {
            pos = pos + n;
            if (pos > 10) {
                pos -= 10;
            }
        }
        score += pos;
    }
};


struct Die {
    std::vector<int> pos;
    int rolls;

    int roll() {
        rolls = rolls + 3;
        auto sum = std::accumulate(pos.begin(), pos.end(), 0);
        for (auto &el: pos) {
            el = el+3;
            if (el > 100) {
                el = el - 100;
            }
        }
        return sum;
    }

    void display() const {
        std::cout << "----- DIE -----\n";
        std::cout << "Num rolls: " << rolls << '\n';
        std::cout << "Triplet: ";
        for (auto const &el : pos)
            std::cout << el << " ";
        std::cout << '\n';
    }
};


std::map<std::vector<uint64_t>, std::pair<uint64_t, uint64_t>> DP;

std::pair<uint64_t, uint64_t> countWins(uint64_t p1, uint64_t s1, uint64_t p2, uint64_t s2)  {
    std::vector<uint64_t> a {p1, p2, s1, s2};
    if (s1 >= 21)
        return std::make_pair(1, 0);
    if (s2 >= 21)
        return std::make_pair(0, 1);
    auto it = DP.find(a);
    if (it != DP.end()) {
        return it->second;
    }
    std::pair<uint64_t, uint64_t> ans (0,0);
    
    for (int i=1; i < 4; i++) {
        for (int j=1; j < 4; j++) {
            for (int k=1; k < 4; k++) {
                uint64_t new_p1 = (p1 + i + j + k) % 10;
                uint64_t new_s1 = s1 + new_p1 + 1;

                auto p = countWins(p2, s2, new_p1, new_s1);
                ans.first += p.second;
                ans.second += p.first;
            }
        }
    }
    
    DP.insert(std::make_pair(a, ans));
    return ans;
}


int main() {
    std::ifstream infile("../inputs/day21.txt");
    std::string line;
    getline(infile, line);
    std::cout << line << std::endl;
    uint64_t pos = line.at(28) - '0';
    uint64_t id = line.at(7) - '0';
    Player p1 {id, pos, 0, 0};
    
    getline(infile, line);
    std::cout << line << std::endl;
    id = line.at(7) - '0';
    pos = line.at(28) - '0';
    Player p2 {id, pos, 0, 0};
    
    // PART 1
    /*
    Die* die = new Die{{1,2,3}, 0};
    while (true) {
        int sum = die->roll();
        //std::cout << "P1 move " << sum << '\n'; 
        p1.move(sum);
        //std::cout << "P1 score: " << p1.score << '\n';
        if (p1.score >= 1000) {
            std::cout << die->rolls * p2.score << '\n';
            break;
        }
        sum = die->roll();
        //std::cout << "P2 move " << sum << '\n';
        p2.move(sum);
        //std::cout << "P2 score: " << p2.score << '\n';
        if (p2.score >= 1000) {
            std::cout << die->rolls * p1.score << '\n';
            break;
        }
    }
    */

    auto answer = countWins(p1.pos-1, 0, p2.pos-1, 0);
    std::cout << answer.first << " - " << answer.second << '\n';


    infile.close();
}
