#include <iostream>
#include "UnigramTextClassifier.h" 

using namespace std;

int main(int argc,char *argv[]) 
{ 
  if (argc>2) {
    UnigramTextClassifier* temp = new UnigramTextClassifier();
    UnigramTextClassifier* classifiers = new UnigramTextClassifier[argc-2];
    float *scores = new float[argc-2];

    temp->read(argv[1]);
    // read in the classifier data and score 
    for (int i=1; i<(argc-1); i++)
      {
	// cout << "Reading ... " << argv[i] << " (file #" << i << ")" << endl;
	classifiers[i-1].read(argv[i]);
	
	// cout << "Scoring ... " << argv[argc-1] << endl;
	scores[i-1] = classifiers[i-1].score(argv[argc-1]);
      }
    // Print the results
    for (int i=0; i<(argc-2); i++)
      {
	cout << "Classifier: " << classifiers[i].classification() << "; score: " << scores[i] << endl;
      }
    // clean up
    delete [] classifiers;
    delete [] scores;
  }
  else 
    { 
      cout << argv[0] << " classifier_data+ text" << endl; 
    }
}
