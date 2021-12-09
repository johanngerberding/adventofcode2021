#include <bits/stdc++.h>


struct Point {
    int val;
    int x,y;
    std::vector<int> adj;
};


int main() {
    std::vector<std::vector<int>> grid;
    std::ifstream infile("../inputs/day09.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::vector<int> nums;
        for (auto el: line) {
            int n = el - '0';
            nums.push_back(n);
        }
        grid.push_back(nums);
    }

    std::vector<Point> points;

    for (size_t row=0; row < grid.size(); row++) {
        for (size_t col=0; col < grid[0].size(); col++) { 
            Point p = {};
            p.val = grid[row][col];
            p.x = col;
            p.y = row;
            // add x-1, y
            if ((p.x-1) >= 0) {
                p.adj.push_back(grid[p.y][p.x-1]);
            }
            // add x, y-1
            if ((p.y-1) >= 0) {
                p.adj.push_back(grid[p.y-1][p.x]);
            }
            // add x+1, y
            if ((p.x+1) < (grid[0].size())) {
                p.adj.push_back(grid[p.y][p.x+1]);
            }
            // add x, y+1
            if ((p.y+1) < (grid.size())) {
                p.adj.push_back(grid[p.y+1][p.x]);
            }
            points.push_back(p);
        }
    }

    std::vector<Point> low_points;
    for (auto el: points) {
        bool t = true;
        for (auto a: el.adj) {
            if (a <= el.val)
                t = false;
        }
        if (t) {
            low_points.push_back(el);
        }
    }
    std::cout << "Low Points: " << std::endl;
    int result = 0;
    for (auto el: low_points) {
        std::cout << el.val << " -> ";
        for (auto a: el.adj) {
            std::cout << a << " ";
        }
        std::cout << std::endl;
        result += (el.val + 1);
    }
    std::cout << "=====================" << std::endl;

    std::cout << result << std::endl;

}