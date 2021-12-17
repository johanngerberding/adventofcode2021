#include <bits/stdc++.h>

class Probe {
public:
    int x;
    int y;
    int x_v;
    int y_v;
    int steps;
    std::vector<int> targetArea;
    std::vector<int> trajectory;

    Probe() {
        x = 0;
        y = 0;
        x_v = 0;
        y_v = 0;
        steps = 0;
        targetArea = {}; 
        trajectory = {0};    
    }

    void step() {
        steps++;
        x += x_v;
        y += y_v;
        trajectory.push_back(y);
        // drag
        if (x_v > 0) {
            x_v--;
        } else if (x_v < 0) {
            x_v++;
        }
        // gravity
        y_v--;
    }

    bool inTargetArea() const {
        if ((x >= targetArea[0]) && 
            (x <= targetArea[1]) && 
            (y >= targetArea[2] ) && 
            (y <= targetArea[3])) {
            return true;
        }
        return false;
    }

    bool terminate() const {
        if (inTargetArea())
            return true;

        if (steps > 1000) 
            return true;
        //int x_v_abs = std::abs(x_v);
        //int max_tA_x = std::max(std::abs(targetArea[0]), std::abs(targetArea[1]));
        
        if ((targetArea[1] > 0) && (targetArea[0] >= 0)) {
            if (x_v >= 0) {
               if (x > targetArea[1]) {
                   return true;
               } 
            }
        } else if ((targetArea[0] < 0) && (targetArea[1] <= 0)) {
            if (x_v <= 0) {
                if (x < targetArea[0]) {
                    return true;
                }
            }
        }

        if ((targetArea[2] >= 0) && (targetArea[3] > 0)) {
            if (y_v <= 0) {
                if (y < targetArea[2]) {
                    return true;
                }
            }
        } else if ((targetArea[2] < 0) && (targetArea[3] <= 0)) {
            if (y_v <= 0) {
                if (y < targetArea[2]) {
                    return true;
                }
            }
        }
        
        return false;
    }

};

std::vector<int> parseTargetArea(std::string tgt)
{
    std::vector<int> targetArea;
    int x_min, x_max, y_min, y_max;

    size_t pos1 = tgt.find('=');
    size_t pos2 = tgt.find('.', pos1);
    std::string xmin = tgt.substr(pos1+1, pos2-pos1-1);
    x_min = std::stoi(xmin);
    pos1 = tgt.find('.', pos2+1);
    pos2 = tgt.find(',', pos1+1);
    std::string xmax = tgt.substr(pos1+1, pos2-pos1-1);
    x_max = std::stoi(xmax);

    pos1 = tgt.find('=', pos2+1);
    pos2 = tgt.find('.', pos1+1);
    std::string ymin = tgt.substr(pos1+1, pos2-pos1-1);
    y_min = std::stoi(ymin);
    pos1 = tgt.find('.', pos2+1);
    std::string ymax = tgt.substr(pos1+1);
    y_max = std::stoi(ymax);
    
    targetArea.push_back(x_min);
    targetArea.push_back(x_max);
    targetArea.push_back(y_min);
    targetArea.push_back(y_max);
    
    return targetArea;
}


int main() {

    std::ifstream infile("../inputs/day17.txt");
    std::string target;
    std::getline(infile, target);

    std::vector<int> targetArea = parseTargetArea(target);

    for (auto el: targetArea) {
        std::cout << el << std::endl;
    }

    // Search space for solutions
    // x_v_max -> zero to x_max if x_min && x_max > 0
    //         -> zero to -x_max if x_min && x_max < 0
    //         -> between -x_min and x_max 

    // y_v_min -> if y_min 
    
    int x_v_max;
    int x_v_min;
    int y_v_min = -100;
    int y_v_max = 100;

    if ((targetArea[0] >= 0) && (targetArea[1] > 0)) {
        x_v_max = targetArea[1];
        x_v_min = 1;
    } else if ((targetArea[0] < 0) && (targetArea[1] <= 0)) {
        x_v_min = targetArea[0];
        x_v_max = -1;
    } else if ((targetArea[0] < 0) && (targetArea[1] > 0)) {
        x_v_min = targetArea[0];
        x_v_max = targetArea[1];
    }


    int max_y = -100000;
    Probe* p = new Probe();
    p->targetArea = targetArea;
    for (int x = x_v_min; x <= x_v_max; x++) {
        for (int y = y_v_min; y <= y_v_max; y++) {
            std::cout << "Test (" << x << "," << y << ")" << std::endl;
            p->x = 0;
            p->y = 0;
            p->steps = 0;
            p->x_v = x;
            p->y_v = y;
            p->trajectory = {0};
            while(true) {
                p->step();
                if (p->terminate()) {
                    if (p->inTargetArea()) {
                        auto it = std::max_element(p->trajectory.begin(), p->trajectory.end());
                        if ((*it) > max_y) {
                            max_y = (*it);
                        }
                    }
                    break;
                }
            }
        }
    }

    std::cout << "max y = " << max_y << std::endl;

    return 0;
}