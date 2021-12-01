#include <bits/stdc++.h>


int main() {

    std::ifstream infile("../inputs/day01.txt");
    std::vector<int> depths;
    int temp;
    while(infile >> temp) {
        depths.push_back(temp);
    }
    int increased = 0;
    for (size_t i = 1; i < depths.size(); i++) {
        if (depths[i] > depths[i-1])
            increased++;
    }
    std::cout << "=========== PART 1 ==========" << std::endl;
    std::cout << "Increased: " << increased << std::endl;
    
    increased = 0;
    for (size_t i = 0; i < depths.size() - 3; i++) {
        int window1 = std::accumulate(depths.begin()+i, depths.begin()+i+3, 0);
        int window2 = std::accumulate(depths.begin() + i + 1, depths.begin() + i + 4, 0);
        
        if (window2 > window1)
            increased++;
    }


    std::cout << "========== PART 2 ==========" << std::endl;
    std::cout << "Increased: " << increased << std::endl;
    
    infile.close();

    return 0;
}