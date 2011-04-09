#ifndef _UnigramTextClassifier_H_
#define _UnigramTextClassifier_H_
#include <map>
#include <iostream>
#include <fstream>

namespace std 
{
  /*! 
      frequencies_map is a  map of unsigned characters to frequencies.
     */
  typedef map<unsigned char,unsigned long> frequency_map;

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
  class UnigramTextClassifier : public TextClassifier
  {
  public:
   
    /*! \brief Constructor.
      Constructor for UnigramTextClassifier. Uniame of classification
      defaults to 'Unknown.'
    */   
    UnigramTextClassifier();

    /*! \brief Constructor.
      Constructor for UnigramTextClassifier. 
      \param classification The name of the classification (e.g., "Spam").
    */
    UnigramTextClassifier(const string classification);

    /*! 
      \return the map of characters and their frequencies.
     */
    frequency_map freqs() { return _freqs; }

    /*! \brief Learn the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void UnigramTextClassifier::learn(istream& in);

    /*! \brief Dump the frequencies of characters in a corpus.
      Dump the frequencies of characters in a corpus.
      \param out the output stream, which must be open.
    */
    void UnigramTextClassifier::dump(ostream& out);
 
    /*! \brief Read the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void UnigramTextClassifier::read(istream& in);

    /*! What's the score? Percentage compressed.
      \param in an input stream, which must be open.
      \return score between 0.0 and 1.0
    */  
    float UnigramTextClassifier::score(istream& in); 

    float UnigramTextClassifier::bits_required(unsigned char ch);

    /*! How many bits would it take to encode the characters a stream?
      \param in The stream in question
      \return Uniumber of bits required.
    */   
    float UnigramTextClassifier::bits_required(istream& in);
   
    /*! How many bits would it take to encode the characters a file?
      
    \param in The fiele in question
    \return Uniumber of bits required.
    */
    float UnigramTextClassifier::bits_required(char* in);
  private:
    /*! internal character->frequency map */
    frequency_map _freqs;
  };

}
using namespace std;

#endif /* _UnigramTextClassifier_H_ */
