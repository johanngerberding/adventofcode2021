#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <map>


struct Cube {
    int x;
    int y;
    int z;
    int on;

};


struct Reactor {
    //std::vector<Cube> cubes;
    std::map<std::vector<int>, int> cubes; 
    int switches;
    Reactor () {
        cubes = {};
        switches = 0;
        for (int i=-50; i <= 50; i++) {
            for (int j=-50; j <=50; j++) {
                for (int k=-50; k <= 50; k++) {
                    std::vector<int> coords {i,j,k};
                    cubes.insert(std::make_pair(coords, 0));
                }
            }
        }
    }
   
    std::vector<int> parseInstruction(const std::string &line) {
        std::vector<int> instructions;
        size_t pos = line.find(' ');
        std::string power = line.substr(0, pos);
        std::cout << power << '\n';
        if (power == "on") {
            instructions.push_back(1);
        } else if (power == "off") {
            instructions.push_back(0);
        } else {
            std::cout << "Unknown statement\n";
        }

        pos = line.find('=', pos);
        size_t next = line.find('.', pos);
        int x1 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(x1);
        std::cout << "x1 -> " << x1 << '\n';
        
        pos = line.find('.', next+1);
        next = line.find(',', pos);
        int x2 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(x2);
        std::cout << "x2 -> " << x2 << '\n';
        
        pos = line.find('=', next+1);
        next = line.find('.', pos);
        int y1 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(y1);
        std::cout << "y1 -> " << y1 << '\n';

        pos = line.find('.', next+1);
        next = line.find(',', pos);
        int y2 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(y2);
        std::cout << "y2 -> " << y2 << '\n';

        pos = line.find('=', next+1);
        next = line.find('.', pos);
        int z1 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(z1);
        std::cout << "z1 -> " << z1 << '\n';

        pos = line.find('.', next+1);
        int z2 = std::stoi(line.substr(pos+1));
        instructions.push_back(z2);
        std::cout << "z2 -> " << z2 << '\n';

        return instructions;
    }

    void switchCube(std::vector<int> &instructions) {
        // validate coordinates
        if (instructions[1] > 50 || instructions[2] < -50 || 
                instructions[3] > 50 || instructions[4] < -50 ||
                instructions[5] > 50 || instructions[6] < -50) {
            return;
        }


        for (int i = instructions[1]; i <= instructions[2]; i++) {
            for (int j = instructions[3]; j <= instructions[4]; j++) {
                for (int k = instructions[5]; k <= instructions[6]; k++) {
                    std::vector<int> s {i,j,k};
                    auto it = cubes.find(s);
                    if (it != cubes.end()) {
                        if (it->second != instructions[0]) {
                            it->second = instructions[0];
                            if (instructions[0] == 1) {
                                switches++;
                            } else {
                                switches--;
                            }
                            
                        }
                    }
                }
            }
        }
    }

};


int main() {
    std::ifstream infile("../inputs/day22.txt");
    std::string line;
    Reactor* react = new Reactor(); 

    while (getline(infile, line)) {
        std::vector<int> ins;
        ins = react->parseInstruction(line);
        react->switchCube(ins);
    }
    
    std::cout << react->switches << '\n'; 

}
