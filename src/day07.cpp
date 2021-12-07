#include <bits/stdc++.h>

std::vector<int> split(const std::string timers) {
    std::vector<int> nums;
    size_t pos = timers.find(',');
    size_t initialPos = 0;
    std::string temp;

    while( pos != std::string::npos ) {
        temp = timers.substr( initialPos, pos - initialPos );
        nums.push_back( std::stoi(temp) );
        initialPos = pos + 1;

        pos = timers.find(',', initialPos );
    }

    // Add the last one
    temp = timers.substr( initialPos, std::min( pos, timers.size()) - initialPos + 1 );
    nums.push_back( std::stoi(temp) );

    return nums;
}

int main() {
    std::ifstream infile("../inputs/day07.txt");
    std::string positions;
    std::getline(infile, positions);
    std::vector<int> nums = split(positions);

    std::vector<int>::iterator result_min = std::min_element(nums.begin(), nums.end());
    int min = nums.at(std::distance(nums.begin(), result_min));

    std::vector<int>::iterator result_max = std::max_element(nums.begin(), nums.end());
    int max = nums.at(std::distance(nums.begin(), result_max));

    std::cout << "min element: " << min << std::endl;
    std::cout << "max element: " << max << std::endl;

    long long distance = 100000000000;
    int start = min;

    for (int i=min; i <= max; i++) {
        long long temp = 0;
        for (auto el: nums) {
            temp += (((std::abs(el - i)) * (std::abs(el - i) + 1)) / 2);
        }
        if (temp < distance) {
            distance = temp;
            start = i;
        }
            
    }

    std::cout << "Best starting value: " << start << std::endl;
    std::cout << "Distance: " << distance << std::endl;
    
}