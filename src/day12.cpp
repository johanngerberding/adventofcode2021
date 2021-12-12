#include <bits/stdc++.h>

bool isUpper(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::isupper(c); });
}

struct Node {
    std::string val;
    std::set<std::string> adj;
    std::string twice;
    Node(std::string v, std::set<std::string> a, std::string t) {
        val = v;
        adj = a;
        twice = t;
    }
};


int main() {
    std::ifstream infile("../inputs/day12.txt");
    std::string line;

    std::map<std::string, std::vector<std::string>> adj_list;

    while (std::getline(infile, line)) {
        size_t pos = line.find('-');
        if (pos != std::string::npos) {
            std::string id1 = line.substr(0, pos);
            std::string id2 = line.substr(pos+1, line.size());

            if (adj_list.find(id1) != adj_list.end()) {
                adj_list[id1].push_back(id2);
            } else {
                std::vector<std::string> temp {id2};
                adj_list.insert(std::make_pair(id1, temp));
            }

            if (adj_list.find(id2) != adj_list.end()) {
                adj_list[id2].push_back(id1);
            } else {
                std::vector<std::string> temp {id1};
                adj_list.insert(std::make_pair(id2, temp));
            }
        }

    }

    for (const auto &p: adj_list) {
        std::cout << p.first << ": ";
        for (auto &n: p.second) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }

    std::deque<Node*> caves; 
    Node* sptr = new Node("start", std::set<std::string> {"start"}, "");
    caves.push_front(sptr);
    long sum = 0;

    bool part2 = true;

    while (!caves.empty()) {
        std::cout << "Deque size: " << caves.size() << std::endl;
        Node* t = caves.front();
        caves.pop_front();
        if (t->val == "end") {
            sum++;
            continue;
        }
        
        for (auto el: adj_list[t->val]) {
            auto it = std::find_if(t->adj.begin(), t->adj.end(), 
                                   [el](std::string s) { return (s == el); });
            if (it == t->adj.end()) {
                std::set<std::string> new_adj;
                for (auto a: t->adj) {
                    new_adj.insert(a);
                }
                if (!isUpper(el)) {
                    new_adj.insert(el);
                }
                Node* nptr = new Node(el, new_adj, t->twice);
                caves.push_back(nptr);

            } else if ((it != t->adj.end()) && part2 && (t->twice == "") && (el != "start") && (el != "end")) {
                Node* nptr = new Node(el, t->adj, el);
                caves.push_back(nptr);
            }
        }
        
    }

    std::cout << sum << std::endl;

    infile.close();
    return 0;
}