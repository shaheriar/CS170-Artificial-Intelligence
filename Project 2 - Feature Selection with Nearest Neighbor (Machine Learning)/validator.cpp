#include "classifier.cpp"
#include <stdlib.h>

using namespace std;

class validator {
  public:
    vector<int> featureSubset;

    float evaluateAccuracy(classifier c){
      float correct = 0;
      float totaltests = 0;

      for (unsigned i = 0; i < c.trainData.size(); i++) {
        if (featureSubset.size()) {
          //IF IT PREDICTS CORRECTLY, INCREMENT CORRECT
          if (c.test(i, featureSubset) == c.trainData[i].classlabel) {
              correct++;
          }
        } else {
          correct += rand() % 2;
        }
          totaltests++;
      }
      return (float)correct/totaltests;
    }

};
