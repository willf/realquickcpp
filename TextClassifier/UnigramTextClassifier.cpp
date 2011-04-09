#include <time.h>
#include "TextClassifier.h" 
#include "UnigramTextClassifier.h" 

using namespace std;

UnigramTextClassifier::UnigramTextClassifier() 
{
  string cl = "Unknown";
  setTotal(0);
  setCorpusTotal(0);
  setClassification(cl);
}


UnigramTextClassifier::UnigramTextClassifier(const string classification) 
{
  string cl = classification;
  setTotal(0);
  setCorpusTotal(0);
  setClassification(cl);
}

void UnigramTextClassifier::learn(istream& in)
{
  char ch; // note: in.get requires char, not unsigned char
  while (in.get(ch))
    {
      _freqs[ch]++;
      // _corpus_total++;
      incCorpusCount();
    }
}

void UnigramTextClassifier::dump(ostream& out) 
{
  frequency_map m = this->freqs();
  long tot = this->corpusTotal();
  out << "// UnigramTextClassifier created this file from " << tot
      << " characters.\n";
  out << "Classification\t" << this->classification() << endl;
  out << "Total\t" << tot << endl;
  for (frequency_map::iterator it=m.begin(); it != m.end(); it++) 
    {
      out << (unsigned int)it->first << "\t" << it->second << "\t" 
	  << info_value((float)(it->second)/tot) << endl;
    }
}


void UnigramTextClassifier::read(istream& in)
{
  
  string classification; 
  unsigned char ch; 
  long frequency;
  char text[256];
  in.getline(text,256,'\n');  // throw away first line
  in.getline(text,256,'\t'); // ignore class header
  in.getline(text,256,'\n'); // get class
  classification = (string)text;
  this->setClassification(classification);
  in.getline(text,256); // throw away 'total' line
  
  while (true)
    {
      in.getline(text,256,'\t'); 
      if (text[0]==0) break;
      ch = (unsigned char)atoi(text);
      in.getline(text,256,'\t');
      frequency = atol(text);
      _freqs[ch] = frequency;
      incCorpusCount(frequency);
      in.getline(text,256); // ignore rest of line
    }
}



float UnigramTextClassifier::score (istream& in) 
{
  float br = bits_required(in);
  long tot = total()*8;
  float sc = 1 - br/tot;
  return (sc >= 0 ? sc : 0.0) ;
}

float UnigramTextClassifier::bits_required(unsigned char ch) 
{
  frequency_map m = this->freqs();
  long tot = this->corpusTotal();
  long frequency = ((!m[ch]) ? 1 : m[ch]) ;
  return info_value((float)frequency/tot);
}

float UnigramTextClassifier::bits_required(istream& in)
{
  char ch; // note: in.get requires char, not unsigned char
  float bits = 0;
  frequency_map tfreq; 
  // count the frequencies in this text
  while (in.get(ch))
    {
      tfreq[(unsigned char)ch]++;
      incCount();
    }
  // iterate through the temp map adding bits * frequency
  for (frequency_map::iterator it=tfreq.begin(); it != tfreq.end(); it++) 
    {
      bits += bits_required(it->first) * it->second;
    }
  return bits;
}

float UnigramTextClassifier::bits_required(char* fname)
{
  ifstream instr(fname);
  return bits_required(instr);
  instr.close();
}



