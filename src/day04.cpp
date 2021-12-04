#include <bits/stdc++.h>
#include <regex>

size_t split(const std::string &txt, std::vector<int> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();
    std::string temp;
    
    // Decompose statement
    while( pos != std::string::npos ) {
        temp = txt.substr( initialPos, pos - initialPos );
        strs.push_back( std::stoi(temp) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    temp = txt.substr( initialPos, std::min( pos, txt.size()) - initialPos + 1 );
    strs.push_back( std::stoi(temp) );

    return strs.size();
}


int main() {

    std::ifstream infile("../inputs/day04.txt");
    std::string numbers;
    std::getline(infile, numbers);

    std::vector<int> bingo_numbers;
    split(numbers, bingo_numbers, ',');
    
    std::string bingo_line;
    std::vector<std::string> lines;
    while(getline(infile, bingo_line)) {
        if (!bingo_line.empty())
            lines.push_back(bingo_line);
    }
    int num_grids = lines.size() / 5;
    assert(lines.size() % 5 == 0);
    
    // create grids
    //std::vector<std::vector<std::vector<int>>> grids;
    int grids[num_grids][5][5];
    std::vector<int> row;
    std::string line;
    for (int i = 0; i < num_grids; i++) {
        for (int j = 0; j < 5; j++) {
            line = lines[i*5+j];
            line = std::regex_replace(line, std::regex("  "), " ");
            if (line[0] == ' ') {
                line.erase(0,1);
            }
            split(line, row, ' ');
            for (size_t k = 0; k < row.size(); k++) {
                grids[i][j][k] = row[k];
            }
        }
    }

    bool winner = false;
    //int winner_num;
    //int winner_player;
    int last_winner;
    std::set<int> winner_players;
    int last_winner_num;

    for (auto el: bingo_numbers){
        for (int i = 0; i < num_grids; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    if (grids[i][j][k] == el) {
                        grids[i][j][k] = -1;
                    }
                }
                
            }
        }
        // calc row and col sums 
        for (int i = 0; i < num_grids; i++) {
            for (int j = 0; j < 5; j++) {
                int row_sum = 0;
                int col_sum = 0;
                for (int k = 0; k < 5; k++) {
                    row_sum = row_sum + grids[i][j][k];
                    col_sum = col_sum + grids[i][k][j];
                }
                if ((row_sum == -5) || (col_sum == -5)) {
                    winner_players.insert(i);
                    if (winner_players.size() == num_grids) {
                        last_winner = i;
                        winner = true;
                        break;
                    }
                    //winner = true;
                    //winner_player = i;
                    //break;

                }
                
            }
            if (winner) {
                break;
            }
        }
        if (winner) {
            last_winner_num = el;
            break;
        }
    }

    std::cout << "Winner player: " << last_winner << std::endl;
    std::cout << "Winner num: " << last_winner_num << std::endl;

    int winner_sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grids[last_winner][i][j] != -1) {
                winner_sum = winner_sum + grids[last_winner][i][j];
            }
        }
    }

    int result = last_winner_num * winner_sum;
    std::cout << result << std::endl;

}