#ifndef TextClassifier_H_
#define TextClassifier_H_
#include <map>
#include <iostream>
#include <fstream>
namespace std 
{
  class TextClassifier 
  {
  public:

    TextClassifier();
    TextClassifier(const string classification);

    unsigned long corpusTotal() { return _corpus_total; }
    /* ... etc ... */
    virtual void TextClassifier::learn(istream& in) =0;

    virtual float TextClassifier::score(istream& in); 
    /* ... etc ... */
  private:
    /*! internal total number of characters in corpus */
    unsigned long _corpus_total;
    /* ... etc ... */
  };
}
using namespace std;
#endif /* TextClassifier_H_ */
