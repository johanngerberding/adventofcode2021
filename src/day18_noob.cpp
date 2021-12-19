// my implementation that doesn't work :D 

#include <bits/stdc++.h>


std::string add(std::string lhs, std::string rhs) {
    std::string res = '[' + lhs + ',' + rhs + ']';
    return res;
}



std::string reduce(const std::string &line)
{   
    std::string separators (",[]");
    bool done = false;
    std::string line_copy = line;
    
    while (!done) {
        int balance = 0;
        
        bool explode = false;
        bool split = false;

        for (size_t i = 0; i < line_copy.size(); i++) {
            char c = line_copy[i];
            
            if (c == '[') {
                balance++;
            } else if (c == ']') {
                balance--;
            }

            if (balance > 4) {
                explode = true;
                std::cout << "------------------- EXPLODE -----------------" << '\n';
                std::cout << line_copy << '\n';
                // find the first closer after 5th opener
                size_t closer = line_copy.find_first_of(']', i);
                std::string tmp = line_copy.substr( i, closer - i);
                size_t opener = tmp.find_last_of('[');
                tmp = tmp.substr(opener+1, closer - opener-1);
                //std::cout << tmp << '\n';
                size_t sep = tmp.find(',');
                int x = std::stoi(tmp.substr(0, sep));
                int y = std::stoi(tmp.substr(sep+1));
                std::cout << "x=" << x << '\n';
                std::cout << "y=" << y << '\n';
                // find commas to left and right 

                std::string left = line_copy.substr(0, i);
                std::cout << "left_str=" << left << '\n';
                std::string right = line_copy.substr(closer+1);
                std::cout << "right_str=" << right << '\n';

                size_t left_num_pos = left.find_last_not_of(separators);
                std::string n_left;
                if (left_num_pos != std::string::npos) {
                    size_t left_num_closer = left.find_first_of(separators, left_num_pos);
                    int left_num = std::stoi(left.substr(left_num_pos, left_num_closer-left_num_pos));
                    std::cout << "left_num=" << left_num << '\n';
                    left_num += x;
                    std::string new_left_num = std::to_string(left_num);
                    n_left = left.substr(0, left_num_pos) + new_left_num + left.substr(left_num_closer);
                    std::cout << "n_left=" << n_left << '\n';
                } else {
                    n_left = left;
                }
                
                size_t right_num_pos = right.find_first_not_of(separators);
                std::string n_right;
                if (right_num_pos != std::string::npos) {
                    size_t right_num_closer = right.find_first_of(separators, right_num_pos);
                    int right_num = std::stoi(right.substr(right_num_pos, right_num_closer-right_num_pos));
                    std::cout << "right_num=" << right_num << '\n';
                    right_num += y;
                    std::string new_right_num = std::to_string(right_num);
                    n_right = right.substr(0, right_num_pos) + new_right_num + right.substr(right_num_closer);
                    std::cout << "n_right=" << n_right << '\n';
                } else {
                    n_right = right;
                }
                
                std::string new_line = n_left + '0' + n_right;
                line_copy = new_line;
                std::cout << line_copy << '\n';
                std::cout << "-------------------------------------------------" << '\n';
                break;
            }
        }
        if (explode) {
            continue;
        }

        for (size_t j = 0; j < line_copy.size(); j++) {
            char c = line_copy[j];
        
            // split stuff 
            if (separators.find(c) == std::string::npos) {
                
                size_t next_separator = line_copy.find_first_of(separators, j);
                std::string tmp = line_copy.substr(j, next_separator - j);
                //std::cout << tmp << '\n';
                int num = std::stoi(tmp);
                std::string new_line;
                if (num > 9) {
                    split = true;
                    std::cout << "--------------- SPLIT -----------------" << '\n'; 
                    std::cout << line_copy << '\n';
                    std::string left = line_copy.substr(0, j);
                    std::string right = line_copy.substr(next_separator);
                    std::cout << "left=" << left << '\n';
                    std::cout << "right=" << right << '\n';
                    std::string n_num;
                    if (num % 2 == 0) {
                        int div = num / 2;
                        std::string d = std::to_string(div);
                        n_num = '[' + d + ',' + d + ']';
                    } else {
                        int div1 = num / 2;
                        int div2 = div1 + 1;
                        std::string d1 = std::to_string(div1);
                        std::string d2 = std::to_string(div2);
                        n_num = '[' + d1 + ',' + d2 + ']';
                    }
                    new_line = left + n_num + right;
                    std::cout << new_line << '\n';
                    std::cout << "--------------- ----- -----------------" << '\n'; 
                    line_copy = new_line;
                    break;
                }
            } 
        }

        if (split) {
            continue;
        }

        done = true;        
        std::cout << line_copy << '\n';
        std::cout << "--------------------------------" << '\n';
        
    }
    return line_copy;
}

long calcMagnitude(std::string &line) {
    long magnitude = 0;
    std::string copyline = line;
    bool done = false;

    while(!done) {

        std::string separators (",[]");
        size_t closer = copyline.find(']');
        std::string tmp = copyline.substr(0, closer);
        size_t opener = tmp.find_last_of('[');

        std::string left = copyline.substr(0, opener);
        std::string right = copyline.substr(closer+1);
        //std::cout << "left=" << left << '\n';
        //std::cout << "right=" << right << '\n';
        //std::cout << tmp << '\n';
        tmp = tmp.substr(opener+1);
        //std::cout << tmp << '\n';
        size_t sep = tmp.find(',');
        long x = std::stol(tmp.substr(0, sep));
        long y = std::stol(tmp.substr(sep+1));
        x *= 3;
        y *= 2;
        long res = x + y;
        magnitude = res;
        std::string resstr = std::to_string(res);

        copyline = left + resstr + right;
        //std::cout << copyline << '\n';

        if ((left.size() == 0) && (right.size() == 0)) {
            done = true;
        }

    }

    std::cout << "Magnitude=" << magnitude << '\n';
    return magnitude;

}



int main() {

    std::ifstream infile("../inputs/day18.txt");
    std::string line1;
    std::string line2;
    std::string result_add;
    std::string result_red;
    long magnitude;

    std::getline(infile, line1);
    while (std::getline(infile, line2)) {
        std::cout << "-----------------" << '\n';
        std::string line1_r = reduce(line1);
        std::string line2_r = reduce(line2);
        std::cout << "  " << line1_r << '\n';
        std::cout << "+ " << line2_r << '\n';
        result_add = add(line1_r, line2_r);
        result_red = reduce(result_add);
        std::cout << "= " << result_red << '\n';
        line1 = result_red; 
    }
    magnitude = calcMagnitude(line1);

    
    return 0;
}