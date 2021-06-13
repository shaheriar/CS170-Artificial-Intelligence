#include <iostream>
#include "search.cpp"

using namespace std;


int main() {	
    srand(time(NULL));
    string in, input, filename;
    search s;
    node* node;
    classifier c;
    bool correct = false;
    int num;

    cout << "Welcome to Shaheriar Malik and Crystal Tong's Feature Search Algorithm" << endl << endl;
    cout << "Type in the name of the file to test: ";
    cin >> filename;
    correct = false;
    cout << "1) Forward Selection"  << endl
         << "2) Backward Elimination" << endl
                                    << endl
         << "Please select with search algorithm to use: ";
    while (!correct) {
        try {
            cin >> input;
			num = stoi(input); correct = true;
		} catch(const invalid_argument& error) {
			cout << "Invalid entry. Please input a number 1-3: ";
			cin >> input;
		}
        if (num == 1 || num == 2) {
            c.train(filename);
            s.classify = c;
            cout << "This dataset has " << c.numfeatures << " features (not including the class attribute), with " << c.trainData.size() << " instances" << endl << endl;
        }
        switch (num) {
            case 1:
                node = s.forwardselection();
                correct = true;
                break;
            case 2:
                node = s.backwardselection();
                correct = true; 
                break;
            default:
                cout << "Invalid entry. Please input a number 1-2: ";
                correct = false;
                break;
        }
    }
    cout << setprecision(3);
    cout << endl << "Finished search!! The best feature subset is {";
    s.print(node);
    cout << "}, which has an accuracy of " << node->accuracy * 100 << "%" << endl;
    return 0;
}