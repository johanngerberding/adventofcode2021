#include <bits/stdc++.h>

struct Point {
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void display() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    std::ifstream infile("../inputs/day13.txt");
    std::string line;

    std::vector<std::unique_ptr<Point>> grid;
    std::vector<std::pair<char, int>> folds;

    while(std::getline(infile, line)) {
        if ((line != "") && (line.rfind("fold", 0) != 0)) {
            int init_pos = 0;
            size_t pos = line.find(',');
            int x = std::stoi(line.substr(init_pos, pos));
            int y = std::stoi(line.substr(pos+1, line.size()));
            
            grid.push_back(std::make_unique<Point>(x,y));
        } else if ((line != "") && (line.rfind("fold", 0) == 0)) {
            int init_pos = 11;
            size_t pos = line.find('=');
            char axis = (line.substr(init_pos, init_pos+1))[0];
            int num = std::stoi(line.substr(pos+1, line.size()));
            folds.push_back(std::make_pair(axis, num));
        }
    }

    int c = 0;
    for(auto &el: folds) {
        c++;

        grid.erase(std::remove_if(grid.begin(), grid.end(), 
                   [&el](auto const& ptr){
                       if (el.first == 'y') {
                           return (el.second == ptr->y);
                       } else {
                           return (el.second == ptr->x);
                       }
                   }), grid.end());
    
        if (el.first == 'y') {
            // only change y's
            for (int i = 1; i <= el.second; i++) {
                int before = el.second + i;
                int after = el.second - i;
                for (auto &p : grid) {
                    if (p->y == before) {
                        (*p).y = after;
                    }
                }
            }
        } else if (el.first == 'x') {
            for (int i = 1; i <= el.second; i++) {
                int before = el.second + i;
                int after = el.second - i;
                for (auto &p : grid) {
                    if (p->x == before) {
                        (*p).x = after;
                    }
                }
            }
        }

        //if (c == 1) {
           // break;
        //}
    }

    std::vector<std::unique_ptr<Point>> ngrid;
    int max_x = 0;
    int max_y = 0;

    for (auto &el: grid) {
        auto itr = std::find_if(
            ngrid.begin(), 
            ngrid.end(), 
            [&el](auto &p) { 
                return ((p->x == el->x) && (p->y == el->y)); 
            }
        );
        if (itr == ngrid.end()) {
            int x = el->x;
            int y = el->y;
            max_x = (x > max_x) ? x : max_x;
            max_y = (y > max_y) ? y : max_y;
            ngrid.push_back(std::make_unique<Point>(x,y));
        }
    }

    std::cout << ngrid.size() << std::endl;
    std::cout << max_x << std::endl;
    std::cout << max_y << std::endl;

    char arr[max_y+1][max_x+1];

    for (int i=0; i <= max_y; i++) {
        for (int j=0; j <= max_x; j++) {
            arr[i][j] = '.';
        }
    }

    for (auto &el: ngrid) {
        arr[el->y][el->x] = '#';
    }

    for (int i=0; i <= max_y; i++) {
        for (int j=0; j <= max_x; j++) {
            std::cout << arr[i][j]; 
        }
        std::cout << std::endl;
    }

    infile.close();
    return 0;
}