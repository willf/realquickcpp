#include <iostream>
#include "UnigramTextClassifier.h" 

using namespace std;
using namespace TextClassifier;

int main(int argc,char *argv[]) 
{ 
  UnigramTextClassifier x = UnigramTextClassifier((string)argv[1]);
  x.learn(cin);
  x.dump(cout);
}
