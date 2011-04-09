#ifndef TextClassifier_H_
#define TextClassifier_H_
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>

namespace std 
{

  /*! \brief A text classifier. 
    T
    The required virtual methods are <b>learn</b> (read a corpus and count the
    frequencies), <b>dump</b> (save the frequencies to a stream) and 
    <b>read</b>, read the frequencies from a stream.
  */   
  class TextClassifier 
  {
  public:
   
    /*! \brief Constructor.
      Constructor for TextClassifier. Name of classification
      defaults to 'Unknown.'
    */   
    TextClassifier()
    {
      _total = 0;
      _corpus_total = 0;
      _classification = "Unknown"; 
    }

    /*! \brief Constructor.
      Constructor for TextClassifier. 
      \param classification The name of the classification (e.g., "Spam").
    */
    TextClassifier(const string classification)
    {
      _total = 0;
      _corpus_total = 0;
      _classification = classification; 
    }
    /*! 
      \return the total number of characters in the corpus.
     */
    unsigned long corpusTotal() { return _corpus_total; }

    /*! 
      \param corpus total
     */
    void setCorpusTotal(long i) {_corpus_total = i; }
    /*! 
      \return the total number of characters in the probe text.
     */
    unsigned long total() { return _total; }
    /*! 
      \param total
     */
    void setTotal(long i) {_total = i; }
    /*! 
      \return the name of the classifier.
     */
    string classification() { return _classification; }
    /*! 
      \param classification the name of the classifier.
     */
    void setClassification(string& classification) {_classification = classification;}

    /*! \brief Learn the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    virtual void TextClassifier::learn(istream& in) =0;

    /*! \brief Learn the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in a filename.
    */
    void TextClassifier::learn(char* in) 
    {
      ifstream instr(in);
      learn(instr);
      instr.close();
    }

    /*! \brief Dump the frequencies of characters in a corpus.
      Dump the frequencies of characters in a corpus.
      \param out the output stream, which must be open.
    */
    void TextClassifier::dump(ostream& out);
 
    /*! \brief Dump the frequencies of characters in a corpus.
      Dump the frequencies of characters in a corpus.
      \param out the output filename.
    */
    void TextClassifier::dump(char* out)
    {
      ofstream outstr(out);
      dump(outstr);
      outstr.close();
    }

    /*! \brief Read the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void TextClassifier::read(istream& in);

    /*! \brief Read the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in a filename.
    */
    void TextClassifier::read(char* in)
    {
      ifstream instr(in);
      learn(instr);
      instr.close();
    }
 
    /*! What's the score? Percentage compressed.
      \param in an input stream, which must be open.
      \return score between 0.0 and 1.0
    */  
    float TextClassifier::score(istream& in); 
    /*! What's the score? Percentage compressed.
    \param in The file in question
    \return score between 0.0 and 1.0
    */
    float TextClassifier::score(char* in) 
      {
	ifstream instr(in);
	float sc = score(instr);
	instr.close();
	return sc;
      }

    unsigned long TextClassifier::incCount() 
    {
      return _total++;
    }

    unsigned long TextClassifier::incCorpusCount() 
    {
      return _corpus_total++;
    }
    unsigned long TextClassifier::incCorpusCount(long i) 
    {
      _corpus_total += i;
      return _corpus_total;
    }
    virtual ~TextClassifier() {} 

    
    /*! internal information value function -lg(n) */
    float TextClassifier::info_value(float n)
    {
      return -log2(n);
    }

  private:

    /*! internal total number of characters in corpus */
    unsigned long _corpus_total;
    /*! internal total number of characters in text */
    unsigned long _total;
    /*! internal name of classifer */
    string _classification;

  };
}
using namespace std;

#endif /* TextClassifier_H_ */
