#include <bits/stdc++.h>


class Line {
private:
    int x1;
    int y1;
    int x2;
    int y2;

public:
    Line (){}
    void drawOnGrid(std::vector<std::vector<int>> &grid) const {
        if (x1 == x2) {
            // vertical line 
            int min_y = std::min(y1, y2);
            int max_y = std::max(y1, y2);
            for (int i = min_y; i <= max_y; i++) {
                grid[x1][i]++;
            }
        } else if (y1 == y2) {
            // horizontal line 
            int min_x = std::min(x1,x2);
            int max_x = std::max(x1,x2);
            for (int i = min_x; i <= max_x; i++) {
                grid[i][y1]++;
            }
        } else if (std::abs((x2 - x1)) == std::abs((y2 - y1))) {
            // diagonal 
            int steps = std::abs((x2 - x1));
            if ((x1 <= x2) && (y1 <= y2)) {
                // from left go up
                for (int i = 0; i <= steps; i++) {
                    grid[x1+i][y1+i]++;
                }
            } else if ((x1 <= x2) && (y1 >= y2)) {
                // from left to right down
                for (int i = 0; i <= steps; i++) {
                    grid[x1+i][y1-i]++;
                }
            } else if ((x1 >= x2) && (y1 <= y2)) {
                // from right to left go up 
                for (int i = 0; i <= steps; i++) {
                    grid[x1-i][y1+i]++;
                }
            } else {
                // from right top down left
                for (int i = 0; i <= steps; i++) {
                    grid[x1-i][y1-i]++;
                }
            }
            
        }
    }
    int get_max_x() { return std::max(x1, x2); }
    int get_max_y() { return std::max(y1, y2); }
    int get_min_x() { return std::min(x1, x2); }
    int get_min_y() { return std::min(y1, y2); }

    void set_x1(int x) { this->x1 = x; }
    void set_y1(int y) { this->y1 = y; }
    void set_x2(int x) { this->x2 = x; }
    void set_y2(int y) { this->y2 = y; }
};


void parse(const std::string &line, Line &l) {
    size_t pos = line.find( ',' );
    size_t initialPos = 0;
    int x1 = std::stoi( line.substr( initialPos, pos - initialPos ) );
    initialPos = pos + 1;
    pos = line.find( ' ' );
    int y1 = std::stoi( line.substr( initialPos, pos - initialPos ) );
    initialPos = pos + 1;
    pos = line.find( ' ', initialPos);
    initialPos = pos + 1;
    pos = line.find( ',' , initialPos);
    int x2 = std::stoi( line.substr( initialPos, pos - initialPos ) );
    initialPos = pos + 1;
    int y2 = std::stoi( line.substr( initialPos ) );

    l.set_x1(x1);
    l.set_y1(y1);
    l.set_x2(x2);
    l.set_y2(y2);
}

/*
bool validateLine(Line &l) {
    if ((l.x1 == l.x2) || (l.y1 == l.y2)) {
        return true;
    } 
    if (std::abs((l.x2 - l.x1)) == std::abs((l.y2 - l.y1)))
        return true;

    return false;
}*/

std::vector<int> getGridCoordinates(const std::vector<Line> &lines) {
    int min_x = 1000;
    int min_y = 1000;
    int max_x = -1;
    int max_y = -1;
    for (auto el: lines) {
        max_x = (el.get_max_x() > max_x) ? el.get_max_x() : max_x;
        min_x = (el.get_min_x() < min_x) ? el.get_min_x() : min_x;
        max_y = (el.get_max_y() > max_y) ? el.get_max_y() : max_y;
        min_y = (el.get_min_y() > min_y) ? el.get_min_y() : min_y;
    }

    std::vector<int> coords {min_x, min_y, max_x, max_y};
    return coords;
}


int main() {
    std::ifstream infile("../inputs/day05.txt");
    std::vector<Line> coordinates;
    std::string line;
    while (std::getline(infile, line)) {
        // parse lines
        //std::cout << line << std::endl;
        Line l; 
        parse(line, l);
        coordinates.push_back(l); 
    }

    infile.close();

    std::vector<int> coords = getGridCoordinates(coordinates);

    std::vector<std::vector<int>> grid (coords[2]+1, std::vector<int>(coords[3]+1));
    
    for (const auto el: coordinates) {
        el.drawOnGrid(grid);
    } 

    int count = 0;
    for (int i = 0; i <= coords[2]; i++) {
        for (int j = 0; j <= coords[3]; j++) {
            if (grid[i][j] >= 2) {
                count++;
            } 
        }
    }

    std::cout << count << std::endl;

}