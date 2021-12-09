#include <bits/stdc++.h>


size_t split (const std::string &line, std::vector<std::vector<std::string>> &parts) {
    
    std::string p1;
    std::string p2;

    size_t pos = line.find('|');
    size_t initialPos = 0;

    while( pos != std::string::npos ) {
        p1 = line.substr( initialPos, pos - initialPos - 1 );
        initialPos = pos + 2;

        pos = line.find( '|', initialPos );
    }

    // Add the last one
    p2 = line.substr( initialPos, std::min( pos, line.size()) - initialPos + 1 );

    std::vector<std::string> part1;
    std::vector<std::string> part2;

    pos = p1.find(' ');
    initialPos = 0;
    std::string temp;

    while( pos != std::string::npos ) {
        temp = p1.substr( initialPos, pos - initialPos );
        part1.push_back(temp);
        initialPos = pos + 1;

        pos = p1.find( ' ', initialPos );
    }

    // Add the last one
    temp = p1.substr( initialPos, std::min( pos, p1.size()) - initialPos + 1 );
    part1.push_back(temp);


    pos = p2.find(' ');
    initialPos = 0;

    while( pos != std::string::npos ) {
        temp = p2.substr( initialPos, pos - initialPos );
        part2.push_back(temp);
        initialPos = pos + 1;

        pos = p2.find( ' ', initialPos );
    }

    // Add the last one
    temp = p2.substr( initialPos, std::min( pos, p2.size()) - initialPos + 1 );
    part2.push_back(temp);

    parts.push_back(part1);
    parts.push_back(part2);

    return parts.size();
}


int main() {

    std::ifstream infile("../inputs/day08.txt");
    std::string line;
    
    std::vector<int> sums;

    while (std::getline(infile, line)) {
        std::vector<std::vector<std::string>> parts;
        split(line, parts);

        std::map<int, std::set<char>> numbers;
        std::map<char, int> counts;
        
        for (auto el: parts[0]) {
            size_t l = el.size();
            if (l == 2) {
                std::set<char> chars;
                for (auto c: el) {
                    chars.insert(c);
                }
                numbers.insert( std::pair<int, std::set<char>>(1, chars) );
            } else if (l == 4) {
                std::set<char> chars;
                for (auto c: el) {
                    chars.insert(c);
                }
                numbers.insert( std::pair<int, std::set<char>>(4, chars) );
            } else if (l == 3) {
                std::set<char> chars;
                for (auto c: el) {
                    chars.insert(c);
                }
                numbers.insert( std::pair<int, std::set<char>>(7, chars) );
            } else if (l == 7) {
                std::set<char> chars;
                for (auto c: el) {
                    chars.insert(c);
                }
                numbers.insert( std::pair<int, std::set<char>>(8, chars) );
            }
            for (auto c: el) {
                if (counts.find(c) == counts.end()) {
                    counts.insert(std::pair<char, int>(c, 1));
                } else {
                    counts[c]++;
                }
            }
        }

        std::set<char> result;
        std::set_difference(numbers[7].begin(), numbers[7].end(), 
            numbers[1].begin(), numbers[1].end(),
            std::inserter(result, result.end()));
        
        char a = *result.begin();
        // insert a 
        result.insert(numbers[4].begin(), numbers[4].end());

        /* number counts
        a: 8 -> like before: 7 - 1
        b: 6 -> unique
        c: 8 -> after having a, we have c
        d: 7 
        e: 4 -> unique
        f: 9 -> unique
        g: 7 
        */

       char b; 
       char c;
       char e;
       char f;

        for (auto it = counts.begin(); it != counts.end(); ++it) {
            if (it->second == 6)
                b = it->first;
            if (it->second == 4)
                e = it->first;
            if (it->second == 9)
                f = it->first;
            if (it->second == 8 && it->first != a)
                c = it->first;
        }

        std::set<char> bcf {b, c, f};
        std::set<char> res;
        std::set_difference(numbers[4].begin(), numbers[4].end(), 
            bcf.begin(), bcf.end(),
            std::inserter(res, res.end()));
        
        char d = *res.begin();
        //std::cout << "d -> " << d << std::endl;


        std::set<char> abcdef {a, b, c, d, e, f};
        std::set<char> reslt;
        std::set_difference(numbers[8].begin(), numbers[8].end(), 
            abcdef.begin(), abcdef.end(),
            std::inserter(reslt, reslt.end()));
        
        char g = *reslt.begin();
        //std::cout << "g -> " << g << std::endl;

        std::map<std::set<char>, int> info {
            {{a,b,c,e,f,g}, 0},
            {{c,f}, 1},
            {{a,c,d,e,g}, 2},
            {{a,c,d,f,g}, 3},
            {{b,c,d,f}, 4},
            {{a,b,d,f,g}, 5},
            {{a,b,d,e,f,g}, 6},
            {{a,c,f}, 7},
            {{a,b,c,d,e,f,g}, 8},
            {{a,b,c,d,f,g}, 9}
        };

        std::string nums;
        for (auto el: parts[1]) {
            std::set<char> chars;
            for (auto c: el) {
                chars.insert(c);
            }
            int num = info[chars];
            std::string s = std::to_string(num);
            nums += s;
        }
       
        int sum = std::stoi(nums);
        sums.push_back(sum);

    }

    int r = 0;
    for (auto el: sums)
        r += el;

    std::cout << r << std::endl;

    infile.close();

}