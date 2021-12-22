#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <array>
#include <bitset>
#include <algorithm>


struct Point {
    int x;
    int y;
};


constexpr std::array<Point, 9> window = {
    Point{-1,-1}, Point{0,-1}, Point{1,-1},
    Point{-1,0}, Point{0,0}, Point{1,0},
    Point{-1,1}, Point{0,1}, Point{1,1}
};


struct Image {
    std::vector<bool> pixels;
    bool background;
    int size;
    
    void display() const {
        std::cout << "Image\n" << "size: " << size << '\n'; 
    }
    
    void display_pixels() const {
        for (int i = 0; i < size * size; i++) {
            int col = i % size;
            int row = i / size;
            std::cout << pixels.at(col + row * size);
            if (col == size-1)
                std::cout << '\n';
        }
    }

    bool operator[](Point const& p) const  {
        if (p.x >= 0 && p.x < size && p.y >= 0 && p.y < size) {
            return pixels.at(p.x + p.y * size);
        } else {
            return background;
        }
    }
};

Image enhance(std::bitset<512> const& enhancement, Image const& img) {
    Image n_img;
    n_img.size = img.size + 2;
    n_img.background = img.background ? enhancement.test(511) : enhancement.test(0);
    //n_img.pixels.reserve(n_img.size * n_img.size);
    n_img.pixels = {};
    for (int i = 0; i < n_img.size * n_img.size; i++) {
        n_img.pixels.push_back(false);
    } 

    int new_size = n_img.size * n_img.size;
    for (int i = 0; i < new_size; i++) {
        int col = i % n_img.size;
        int row = i / n_img.size;
        Point p {col-1, row-1};
        std::string win;
        for (auto const &el : window) {
            Point a {p.x + el.x, p.y + el.y};
             
            bool old_val = img[a]; 
            
            if (old_val) {
                win.push_back('1');
            } else {
                win.push_back('0');    
            }
        }

        assert (win.size() == 9);
        int dec = std::stoi(win, nullptr, 2);
        bool val = enhancement.test(dec);
        
        n_img.pixels[col + row * n_img.size] = val;
    }

    return n_img;    
}

Image parse (std::ifstream &infile) {
    Image img;
    std::string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            img.size = line.size();
            for (int i=0; i < img.size; i++) {
                if (line.at(i) == '.') {
                    img.pixels.push_back(false);
                } else if (line.at(i) == '#') {
                    img.pixels.push_back(true);
                }
            }
        }
    }

    return img;
}


int main() {
    std::ifstream infile("../inputs/day20.txt");
    std::string line;
    getline(infile, line);
    std::bitset<512> enhancement;
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == '#') {
            enhancement.set(i, true);
        }
    }
    
    Image img = parse(infile);
    
    for (int i = 0; i < 50; i++) {
        Image n_img = enhance(enhancement, img);
        if (i == 1 || i == 49) {
            auto count = std::count(n_img.pixels.begin(), n_img.pixels.end(), true);
            std::cout << "Count [" << i+1 << "] -> " << count << '\n';
        }
        img = n_img;
    }

    infile.close();
    return 0;
}
