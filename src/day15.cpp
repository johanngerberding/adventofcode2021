#include <bits/stdc++.h>

struct node {
    int x;
    int y;
    int weight;
    node(int x, int y, int w) {
        this->x = x;
        this->y = y;
        this->weight = w;
    }
    void display() const {
        std::cout << "(" << x << "," << y << ") -> " << weight << std::endl;
    }
};

std::string next_line(const std::string &line) {
    std::vector<int> nums;
    std::string n_line;
    for (auto c: line) {
        int n = c - '0';
        n++;
        if (n > 9) {
            n = 1;
        }
        char n_c = '0' + n;
        n_line.push_back(n_c);
    }
    return n_line;
}


int main() {

    std::ifstream infile("../inputs/day15.txt");
    std::string line;
    
    std::map<node*, std::vector<node*>> adj;
    std::map<node*, bool> processed; 
    std::map<node*, int> distance;
   
    std::vector<std::string> lines;

    // Read input 
    while (std::getline(infile, line)) {
        lines.push_back(line); 
    }

    std::vector<std::string> big_grid;
    // part 2 -> grid expansion
    for (auto line: lines) {
        std::string big_line = line;
        std::string tmp = line;
        for (int i=1; i < 5; i++) {
            std::string n_line = next_line(tmp);
            big_line += n_line;
            tmp = n_line;
        }
        big_grid.push_back(big_line);
    }

    std::vector<std::string> superbig_gird = big_grid;
    std::vector<std::string> tmp = big_grid;
    for (int i=1; i<5; i++) {
        std::vector<std::string> next_big_grid;
        std::vector<std::string> plholder;
        for (auto el: tmp) {
            std::string new_line = next_line(el);
            superbig_gird.push_back(new_line);
            next_big_grid.push_back(new_line);
        }
        tmp = next_big_grid;
        next_big_grid = plholder;
    }

    std::cout << "Superbig grid rows: " << superbig_gird.size() << std::endl;
    std::cout << "Superbig grid cols: " << superbig_gird[0].size() << std::endl;

    for (auto line: superbig_gird) {
        std::cout << line << std::endl;
    }

    std::vector<node*> nodes;
    int row = 0;
    for (auto el: superbig_gird) {
        int col = 0;
        for (auto c: el) {
            int w = c - '0';
            node* n = new node(col, row, w);
            nodes.push_back(n);
            col++;
        }
        row++;
    }

    for (auto el: nodes) {
        std::vector<node*> adj_nodes;
        // upper  
        if (el->y-1 >= 0) {
            auto it = std::find_if(
                nodes.begin(), 
                nodes.end(), 
                [&el](node* np) { 
                    return ((el->x == np->x) && (np->y == el->y-1)); 
                }
            );
            node* nptr = (*it);
            adj_nodes.push_back(nptr);
        }
        // down 
        if (el->y+1 < superbig_gird.size()) {
            auto it = std::find_if(
                nodes.begin(), 
                nodes.end(), 
                [&el](node* np) { 
                    return ((el->x == np->x) && (np->y == el->y+1)); 
                }
            );
            node* nptr = (*it);
            adj_nodes.push_back(nptr);
        }
        // left 
        if (el->x-1 >= 0) {
            auto it = std::find_if(
                nodes.begin(), 
                nodes.end(), 
                [&el](node* np) { 
                    return ((el->x-1 == np->x) && (np->y == el->y)); 
                }
            );
            node* nptr = (*it);
            adj_nodes.push_back(nptr);
        }
        // right 
        if (el->x + 1 < superbig_gird[0].size()) {
            auto it = std::find_if(
                nodes.begin(), 
                nodes.end(), 
                [&el](node* np) { 
                    return ((el->x+1 == np->x) && (np->y == el->y)); 
                }
            );
            node* nptr = (*it);
            adj_nodes.push_back(nptr);
        }
        adj.insert(std::make_pair(el, adj_nodes));
    }

    std::cout << "Size of adjancency list: " << adj.size() << std::endl;

    // all distances are INF
    for (auto &el: adj) {
        distance.insert(std::make_pair(el.first, std::numeric_limits<int>::max()));
    }

    auto itr_start = std::find_if(
        nodes.begin(), 
        nodes.end(), 
        [](node* n) { return ((n->x == 0) && (n->y == 0)); }
    );
    node* start = (*itr_start);
    std::cout << "Start node -> (" << start->x << "," << start->y << ")" << std::endl;
    distance[start] = 0;

    auto comp = [&distance](node* n1, node* n2) { return distance[n1] > distance[n2]; };

    std::priority_queue<node*, std::vector<node*>, decltype( comp )> temp( comp );
    temp.push(start);

    while (!temp.empty()) {
        node* n = temp.top();
        temp.pop();
        if (processed[n]) continue;
        processed[n] = true;
        for (auto &el : adj[n]) {
            int w = el->weight;
            if (distance[n] + w < distance[el]) {
                distance[el] = distance[n] + w;
                temp.push(el);
            }
        }
    }

    auto itr_end = std::find_if(
        nodes.begin(), 
        nodes.end(), 
        [&superbig_gird](node* n) { 
            return ((n->x == superbig_gird[0].size()-1) && (n->y == superbig_gird.size()-1)); 
        }
    );
    node* end = (*itr_end);
    std::cout << "End node -> (" << end->x << "," << end->y << ")" << std::endl;
    int result = distance[end];

    std::cout << "Result: " << result << std::endl;
    
    
    infile.close();
    return 0;
}