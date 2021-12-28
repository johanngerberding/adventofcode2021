#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <ostream>
#include <istream>



/*
struct Reactor {
    //std::vector<Cube> cubes;
    std::map<std::vector<int32_t>, int32_t> cubes; 
    uint64_t switches;
    Reactor () {
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
   
    std::vector<int32_t> parseInstruction(const std::string &line) {
        std::vector<int32_t> instructions;
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
        int32_t x1 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(x1);
        std::cout << "x1 -> " << x1 << '\n';
       
        pos = line.find('.', next+1);
        next = line.find(',', pos);
        int32_t x2 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(x2);
        std::cout << "x2 -> " << x2 << '\n';
        
        pos = line.find('=', next+1);
        next = line.find('.', pos);
        int32_t y1 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(y1);
        std::cout << "y1 -> " << y1 << '\n';

        pos = line.find('.', next+1);
        next = line.find(',', pos);
        int32_t y2 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(y2);
        std::cout << "y2 -> " << y2 << '\n';

        pos = line.find('=', next+1);
        next = line.find('.', pos);
        int32_t z1 = std::stoi(line.substr(pos+1, next));
        instructions.push_back(z1);
        std::cout << "z1 -> " << z1 << '\n';

        pos = line.find('.', next+1);
        int32_t z2 = std::stoi(line.substr(pos+1));
        instructions.push_back(z2);
        std::cout << "z2 -> " << z2 << '\n';

        return instructions;
    }

    void switchCube(std::vector<int32_t> &instructions) {
        // validate coordinates
        if (instructions[1] > 50 || instructions[2] < -50 || 
                instructions[3] > 50 || instructions[4] < -50 ||
                instructions[5] > 50 || instructions[6] < -50) {
            return;
        }

        for (int32_t i = instructions[1]; i <= instructions[2]; i++) {
            for (int32_t j = instructions[3]; j <= instructions[4]; j++) {
                for (int32_t k = instructions[5]; k <= instructions[6]; k++) {
                    std::vector<int32_t> s {i,j,k};
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
                    } else {
                        cubes.insert(std::make_pair(s, instructions[0]));
                        if (instructions[0] == 1) {
                            switches++;
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
        std::vector<int32_t> ins;
        ins = react->parseInstruction(line);
        react->switchCube(ins);
    }
    
    std::cout << react->switches << '\n'; 

}

*/

// Code from here, for Part 2
// https://itnext.io/modern-c-in-advent-of-code-day22-ff85b2540d9b

struct Point3D {
    int64_t x;
    int64_t y;
    int64_t z;
};

struct CuboidInstruction {
    Point3D min;
    Point3D max;
    bool on;
    operator int64_t() const;
    friend std::istream &operator>>(std::istream &, CuboidInstruction &);
    friend std::ostream &operator<<(std::ostream &, CuboidInstruction &);
    friend auto operator<=>(const CuboidInstruction &, const CuboidInstruction &) = default;
};


std::istream &operator>>(std::istream &s, CuboidInstruction &cube) {
    std::string line;
    if (!getline(s, line))
        return s;

    CuboidInstruction result;
    if (line.starts_with("on")) {
        result.on = true;
    } else if (line.starts_with("off")) {
        result.on = false;
    } else {
        throw std::runtime_error("Failed to parse input.");
    }

    auto xpos = line.find("x=");
    if (xpos == std::string::npos)
        throw std::runtime_error("Failed to parse input, did not find x coordinate.");
    result.min.x = std::stoll(line.substr(xpos+2));
    auto xpos_max = line.find("..", xpos+2);
    if (xpos_max == std::string::npos) {
        throw std::runtime_error("Failed to parse input, did not find last x coordinate.");
    }
    result.max.x = std::stoll(line.substr(xpos_max + 2));

    auto ypos = line.find("y=");
    if (ypos == std::string::npos) {
        throw std::runtime_error("Failed to parse input, didn't find y coordinate.");
    }
    result.min.y = std::stoll(line.substr(ypos + 2));
    auto ypos_max = line.find("..", ypos + 2);
    if (ypos_max == std::string::npos) {
        throw std::runtime_error("Failed to parse input, did not find last y coordinate.");
    }
    result.max.y = std::stoll(line.substr(ypos_max + 2));

    auto zpos = line.find("z=");
    if (zpos == std::string::npos) 
        throw std::runtime_error("Failed to parse input, first z coordinate.");
    result.min.z = std::stoll(line.substr(zpos + 2));
    auto zpos_max = line.find("..", zpos + 2);
    if (zpos_max == std::string::npos) {
        throw std::runtime_error("Failed to parse input, last z coordinate");
    }
    result.max.z = std::stoll(line.substr(zpos_max + 2));
    
    cube = result;

    return s;
}


CuboidInstruction::operator int64_t() const {
    if (on) {
        return (max.x - min.x + 1) * (max.y - min.y + 1) * (max.z - min.z + 1);
    } else {
        return -1 * (max.x - min.x + 1) * (max.y - min.y + 1) * (max.z - min.z + 1);
    }
}


std::optional<CuboidInstruction> intersect(const CuboidInstruction &lhs, const CuboidInstruction &rhs) {
    int64_t min_x = std::max(lhs.min.x, rhs.min.x);
    int64_t max_x = std::min(lhs.max.x, rhs.max.x);
    int64_t min_y = std::max(lhs.min.y, rhs.min.y);
    int64_t max_y = std::min(lhs.max.y, rhs.max.y);
    int64_t min_z = std::max(lhs.min.z, rhs.min.z);
    int64_t max_z = std::min(lhs.max.z, rhs.max.z);
    if (min_x > max_x || min_y > max_y || min_z > max_z) {
        return {};
    }
    return CuboidInstruction{{min_x, min_y, min_z}, {max_x, max_y, max_z}, !lhs.on};
}

int64_t apply_instructions(std::istream &in, std::optional<CuboidInstruction> limit) {
    std::string line;
    std::vector<CuboidInstruction> cuboids;
    CuboidInstruction cube;
    while (in >> cube) {
        if (limit.has_value()) {
            auto smaller = intersect(cube, limit.value());
            if (smaller.has_value()) {
                cube = smaller.value();
            } else {
                continue;
            }
        }

        std::vector<CuboidInstruction> merge;
        if (cube.on) {
            merge.push_back(cube);
        }
        for (auto &c: cuboids) {
            auto inter = intersect(c, cube);
            if (inter.has_value()) {
                merge.push_back(inter.value());
            }
        }
        std::ranges::copy(merge, std::back_insert_iterator(cuboids));
    }

    return std::accumulate(cuboids.begin(), cuboids.end(), INT64_C(0), std::plus<>());
}




int main() {
    std::ifstream infile("../inputs/day22.txt");
    
    std::cout << "Sum => " << apply_instructions(infile, {}) << "\n";

    infile.close();
}

