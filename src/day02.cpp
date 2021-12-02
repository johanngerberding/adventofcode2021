#include <bits/stdc++.h>

int main() {
    int horizontal = 0;
    int depth = 0;
    int aim = 0;

    std::ifstream infile("../inputs/day02.txt");
    std::string line;
    while(getline(infile, line)) {
        size_t pos = line.find(" ");
        std::string command = line.substr(0, pos);
        std::string num = line.substr(pos+1);
        int number = stoi(num);
        
        if (command == "forward") {
            horizontal += number;
            depth += (aim * number);
        } else if(command == "down") {
            aim += number;
        } else if(command == "up") {
            aim -= number;
        } else {
            std::cout << "Unknown command" << std::endl;
            return 0;
        }
    
    }

    int result = depth * horizontal;
    std::cout << "Result: " << result << std::endl;

    return 0;

}