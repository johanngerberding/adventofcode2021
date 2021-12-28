#include <iostream>
#include <stack>
#include <vector>
#include <optional>


// represents rooms + hallway
class Room {
public:
    char type;
    std::vector<char> roomates;
    std::optional<std::vector<int>> invalid_pos;

    Room (char t, std::vector<char> mates) {
        type = t;
        roomates = mates;
        if (t == 'H') {
            invalid_pos = {2,4,6,8};
        }
    }

    bool finished() {
        for (auto el: roomates) {
            if (el != type) {
                return false;
            }
        }
        return true;
    }
};


// represents the current playboard state
class Board {
public:
    std::vector<Room> rooms;
    uint64_t cost;

    Board () {
        cost = 0;
        rooms = {};
    }
    
    bool board_finished() {
        for (auto &el: rooms) {
            if (!el.finished()) {
                return false;
            }
        }
        return true;
    }
    
    // get valid moves -> what can be done 
    // based on the actual state of the board
    // how to represent moves? -> new vector of rooms?
    // --> sequence of room vectors including the costs
    // monte-carlo tree search? 
    


};

// INPUT
// #############
// #...........#
// ###B#A#B#C###
//   #D#A#D#C#
//   #########

int main() {

    Board* b = new Board();
    b->rooms.push_back(Room('H', {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}));
    b->rooms.push_back(Room('A', {'D', 'B'}));
    b->rooms.push_back(Room('B', {'A', 'A'}));
    b->rooms.push_back(Room('C', {'D', 'B'}));
    b->rooms.push_back(Room('D', {'C', 'C'}));

    return 0;
}
