#include <map>

using namespace std;

class node {
    public:
        float accuracy;
        map<int,int> features;
        node(){
            accuracy = 0.0;
        }
};