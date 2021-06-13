#include "node.cpp"
#include "validator.cpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

class search {
    public:
        classifier classify;

        //RETURNS A NODE WITH THE HIGHEST ACCURACY USING FORWARD SELECTION
        node* forwardselection() {                              //takes in the number of features
            bool found = false;                                 //boolean to check if we found a higher accuracy than curr
            node* curr = new node();                            //curr is the root -> it has 0 features and 4 children
            validator firstv;
            curr->accuracy = firstv.evaluateAccuracy(classify);
            cout << "Running nearest neighbor with no features (default rate), using \"leave-one-out\" evaluation, I get an accuracy of " << setprecision(3) << curr->accuracy * 100.00  << "%" << endl << endl;
            int features = classify.numfeatures;
            //outer for loop reduces the number of children
            for (int numchild = features; numchild >= 0; numchild--) {

                found = false;
                //initiliaze the nextnode to curr
                node* nextnode = curr;

                //inner for loop goes through the children of curr and checks for accuracy
                for (int i = 1; i < features + 1; i++) {

                    if (!curr->features.count(i)) {             //if a feature is not included as a child
                        node* child = new node();               //make a new child
                        child->features = curr->features;       //copy the features from the parent
                        child->features[i] = i;                 //make sure that the selected feature is added
                        validator v;
                        for (auto x : child->features) {
                            v.featureSubset.push_back(x.second);
                        }
                        float childeval = v.evaluateAccuracy(classify);
                        child->accuracy = childeval;
                        cout << setprecision(3) << "Using feature(s) {";
                        print(child);
                        cout << "} accuracy is " << child->accuracy * 100.00 << "%" << endl;

                        if (childeval > nextnode->accuracy) {   //check for max accuracy
                            nextnode = child;                   //select the max accuracy node as the next node to expand
                            found = true;                       //
                        }
                    }

                }
                if (!found) {                                   //if none of the children have a higher accuracy than curr
                    cout << endl << "(Warning! Accuracy has decreased!)" << endl;
                    return curr;                                //return curr
                }

                curr = nextnode;                                //else curr becomes next node
                cout << endl << "Feature set {";
                print(nextnode);
                cout << "} was best, accuracy is " << nextnode->accuracy * 100 << "%" << endl << endl; 
            }
            return curr;
        }

        node* backwardselection() {
            bool found = false;
            validator firstv;
            node* curr = new node();
            int features = classify.numfeatures;
            for (int i = 1; i < features + 1; i++) {
                curr->features[i] = i;
                firstv.featureSubset.push_back(i);
            }
            curr->accuracy = firstv.evaluateAccuracy(classify);
            cout << "Running nearest neighbor with all features (default rate), using \"leave-one-out\" evaluation, I get an accuracy of " << setprecision(3) << curr->accuracy * 100.00  << "%" << endl << endl;
            for (int numchild = 0; numchild <= features; numchild++) {          //same as forward selection but now num of children start from 0 and go up
                found = false;
                node* nextnode = curr;
                for (int i = 1; i < features + 1; i++) {
                    if (curr->features.count(i)) {                              //if the feature is included remove it
                        node* child = new node();
                        child->features = curr->features;
                        child->features.erase(i);
                        validator v;
                        for (auto x : child->features) {
                            v.featureSubset.push_back(x.second);
                        }
                        float childeval = v.evaluateAccuracy(classify);
                        child->accuracy = childeval;
                        cout << setprecision(3) << "Using feature(s) {";
                        print(child);
                        cout << "} accuracy is " << child->accuracy * 100 << "%" << endl;
                        if (childeval >= nextnode->accuracy) {
                            nextnode = child;
                            found = true;
                        }
                    }
                }
                if (!found) {
                    cout << endl << "(Warning! Accuracy has decreased!)" << endl;
                    return curr;
                }
                curr = nextnode;
                cout << endl << "Feature set {";
                print(nextnode);
                cout << "} was best, accuracy is " << nextnode->accuracy * 100 << "%" << endl << endl; 
            }
            return curr;
        }
        
        void print(node* f) {
            map<int,int>::iterator it;
            for (it = f->features.begin(); it != f->features.end(); it++) {
                if (it == prev(f->features.end())) {
                    cout << it->second;
                } else {
                    cout << it->second << ",";
                }
            }
        }
};