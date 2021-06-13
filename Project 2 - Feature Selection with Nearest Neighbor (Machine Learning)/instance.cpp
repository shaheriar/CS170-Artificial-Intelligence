#include <vector>

using namespace std;

class instance {
	public:
        float classlabel;
		vector<float> features;
		vector<float> normalizedfeatures;
		float distance;
        void setClass(float c) {
            classlabel = c;
        }
		void addFeature(float f) {
				features.push_back(f);
		}
};
					
	
            
