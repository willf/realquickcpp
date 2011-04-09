#ifndef UnigramTextClassifier_H_
#define UnigramTextClassifier_H_
#include <map>
#include <iostream>
#include <fstream>
namespace std 
{
  class UnigramTextClassifier : public TextClassifier 
  {
  public:

    /* ... etc ... */

  private:

    UnigramTextClassifier ut1 = UnigramTextClassifier();
    UnigramTextClassifier ut2 = ut1;

    void test(UnigramTextClassifier ut) { } 

    void swap(int& i, int& j) { int temp=i; i=j; j=temp; }
    /* ... etc ... */
  };
}
using namespace std;
#endif /* UnigramTextClassifier_H_ */
