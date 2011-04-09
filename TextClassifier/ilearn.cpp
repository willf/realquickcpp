#include <iostream>
#include "TextClassifier.h" 
#include "UnigramTextClassifier.h" 

using namespace std;

int main(int argc,char *argv[]) 
{ 
  UnigramTextClassifier x = UnigramTextClassifier((string)argv[1]);
  x.learn(cin);
  x.dump(cout);
}
