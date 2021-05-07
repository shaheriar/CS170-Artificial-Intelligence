#include <iostream>
#include <string>
#include "Problem.cpp"
#include "Node.cpp"
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <math.h>

using namespace std;

class Search {
    public:
        //FOR PRIORITY QUEUE TO BE ABLE TO COMPARE TWO NODES
        struct TotalCostCompare {
            bool operator() (Node* n1, Node* n2) {
                return (n1->totalcost > n2->totalcost);
            }
        };

        //COMPUTING H(N) FOR MISPLACED
        int CalculateMisplaced(vector<vector<int>> state, vector<vector<int>> goal_state) {
            int h = 0;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    //increments h by 1 when a node of the current state != node of goal state
                    if (state[i][j] != goal_state[i][j]){
                        h += 1;
                    }
                }
            }
            return h;
        }

        //COMPUTING H(N) FOR EUCLIDIAN
        int CalculateEuclidian(vector<vector<int>> state) {
            int h = 0;
            for (int i = 0; i < state.size(); i++) {
                for (int j = 0; j < state.size(); j++) {

                    //EUCLIDEAN HEURISTIC IS CALCULATED USING PYTHAGOREAN: H = (DX^2 + DY^2)^0.5
                    switch(state[i][j]) {
                        case 1: h += sqrt(pow(i-0, 2) + pow(j-0, 2)); break;
                        case 2: h += sqrt(pow(i-0, 2) + pow(j-1, 2)); break;
                        case 3: h += sqrt(pow(i-0, 2) + pow(j-2, 2)); break;
                        case 4: h += sqrt(pow(i-1, 2) + pow(j-0, 2)); break;
                        case 5: h += sqrt(pow(i-1, 2) + pow(j-1, 2)); break;
                        case 6: h += sqrt(pow(i-1, 2) + pow(j-2, 2)); break;
                        case 7: h += sqrt(pow(i-2, 2) + pow(j-0, 2)); break;
                        case 8: h += sqrt(pow(i-2, 2) + pow(j-1, 2)); break;
                        case 0: h += sqrt(pow(i-2, 2) + pow(j-2, 2)); break;
                        default: break;
                    }

                }
            }
            return h;
        }

        //HELPER FUNCTION THAT PRINTS A VECTOR
        void print(vector<vector<int>> state) {
            if (state.size() > 0) {
                cout << "-----------------------------" << endl;
                for (int i = 0; i < state.size(); i++) {
                    for (int j = 0; j < state.size(); j++) {
                        cout << state[i][j] << ' ';
                    }
                    cout << endl;
                }
            }
        }

        //EXTRA CREDIT BACKTRACKING ALGORITHM
        void backtrack(Node* curr) {
            stack<Node*> stack;
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->parent;
            }
            int i = 0;
            while (!stack.empty()) {
                cout << "STEP " << i << endl;
                print(stack.top()->state);
                cout << stack.top()->identity << endl;
                cout << "-----------------------------" << endl;
                stack.pop();
                i++;
            }
        }

        //UNIFORM COST SEARCH ALGORITHM
        bool uniformCostSearch(Problem p) {

            //MAP TO KEEP TRACK OF VISITED NODES
            map<vector<vector<int>>, bool> visited;

            //IF THE ROOT IS THE ANSWER THEN DON'T WASTE TIME FINDING THE SOLUTION
            Node* root = new Node(p.initial_state);
            if (root->state == p.goal_state) {
                cout << "SUCCESS" << endl;
                cout << "FOUND SUCCESS AFTER EXPANDING " << root->totalcost << " NODES" << endl;
                cout << "TOTAL NODES EXPLORED: 0" << endl;
                return true;
            }
            
            cout << "-----------------------------" << endl;
            cout << "PRINTING INITIAL STATE" << endl;
            print(root->state);
            cout << "-----------------------------" << endl;

            //PRIORITY QUEUE FOR NODES TO VISIT
            priority_queue<Node*, vector<Node*>, TotalCostCompare> pq;

            //NODES AFTER OPERATIONS
            Node* up = new Node(p.up(root->state), root, "UP", 0);
            Node* down = new Node(p.down(root->state), root, "DOWN", 0);
            Node* left = new Node(p.left(root->state), root, "LEFT", 0);
            Node* right = new Node(p.right(root->state), root, "RIGHT", 0);

            //ASSIGNING CHILDREN
            root->up = up;
            root->down = down;
            root->left = left;
            root->right = right;

            //MARKING THEM AS VISITED
            visited[up->state] = true;
            visited[down->state] = true;
            visited[left->state] = true;
            visited[right->state] = true;

            //PUT THESE NODES IN PRIORITY QUEUE
            pq.push(up);
            pq.push(down);
            pq.push(left);
            pq.push(right);

            Node* curr;
            int count = 0;
            unsigned size = 0;

            while (!pq.empty()) {
                curr = pq.top();

                //GETTING THE MAX SIZE OF PQ
                size = (pq.size() > size) ? pq.size() : size;
                
                cout << "The best state to expand with f(n) = " << curr->totalcost << ", g(n) = " << curr->cost << " and h(n) = " << curr->h << " is " << endl;
                print(curr->state);
                cout << "Expanding this node..." << endl;
                cout << "-----------------------------" << endl;
                
                count++;
                if (curr->state == p.goal_state) {
                    cout << "SUCCESS" << endl;
                    backtrack(curr);
                    cout << "FOUND SUCCESS WITH TOTAL COST: " << curr->totalcost << endl;
                    cout << "TOTAL NODES EXPANDED: " << count << endl;
                    cout << "MAXIMUM PRIORITY QUEUE SIZE: " << size << endl;
                    return true;
                }

                pq.pop();

                //FOR UP
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.up(curr->state))) {
                    Node* up = new Node(p.up(curr->state), curr, "UP", 0);
                    curr->up = up;
                    visited[up->state] = true;
                    pq.push(up);
                }

                //FOR DOWN
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.down(curr->state))) {
                    Node* down = new Node(p.down(curr->state), curr, "DOWN", 0);
                    curr->down = down;
                    visited[down->state] = true;
                    pq.push(down);
                }

                //FOR LEFT
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.left(curr->state))) {
                    Node* left = new Node(p.left(curr->state), curr, "LEFT", 0);
                    curr->left = left;
                    visited[left->state] = true;
                    pq.push(left);
                }

                //FOR RIGHT
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.right(curr->state))) {
                    Node* right = new Node(p.right(curr->state), curr, "RIGHT", 0);
                    curr->right = right;
                    visited[right->state] = true;
                    pq.push(right);
                }
            }
            cout << "FAILED AFTER EXPANDING " << count << " NODES" << endl;
            cout << "MAXIMUM PRIORITY QUEUE SIZE: " << size << endl;
            return false;
        }

        //TODO
        //A* with the Misplaced Tile heuristic
        bool AStarMisplaced(Problem p) {
            
            //MAP TO KEEP TRACK OF VISITED NODES
            map<vector<vector<int>>, bool> visited;

            //IF THE ROOT IS THE ANSWER THEN DON'T WASTE TIME FINDING THE SOLUTION
            Node* root = new Node(p.initial_state);
            if (root->state == p.goal_state) {
                cout << "SUCCESS" << endl;
                cout << "FOUND SUCCESS AFTER EXPANDING " << root->totalcost << " NODES" << endl;
                cout << "TOTAL NODES EXPLORED: 0" << endl;
                return true;
            }
            
            cout << "-----------------------------" << endl;
            cout << "PRINTING INITIAL STATE" << endl;
            print(root->state);
            cout << "-----------------------------" << endl;

            //PRIORITY QUEUE FOR NODES TO VISIT
            priority_queue<Node*, vector<Node*>, TotalCostCompare> pq;

            //NODES AFTER OPERATIONS
            Node* up = new Node(p.up(root->state), root, "UP", CalculateMisplaced(p.up(root->state), p.goal_state));
            Node* down = new Node(p.down(root->state), root, "DOWN", CalculateMisplaced(p.down(root->state), p.goal_state));
            Node* left = new Node(p.left(root->state), root, "LEFT", CalculateMisplaced(p.left(root->state), p.goal_state));
            Node* right = new Node(p.right(root->state), root, "RIGHT", CalculateMisplaced(p.right(root->state), p.goal_state));

            //ASSIGNING CHILDREN
            root->up = up;
            root->down = down;
            root->left = left;
            root->right = right;

            //MARKING THEM AS VISITED
            visited[up->state] = true;
            visited[down->state] = true;
            visited[left->state] = true;
            visited[right->state] = true;

            //PUT THESE NODES IN PRIORITY QUEUE
            pq.push(up);
            pq.push(down);
            pq.push(left);
            pq.push(right);

            Node* curr;
            int count = 0;
            unsigned size = 0;

            while (!pq.empty()) {
                curr = pq.top();

                //GETTING THE MAX SIZE OF PQ
                size = (pq.size() > size) ? pq.size() : size;
                
                cout << "The best state to expand with g(n) = " << curr->cost << " and h(n) = " << curr->h << " is " << endl;
                print(curr->state);
                cout << "Expanding this node..." << endl;
                cout << "-----------------------------" << endl;
                
                count++;
                if (curr->state == p.goal_state) {
                    cout << "SUCCESS" << endl;
                    backtrack(curr);
                    cout << "-----------------------------" << endl;
                    cout << "FOUND SUCCESS AFTER EXPANDING " << curr->totalcost << " NODES" << endl;
                    cout << "TOTAL NODES EXPLORED: " << count << endl;
                    cout << "MAXIMUM PRIORITY QUEUE SIZE: " << size << endl;
                    return true;
                }

                pq.pop();

                //FOR UP
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.up(curr->state))) {
                    Node* up = new Node(p.up(curr->state), curr, "UP", CalculateMisplaced(curr->state, p.goal_state));
                    curr->up = up;
                    visited[up->state] = true;
                    pq.push(up);
                }

                //FOR DOWN
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.down(curr->state))) {
                    Node* down = new Node(p.down(curr->state), curr, "DOWN", CalculateMisplaced(curr->state, p.goal_state));
                    curr->down = down;
                    visited[down->state] = true;
                    pq.push(down);
                }

                //FOR LEFT
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.left(curr->state))) {
                    Node* left = new Node(p.left(curr->state), curr, "LEFT", CalculateMisplaced(curr->state, p.goal_state));
                    left->identity = "LEFT";
                    curr->left = left;
                    visited[left->state] = true;
                    pq.push(left);
                }

                //FOR RIGHT
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.right(curr->state))) {
                    Node* right = new Node(p.right(curr->state), curr, "RIGHT", CalculateMisplaced(curr->state, p.goal_state));
                    right->identity = "RIGHT";
                    curr->right = right;
                    visited[right->state] = true;
                    pq.push(right);
                }
            }
            cout << "FAILED AFTER EXPANDING " << count << " NODES" << endl;
            cout << "MAXIMUM PRIORITY QUEUE SIZE: " << size << endl;;
            return false;
        }

        //A* with the Eucledian distance heuristic.
        bool AStarEuclidian(Problem p) {
            
            //MAP TO KEEP TRACK OF VISITED NODES
            map<vector<vector<int>>, bool> visited;

            //IF THE ROOT IS THE ANSWER THEN DON'T WASTE TIME FINDING THE SOLUTION
            Node* root = new Node(p.initial_state);
            if (root->state == p.goal_state) {
                cout << "SUCCESS" << endl;
                cout << "FOUND SUCCESS AFTER EXPANDING " << root->totalcost << " NODES" << endl;
                cout << "TOTAL NODES EXPLORED: 0" << endl;
                return true;
            }
            
            cout << "-----------------------------" << endl;
            cout << "PRINTING INITIAL STATE" << endl;
            print(root->state);
            cout << "-----------------------------" << endl;

            //PRIORITY QUEUE FOR NODES TO VISIT
            priority_queue<Node*, vector<Node*>, TotalCostCompare> pq;

            //NODES AFTER OPERATIONS
            Node* up = new Node(p.up(root->state), root, "UP", CalculateEuclidian(p.up(root->state)));
            Node* down = new Node(p.down(root->state), root, "DOWN", CalculateEuclidian(p.down(root->state)));
            Node* left = new Node(p.left(root->state), root, "LEFT", CalculateEuclidian(p.left(root->state)));
            Node* right = new Node(p.right(root->state), root, "RIGHT", CalculateEuclidian(p.right(root->state)));

            //ASSIGNING CHILDREN
            root->up = up;
            root->down = down;
            root->left = left;
            root->right = right;

            //MARKING THEM AS VISITED
            visited[up->state] = true;
            visited[down->state] = true;
            visited[left->state] = true;
            visited[right->state] = true;

            //PUT THESE NODES IN PRIORITY QUEUE
            pq.push(up);
            pq.push(down);
            pq.push(left);
            pq.push(right);

            Node* curr;
            int count = 0;
            unsigned size = 0;

            while (!pq.empty()) {
                curr = pq.top();

                //GETTING THE MAX SIZE OF PQ
                size = (pq.size() > size) ? pq.size() : size;
                
                cout << "The best state to expand with f(n) = " << curr->totalcost << ", g(n) = " << curr->cost << " and h(n) = " << curr->h << " is " << endl;
                print(curr->state);
                cout << "Expanding this node..." << endl;
                cout << "-----------------------------" << endl;
                
                count++;
                if (curr->state == p.goal_state) {
                    cout << "SUCCESS" << endl;
                    backtrack(curr);
                    cout << "FOUND SUCCESS WITH TOTAL COST: " << curr->totalcost << endl;
                    cout << "TOTAL NODES EXPANDED: " << count << endl;
                    cout << "MAXIMUM PRIORITY QUEUE SIZE: " << size << endl;
                    return true;
                }

                pq.pop();

                //FOR UP
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.up(curr->state))) {
                    Node* up = new Node(p.up(curr->state), curr, "UP", CalculateEuclidian(p.up(curr->state)));
                    curr->up = up;
                    visited[up->state] = true;
                    pq.push(up);
                }

                //FOR DOWN
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.down(curr->state))) {
                    Node* down = new Node(p.down(curr->state), curr, "DOWN", CalculateEuclidian(p.down(curr->state)));
                    curr->down = down;
                    visited[down->state] = true;
                    pq.push(down);
                }

                //FOR LEFT
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.left(curr->state))) {
                    Node* left = new Node(p.left(curr->state), curr, "LEFT", CalculateEuclidian(p.left(curr->state)));
                    curr->left = left;
                    visited[left->state] = true;
                    pq.push(left);
                }

                //FOR RIGHT
                //IF NOT VISITED THEN VISIT IT AND ADD TO PQ
                if (!visited.count(p.right(curr->state))) {
                    Node* right = new Node(p.right(curr->state), curr, "RIGHT", CalculateEuclidian(p.right(curr->state)));
                    curr->right = right;
                    visited[right->state] = true;
                    pq.push(right);
                }
            }
            cout << "FAILED AFTER EXPANDING " << count << " NODES" << endl;
            cout << "MAXIMUM PRIORITY QUEUE SIZE: " << size << endl;
            return false;
        }
};
