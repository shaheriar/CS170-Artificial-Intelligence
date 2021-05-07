#include <vector>
#include <iostream>

using namespace std;

class Problem {
    public:
        vector<vector<int>> initial_state;

    //OPERATIONS--------------------------

        //WHAT HAPPENS IF WE MOVE 0 UP
        vector<vector<int>> up(vector<vector<int>> v) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (v[i][j] == 0 && i > 0) {
                        swap(v[i][j], v[i-1][j]);
                        return v;
                    }
                }
            }
            return v;
        }

        //WHAT HAPPENS IF WE MOVE 0 DOWN
        vector<vector<int>> down(vector<vector<int>> v) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (v[i][j] == 0 && i < 2) {
                        swap(v[i][j], v[i+1][j]);
                        return v;
                    }
                }
            }
            return v;
        }

        //WHAT HAPPENS IF WE MOVE 0 LEFT
        vector<vector<int>> left(vector<vector<int>> v) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (v[i][j] == 0 && j > 0) {
                        swap(v[i][j], v[i][j-1]);
                        return v;
                    }
                }
            }
            return v;
        }
        
        //WHAT HAPPENS IF WE MOVE 0 RIGHT
        vector<vector<int>> right(vector<vector<int>> v) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (v[i][j] == 0 && j < 2) {
                        swap(v[i][j], v[i][j+1]);
                        return v;
                    }
                }
            }
            return v;
        }
    //------------------------------------

    //STATES------------------------------
        vector<vector<int>> goal_state =   {{1,2,3},
                                            {4,5,6},
                                            {7,8,0}};

        vector<vector<int>> trivial =      {{1,2,3},
                                            {4,5,6},
                                            {7,8,0}};

        vector<vector<int>> easy =         {{1,2,0},
                                            {4,5,3},
                                            {7,8,6}};

        vector<vector<int>> very_easy =    {{1,2,3},
                                            {4,5,6},
                                            {7,0,8}};

        vector<vector<int>> doable =       {{0,1,2},
                                            {4,5,3},
                                            {7,8,6}};

        vector<vector<int>> ohboy =        {{8,7,1},
                                            {6,0,2},
                                            {5,4,3}};

        vector<vector<int>> impossible =   {{1,2,3},
                                            {4,5,6},
                                            {8,7,0}};
    //------------------------------------

};
