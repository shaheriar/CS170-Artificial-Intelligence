#include <iostream>
#include <vector>
#include <map>
#include "Search.cpp"

using namespace std;

int main() {
    string input;
    bool correct = false;
    int num;
    Problem p;
    Search search;
    string first, second, third;
    vector<vector<int>> problem;
    map<int, bool> valid;
    vector<int> row1, row2, row3;


    cout << "---------------"   << endl
         << "8-PUZZLE SOLVER"   << endl
         << "---------------"   << endl
         << "1. Trivial"        << endl 
         << "2. Very Easy"      << endl 
         << "3. Easy"           << endl
         << "4. Doable"         << endl
         << "5. Oh Boy"         << endl
         << "6. Impossible"     << endl
         << "7. Custom Problem" << endl
                                << endl
         << "Please choose which difficulty to start with: ";

    while(!correct) {
		try {
            cin >> input;
			num = stoi(input); correct = true;
		} catch(const invalid_argument& error) {
			cout << "Invalid entry. Please input a number 1-6: ";
			cin >> input;
		}
        switch(num) {
            case 1:
                p.initial_state = p.trivial;
                correct = true;
                break;

            case 2:
                p.initial_state = p.very_easy;
                correct = true;
                break;

            case 3:
                p.initial_state = p.easy;
                correct = true;
                break;

            case 4:
                p.initial_state = p.doable;
                correct = true;
                break;

            case 5:
                 p.initial_state = p.ohboy;
                correct = true;
                break;

            case 6:
                p.initial_state = p.impossible;
                correct = true;
                break;

            case 7:
                cout << "Please enter the first row: ";
                cin >> first;
                cout << "Please enter the second row: ";
                cin >> second;
                cout << "Please enter the third row: ";
                cin >> third;

                for (auto x : first) {
                    row1.push_back(int(x)-48);
                }
                problem.push_back(row1);

                for (auto x : second) {
                    row2.push_back(int(x)-48);
                }
                problem.push_back(row2);

                for (auto x : third) {
                    row3.push_back(int(x)-48);
                }
                problem.push_back(row3);
                
                p.initial_state = problem;
                break;
                
            default:
                cout << "Invalid entry. Please input a number 1-6: ";
                correct = false;
                break;
        }
	}
    correct = false;
    cout << "----------" << endl
         << "Algorithms" << endl
         << "----------" << endl
         << "1) Uniform Cost Search"                << endl
         << "2) A* Search with Misplaced Heuristic" << endl
         << "3) A* Search with Euclidean Heuristic" << endl << endl

         << "Please select which algorithm to solve this problem with (1-3): ";

    while (!correct) {
        try {
            cin >> input;
			num = stoi(input); correct = true;
		} catch(const invalid_argument& error) {
			cout << "Invalid entry. Please input a number 1-3: ";
			cin >> input;
		}
        switch (num) {
            case 1: 
                search.uniformCostSearch(p);
                correct = true; 
                break;
            case 2: 
                search.AStarMisplaced(p); 
                correct = true; 
                break;
            case 3: 
                search.AStarEuclidian(p); 
                correct = true; 
                break;
            default:
                cout << "Invalid entry. Please input a number 1-3: ";
                correct = false;
                break;
        }
    }
    return 0;
}