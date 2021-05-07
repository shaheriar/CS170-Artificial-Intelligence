#include <iostream>
#include <vector>

using namespace std;

class Node {
    public:
        vector<vector<int>> state;
        Node* parent;
        Node* up;
        Node* down;
        Node* left;
        Node* right;
        int cost, h, totalcost;
        string identity;

        Node(vector<vector<int>> inputstate) {
            cost = 0;
            h = 0;
            totalcost = cost + h;
            state = inputstate;
            parent = nullptr;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
            identity = "ROOT";
        }

        Node(vector<vector<int>> inputstate, Node* parent, string id, int h) {
            state = inputstate;
            this->parent = parent;
            this->h = h;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
            cost = parent->cost + 1;
            totalcost = cost + h;
            identity = id;
        }
};