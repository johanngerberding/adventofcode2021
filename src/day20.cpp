#include <fstream>
#include <iostream>

struct Image {
    int width;
    int height;
    
    void enhance(std::string &enhancement) {

    } 

    friend std::istream&<<(std::istream &s, Image &im) {
        std::string line;
        while (getline(s, line)) {
            
        }
        return s;
    }
};

int main() {
    std::ifstream infile("../inputs/day20.txt");
    std::string enhance;
    getline(infile, enhance);
    
    
    

    return 0;
}
