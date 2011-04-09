#include <iostream>
#include "TextClassifier.h" 
#include "NgramTextClassifier.h" 

using namespace std;

int main(int argc,char *argv[]) 
{ 
  NgramTextClassifier x = NgramTextClassifier((string)argv[1],atoi(argv[2]));
  x.learn(cin);
  x.dump(cout);
}
