#include <time.h>
#include "TextClassifier.h" 
#include "NgramTextClassifier.h" 

using namespace std;

NgramTextClassifier::NgramTextClassifier() 
{
  string cl = "Unknown";
  setTotal(0);
  setCorpusTotal(0);
  setClassification(cl);
  _n_gram_size = 1;
  _n_gram = 0;
}


NgramTextClassifier::NgramTextClassifier(const string classification) 
{
  string cl = classification;
  setTotal(0);
  setCorpusTotal(0);
  setClassification(cl);
  _n_gram_size = 1;
  _n_gram = 0;
}

NgramTextClassifier::NgramTextClassifier(const string classification, int n) 
{
  string cl = classification;
  setTotal(0);
  setCorpusTotal(0);
  setClassification(cl);
  _n_gram_size = n;
  _n_gram = 0;
}

NgramTextClassifier::NgramTextClassifier(int n) 
{
  string cl = "Unknown";
  setTotal(0);
  setCorpusTotal(0);
  setClassification(cl);
  _n_gram_size = n;
  _n_gram = 0;
}

void NgramTextClassifier::learn(istream& in)
{
  char ch; // note: in.get requires char, not unsigned char
  unsigned long mask = 0;
  switch (_n_gram_size) 
    {
    case 1: mask = 0x000000FF; break;
    case 2: mask = 0x0000FFFF; break;
    case 3: mask = 0x00FFFFFF; break;
    case 4: mask = 0xFFFFFFFF; break;
    default: { /* throw an error ... */ }
    }
  
  while (in.get(ch))
    {
      // shift left 8 bits; add 'ch', mask out bits
     //  cout << "CH: " << ch << ";as unsigned long: " << ((unsigned long)ch)
// 	   << "; _n_gram: " <<  _n_gram << "; shifted: " << (_n_gram << 8) 
// 	   << "; mask: " << mask;
      _n_gram = ((_n_gram << 8) + (unsigned long)ch) & mask;
      //      cout << "; new _n_gram: " << _n_gram << endl;
      incCorpusCount();
      if (corpusTotal() > (unsigned long)_n_gram_size) 
	{
	  _freqs[_n_gram]++;
	}
    }
}

void NgramTextClassifier::dump(ostream& out) 
{
  frequency_map m = this->freqs();
  long tot = this->corpusTotal();
  out << "// NgramTextClassifier created this file from " << tot
      << " characters.\n";
  out << "Classification\t" << this->classification() << endl;
  out << "Total\t" << tot << endl;
  for (frequency_map::iterator it=m.begin(); it != m.end(); it++) 
    {
      out << it->first << "\t" << it->second << "\t" 
	  << info_value((float)(it->second)/tot) << endl;
    }
}


void NgramTextClassifier::read(istream& in)
{
  
  string classification; 
  unsigned long i; 
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
      i = (unsigned long)atol(text);
      in.getline(text,256,'\t');
      frequency = atol(text);
      _freqs[i] = frequency;
      incCorpusCount(frequency);
      in.getline(text,256); // ignore rest of line
    }
}



float NgramTextClassifier::score (istream& in) 
{
  frequency_map sfreqs;
  char ch; // note: in.get requires char, not unsigned char
  unsigned long mask = 0;
  switch (_n_gram_size) 
    {
    case 1: mask = 0x000000FF; break;
    case 2: mask = 0x0000FFFF; break;
    case 3: mask = 0x00FFFFFF; break;
    case 4: mask = 0xFFFFFFFF; break;
    default: { /* throw an error ... */ }
    }

  // reset _n_gram, count
  unsigned long n_gram = 0;
  unsigned long ttotal = 0;
  // setCount(0); -- add this

  while (in.get(ch))
    {
      // shift left 8 bits; add 'ch', mask out bits
      // cout << "CH: " << ch << ";as unsigned long: " << ((unsigned long)ch)
      //  << "; _n_gram: " <<  _n_gram << "; shifted: " << (_n_gram << 8) 
      //   << "; mask: " << mask;
      n_gram = ((n_gram << 8) + (unsigned long)ch) & mask;
      //    cout << "; new _n_gram: " << _n_gram << endl;
      ttotal++;
      if (ttotal > (unsigned long)_n_gram_size) 
	{
	  sfreqs[n_gram]++;
	}
    }
  float bits = 0.0;
  long tot = this->corpusTotal();
  frequency_map m = this->freqs();
  for (frequency_map::iterator it=sfreqs.begin(); it != sfreqs.end(); it++) 
    {
      long frequency = ((!m[it->first]) ? 1 : m[it->first]) ;
      bits += info_value((float)frequency/tot) * it->second;
    }
  // cout << tot << " " << this->classification() << " " << (- bits) << "; size " << _n_gram_size << endl;
  return  - bits; // fewer the better
}
// {
//   float br = bits_required(in);
//   long tot = total()*8;
//   float sc = 1 - br/tot;
//   return (sc >= 0 ? sc : 0.0) ;
// }

float NgramTextClassifier::bits_required(unsigned char ch) 
{
  frequency_map m = this->freqs();
  long tot = this->total();
  long frequency = ((!m[ch]) ? 1 : m[ch]) ;
  return info_value((float)frequency/tot);
}

float NgramTextClassifier::bits_required(istream& in)
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

float NgramTextClassifier::bits_required(char* fname)
{
  ifstream instr(fname);
  return bits_required(instr);
  instr.close();
}



