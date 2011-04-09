#ifndef _UnigramTextClassifier_H_
#define _UnigramTextClassifier_H_
#include <map>
#include <iostream>
#include <fstream>

namespace std 
{
  
  typedef map<unsigned char,unsigned long> frequency_map;

  
  class UnigramTextClassifier 
  {
  public:
    
    UnigramTextClassifier();
    UnigramTextClassifier(const string classification);

    frequency_map freqs() { return _freqs; }
    unsigned long corpus_total() { return _corpus_total; }
    unsigned long total() { return _total; }
    string classification() { return _classification; }
    void setClassification(string& classification) {_classification = classification;}

    void UnigramTextClassifier::learn(istream& in);
    void UnigramTextClassifier::learn(char* in);
    
    void UnigramTextClassifier::dump(ostream& out);
    void UnigramTextClassifier::dump(char* out);

    void UnigramTextClassifier::read(istream& in);
    void UnigramTextClassifier::read(char* in);
  
    float UnigramTextClassifier::score(istream& in); 
    float UnigramTextClassifier::score(char* in) ;
     
    float UnigramTextClassifier::bits_required(unsigned char ch);
    float UnigramTextClassifier::bits_required(istream& in);
    float UnigramTextClassifier::bits_required(char* in);
  private:
    /*! internal character->frequency map */
    frequency_map _freqs;
    /*! internal total number of characters in corpus */
    unsigned long _corpus_total;
    /*! internal total number of characters in text */
    unsigned long _total;
    /*! internal name of classifer */
    string _classification;
    /*! internal base-2 logarithm */
    float UnigramTextClassifier::lg (float n);
    /*! internal information value function -lg(n) */
    float UnigramTextClassifier::info_value(float n);
    /*! internal current time stream */
    string UnigramTextClassifier::ctime_string();
  };
}
using namespace std;

#endif /* _UnigramTextClassifier_H_ */
