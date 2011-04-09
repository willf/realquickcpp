#ifndef UnigramTextClassifier_H
#define UnigramTextClassifier_H
#include <map>
#include <iostream>
#include <fstream>

namespace TextClassifier
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
  class UnigramTextClassifier 
  {
  public:
   
    /*! \brief Constructor.
      Constructor for UnigramTextClassifier. Name of classification
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
    frequency_map freqs() { return my_freqs; }
    /*! 
      \return the total number of characters in the corpus.
     */
    unsigned long corpus_total() { return my_corpus_total; }
    /*! 
      \return the total number of characters in the corpus.
     */
    unsigned long total() { return my_total; }
    /*! 
      \return the name of the classifier.
     */
    string classification() { return my_classification; }
    /*! 
      \param classification the name of the classifier.
     */
    void setClassification(string& classification) {my_classification = classification;}

    /*! \brief Learn the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void UnigramTextClassifier::learn(istream& in);

    /*! \brief Learn the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in a filename.
    */
    void UnigramTextClassifier::learn(char* in);

    /*! \brief Dump the frequencies of characters in a corpus.
      Dump the frequencies of characters in a corpus.
      \param out the output stream, which must be open.
    */
    void UnigramTextClassifier::dump(ostream& out);
 
    /*! \brief Dump the frequencies of characters in a corpus.
      Dump the frequencies of characters in a corpus.
      \param out the output filename.
    */
    void UnigramTextClassifier::dump(char* out);

    /*! \brief Read the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in an input stream, which must be open.
    */
    void UnigramTextClassifier::read(istream& in);

    /*! \brief Read the frequencies of characters in a corpus.
      Learn the frequencies of characters in a corpus; may be called
      multiple times.
      \param in a filename.
    */
    void UnigramTextClassifier::read(char* in);
 
    /*! What's the score? Percentage compressed.
      \param in an input stream, which must be open.
      \return score between 0.0 and 1.0
    */  
    float UnigramTextClassifier::score(istream& in); 
    /*! What's the score? Percentage compressed.
    \param in The file in question
    \return score between 0.0 and 1.0
    */
    float UnigramTextClassifier::score(char* in) ;
    /*! How many bits would it take to code a character?
      \param ch The character in question.
      \return Number of bits required.
    */  

    float UnigramTextClassifier::bits_required(unsigned char ch);

    /*! How many bits would it take to encode the characters a stream?
      \param in The stream in question
      \return Number of bits required.
    */   
    float UnigramTextClassifier::bits_required(istream& in);
   
    /*! How many bits would it take to encode the characters a file?
      
    \param in The file in question
    \return Number of bits required.
    */
    float UnigramTextClassifier::bits_required(char* in);
  private:
    /*! internal character->frequency map */
    frequency_map my_freqs;
    /*! internal total number of characters in corpus */
    unsigned long my_corpus_total;
    /*! internal total number of characters in text */
    unsigned long my_total;
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

#endif /* UnigramTextClassifier_H */
