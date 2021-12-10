#include <bits/stdc++.h>


struct Point {
    int val;
    int x;
    int y;
    bool visited;
    std::vector<Point*> adj;
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
            Point p;
            p.val = grid[row][col];
            p.x = col;
            p.y = row;
            p.visited = false;
            points.push_back(p);
        }
    }

    
    // add adjacent points to points in set
    for (auto &p: points) {
        // add x-1, y
        if ((p.x-1) >= 0) {
            auto it = std::find_if(points.begin(), points.end(), 
                                   [p](const Point &pt){ return ((pt.x == (p.x-1)) && (pt.y == p.y)); });
            
            if (it != points.end()) {
                Point *p_ptr = &(*it);
                p.adj.push_back(p_ptr);
            }
        }
        // add x, y-1
        if ((p.y-1) >= 0) {
            auto it = std::find_if(points.begin(), points.end(), 
                                   [p](const Point &pt){ return ((pt.x == p.x) && (pt.y == (p.y-1))); });
            
            if (it != points.end()) {
                Point *p_ptr = &(*it);
                p.adj.push_back(p_ptr);
            }
        }
        // add x+1, y
        if ((p.x+1) < (grid[0].size())) {
            auto it = std::find_if(points.begin(), points.end(), 
                                   [p](const Point &pt){ return ((pt.x == (p.x+1)) && (pt.y == p.y)); });
            
            if (it != points.end()) {
                Point *p_ptr = &(*it);
                p.adj.push_back(p_ptr);
            }
        }
        // add x, y+1
        if ((p.y+1) < (grid.size())) {
            auto it = std::find_if(points.begin(), points.end(), 
                                   [p](const Point &pt){ return ((pt.x == p.x) && (pt.y == (p.y+1))); });
            
            if (it != points.end()) {
                Point *p_ptr = &(*it);
                p.adj.push_back(p_ptr);
            }
        }
    }

    std::vector<Point> low_points;

    std::cout << "Number points: " << points.size() << std::endl;

    Point test = points[2];
    std::cout << "(" << test.x << "," << test.y << ") - " << test.val << " " << test.adj.size() << std::endl;
    
    for (auto &el: test.adj) {
        std::cout << "(" << (*el).x << "," << (*el).y << ") - " << (*el).val << std::endl;
    }

    for (auto &el: points) {
        int c = 0;
        for (auto &a: el.adj) {
            if ((*a).val <= el.val) {
                c++;
            }
        }
        if (c == 0) {
            low_points.push_back(el);
        }
    }

    std::cout << "Number of low points: " << low_points.size() << std::endl;

    std::cout << "Low Points: " << std::endl;
    int result = 0;
    for (const auto &el: low_points) {
        std::cout << el.val << " -> ";
        for (const auto &a: el.adj) {
            std::cout << (*a).val << " ";
        }
        std::cout << std::endl;
        result += (el.val + 1);
    }
    std::cout << "========== PART 1 ===========" << std::endl;

    std::cout << result << std::endl;

    std::cout << "========== PART 2 ===========" << std::endl;

    
    std::vector<int> basins;

    for (auto &el: low_points) {
        std::queue<Point> pts;
        int count = 0;
        pts.push(el);

        std::cout << "Check: " << el.val << std::endl;

        while (!pts.empty()) {
            Point pt = pts.front();
            pts.pop();
            for (auto &u : pt.adj) {
                if ((*u).visited || (*u).val == 9) continue;
                (*u).visited = true;
                count++;
                pts.push((*u));
            }
        }
        std::cout << "Point (" << el.x << "," << el.y << ") - " << el.val << " - count: " << count << std::endl;
        basins.push_back(count);
    }

    std::sort(basins.rbegin(), basins.rend());
    int res = 1;
    for (size_t i = 0; i < 3; i++) {
        res *= basins[i];
    }
    std::cout << "Result: " << res << std::endl;
    
}