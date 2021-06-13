#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "instance.cpp"
#include <numeric>
#include <math.h>
#include <iomanip>

using namespace std;

class classifier {
	public:
		vector<instance> trainData;
		int numfeatures;
		vector<int> usingfeatures;

		//create set of training instances: trainData
		void train(string filename) {
			importData(filename);
			cout << endl << "Please wait while I normalize the data...	";
    		normalize();
			cout << "Done!" << endl << endl;
		}

		//test an instance against trainData and output predictedClass;
		int test(int id, vector<int> testingfeatures) {
			instance predictedClass;
			usingfeatures = testingfeatures;
			predictedClass.distance = INT16_MAX;

			//RUN A LOOP TO CALCULATE THE DISTANCE FROM TRAIN DATA OF GIVEN ID TO TRAINDATA OF I AND PUSH IT TO PQ
			for (unsigned i = 0; i < trainData.size(); i++) {
				if (i != id) {
					trainData[i].distance = calculateDistance(trainData[id], trainData[i]);
					predictedClass = (trainData[i].distance < predictedClass.distance) ? trainData[i] : predictedClass;
				}
			}
			return predictedClass.classlabel;
		}

		//CALCULATING EUCLIDEAN DISTANCE BETWEEN TWO DATA POINTS
		float calculateDistance(instance testpoint, instance neighbor) {
			float distance = 0;

			//DISTANCE FROM THE TESTPOINT TO THE NEIGHBOR AT THE GIVEN FEATURE
			for (unsigned i = 0; i < usingfeatures.size(); i++) {
				distance += pow((testpoint.normalizedfeatures[usingfeatures[i]-1] - neighbor.normalizedfeatures[usingfeatures[i]-1]), 2.0);
			}
			return sqrt(distance);
		}

		//NORMALIZE THE DATA SET AND PUT IT IN EACH trainData'S NORMALIZED VECTOR
		void normalize() {

			//INITIALIZE A VECTOR OF THE SIZE OF HOWEVER MANY FEATURES WE ARE USING
			vector<vector<float>> set(numfeatures);

			for(unsigned i = 0; i < trainData.size(); i++){
				for(unsigned j = 0; j < trainData[i].features.size(); j++){
					set[j].push_back(trainData[i].features[j]);
				}
			}

			vector<float> meanstd;

			for (unsigned i = 0; i < set.size(); i++) {
				float avg = 0;
				float std = 0;
				float summation = 0;

				//SUM OF ALL THE ELEMENTS IN THE SET DIVIDED BY THE TOTAL SIZE OF THE SET
				avg = accumulate(set[i].begin(), set[i].end(), 0.0) / (float)set[i].size();

				//SUM OF ALL THE ELEMENTS IN THE SET SUBTRACTED BY THE AVERAGE AND RAISED TO A POWER OF 2
				for (unsigned j = 0; j < set[i].size(); j++) {
					summation += pow((set[i][j] - avg), 2);
				}

				//STANDARD DEVIATION IS THE SQUARE ROOT OF THE SUMMATION DIVIDED BY THE TOTAL SIZE
				std = sqrt(summation/(float)set[i].size());
				meanstd.push_back(avg/std);
			}

			//CREATE A NEW NORMALIZEDFEATURES VECTOR INSTEAD OF OVERWRITING THE EXISTING DATASET
			for (unsigned i = 0; i < trainData.size(); i++) {
				for (unsigned j = 0; j < trainData[i].features.size(); j++) {
					trainData[i].normalizedfeatures.push_back(trainData[i].features[j] - meanstd[j]); //NORMALIZE THE FEATURE BY THE MEAN/STD
				}
			}

		}

//---------------------HELPER FUNCTIONS----------------------------------------//

		//HELPER FUNCTION TO PRINT THE NORMALIZED DATA
		void print() {
			for (unsigned i = 0; i < 10; i++) {
				cout << setw(10) << i << " | ";
			}
			cout << endl;
			for (unsigned i = 0; i < trainData.size(); i++) {
				cout << "INSTANCE ID#" << i << endl;
				for (unsigned j = 0; j < trainData[i].normalizedfeatures.size(); j++) {
					cout << setw(10) << trainData[i].normalizedfeatures[j] << " | ";
				}
				cout << endl << endl;
			}
		}

		//IMPORT THE TEXT FILE AND PARSE IT
		void importData(string fileName) {
			ifstream fin;
			string temp;
			fin.open(fileName);
			if(!fin.is_open()) {
				cout << "Failed to open \"" << fileName << "\"" << endl;
				exit(404);
			}
			while(getline(fin, temp)) {
				stringstream ss(temp);
				int classlabel;
				ss >> classlabel;
				instance x;
				x.setClass(classlabel);
				float feature;
				while(ss >> feature) {
					x.addFeature(feature);
				}
				trainData.push_back(x);
			}
			for(unsigned i = 0 ; i < trainData.size(); i++){
				trainData[i].features.erase(trainData[i].features.begin());
			}
			numfeatures = trainData[0].features.size();
		}
};	
