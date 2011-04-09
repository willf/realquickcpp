#ifndef _NgramTextClassifier_H_
#define _NgramTextClassifier_H_
#include <map>
#include <iostream>
#include <fstream>

namespace std 
{
  /*! 
      frequencies_map is a  map of unsigned characters to frequencies.
     */
  typedef map<unsigned long,unsigned long> frequency_map;

  /*! \brief A text classifier based on single characters.
    The basic idea: texts from the same class will tend to have 
    character (byte) frequencies that are similar. In information
    theoretical terms, texts from the same class should require the same
    number of bits to encode them in a perfect encoding. We don't
    actually have to create the encoding, just use the number of bits.
    The basic methods are <b>learn</b> (read a corpus and count the
    frequencies), <b>dump</b> (save the frequencies to a stream) and 
    <b>read</b>, read the frequencies from a stream.
  */   
  class NgramTextClassifier : public TextClassifier
  {
  public:
   
    /*! \brief Constructor.
      Constructor for NgramTextClassifier. Name of classification
      defaults to 'Unknown.'
    */   
    NgramTextClassifier();

    /*! \brief Constructor.
      Constructor for NgramTextClassifier. 
      \param classification The name of the classification (e.g., "Spam").
    */
    NgramTextClassifier(const string classification);

    /*! \brief Constructor.
      Constructor for NgramTextClassifier. 
      \param classification The name of the classification (e.g., "Spam").
      \param n size of ngram
    */
    NgramTextClassifier(const string classification, int nsize);
    /*! \brief Constructor.
      Constructor for NgramTextClassifier. 
      \param n size of ngram
    */
    NgramTextClassifier(int nsize);
    /*! 
      \return the map of characters and their frequencies.
     */
    frequency_map freqs() { return _freqs; }

    int NGramSize() { return _n_gram_size; }

    /*! \brief Learn the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void NgramTextClassifier::learn(istream& in);

    /*! \brief Dump the frequencies of characters in a corpus.
      Dump the frequencies of characters in a corpus.
      \param out the output stream, which must be open.
    */
    void NgramTextClassifier::dump(ostream& out);
 
    /*! \brief Read the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void NgramTextClassifier::read(istream& in);

    /*! What's the score? Percentage compressed.
      \param in an input stream, which must be open.
      \return score between 0.0 and 1.0
    */  
    float NgramTextClassifier::score(istream& in); 

    float NgramTextClassifier::bits_required(unsigned char ch);

    /*! How many bits would it take to encode the characters a stream?
      \param in The stream in question
      \return Number of bits required.
    */   
    float NgramTextClassifier::bits_required(istream& in);
   
    /*! How many bits would it take to encode the characters a file?
      
    \param in The fiele in question
    \return Number of bits required.
    */
    float NgramTextClassifier::bits_required(char* in);
  private:
    /*! internal character->frequency map */
    frequency_map _freqs;
    /*! internal running ngram */
    unsigned long _n_gram;
    int _n_gram_size;
  };

}
using namespace std;

#endif /* _NgramTextClassifier_H_ */
