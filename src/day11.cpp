#include <bits/stdc++.h>


struct Octopus {
    int val;
    int x;
    int y;
    bool visited;
    std::vector<Octopus*> adj;
    void display() const {
        std::cout << "(" << x << "," << y << ") - " << val << " - " << adj.size() << std::endl; 
    }
};


int main() {

    std::ifstream infile("../inputs/day11.txt");
    std::string line;
    std::vector<Octopus> dumbos;
    int max_row = 0;
    int max_col = 0;
    int row = 0;
    while (std::getline(infile, line)) {
        int col = 0;
        for (const auto c: line) {
            int val = c - '0';
            Octopus o {val, col, row, false, {}};
            dumbos.push_back(o);
            col++;
            max_col = col > max_col ? col : max_col;
        }
        row++;
        max_row = row > max_row ? row : max_row;
    }

    // add adjacent Octopusses
    for (auto &el: dumbos) {
        // left 
        if (el.x > 0) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.x-1 == o.x) && (el.y == o.y));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // right 
        if (el.x < (max_col-1)) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.x+1 == o.x) && (el.y == o.y));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // upper 
        if (el.y > 0) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.y-1 == o.y) && (el.x == o.x));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // lower 
        if (el.y < (max_row-1)) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.y+1 == o.y) && (el.x == o.x));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // left up
        if ((el.x > 0) && (el.y > 0)) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.y-1 == o.y) && (el.x-1 == o.x));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // left down
        if ((el.x > 0) && (el.y < (max_row-1))) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.y+1 == o.y) && (el.x-1 == o.x));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // right up
        if ((el.x < (max_col-1)) && (el.y > 0)) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.y-1 == o.y) && (el.x+1 == o.x));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
        // right down
        if ((el.x < (max_col-1)) && (el.y < (max_row-1))) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                [el](Octopus &o){ return ((el.y+1 == o.y) && (el.x+1 == o.x));});
            if (it != dumbos.end()) {
                Octopus * ptr = &(*it);
                el.adj.push_back(ptr);
            }
        }
    }

    int flashes = 0;
    for (int i = 0; i < 100000; i++) {
        // step
        int fl = 0;
        std::cout << "Round " << i << " - " << flashes << std::endl;
        for (auto &el: dumbos) {
            el.val++;
            el.visited = false;
        }

        while(true) {
            auto it = std::find_if(dumbos.begin(), dumbos.end(), 
                                   [](Octopus &o){ return ((o.val > 9) && (o.visited == false)); });
            if (it == dumbos.end()) {
                break;
            }
            Octopus* o = &(*it);
            o->visited = true;

            for (auto &a: o->adj) {
                if ((*a).visited == false) {
                    (*a).val++;
                }
            }
        }
        for (auto &el: dumbos) {
            if (el.val > 9) {
                el.val = 0;
                flashes++;
                fl++;
            }
        }
        if (fl == dumbos.size()) {
            std::cout << "All flash: " << i+1 << std::endl;
            break;
        }
    }

    std::cout << "Flashes: " << flashes << std::endl;
    
}