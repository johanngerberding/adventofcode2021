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
    std::ifstream infile("../inputs/day06.txt");
    std::string timers;
    std::getline(infile, timers);
    std::vector<int> fishes;
    fishes = split(timers);

    std::vector<long long> val_counts {0,0,0,0,0,0,0,0,0};
    std::cout << val_counts.size() << std::endl;
    for (auto el: fishes) {
        val_counts[el]++;
    }

    for (size_t i=0; i < val_counts.size(); i++) {
        std::cout << i << ": " << val_counts[i] << std::endl;
    }

    int num_steps = 256;
    
    for (int j=0; j<num_steps; j++) {
        // werte schieben
        long long temp = val_counts.at(0);
        for (size_t i = 0; i < val_counts.size() - 1; i++)
        {
            val_counts.at(i) = val_counts.at(i + 1);
        }
        val_counts.at(val_counts.size() - 1) = temp;
        val_counts.at(6) += temp;
    }

    for (size_t i=0; i < val_counts.size(); i++) {
        std::cout << i << ": " << val_counts[i] << std::endl;
    }

    long long sum = 0;
    for (auto el: val_counts) {
        sum += el;
    }

    std::cout << sum << std::endl;
    
    infile.close();
}