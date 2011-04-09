#include <time.h>
#include "UnigramTextClassifier.h" 

using namespace std;
using namespace TextClassifier;

UnigramTextClassifier::UnigramTextClassifier() 
{
  my_total = 0;
  my_corpus_total = 0;
  my_classification = "Unknown"; 
}


UnigramTextClassifier::UnigramTextClassifier(const string classification) 
{
  my_total = 0;
  my_corpus_total = 0;
  my_classification = classification; 
}

void UnigramTextClassifier::learn(istream& in)
{
  char ch; // note: in.get requires char, not unsigned char
  while (in.get(ch))
    {
      my_freqs[ch]++;
      my_corpus_total++;
    }
}

void UnigramTextClassifier::learn(char* fname)
{
  ifstream instr(fname);
  learn(instr);
  instr.close();
}

void UnigramTextClassifier::dump(ostream& out) 
{
  frequency_map m = this->freqs();
  long tot = this->corpus_total();
  out << "// UnigramTextClassifier created this file from " << tot
       << " characters. It was created on " + ctime_string() << ".\n";
  out << "Classification\t" << this->classification() << endl;
  out << "Total\t" << tot << endl;
  for (frequency_map::iterator it=m.begin(); it != m.end(); it++) 
    {
      out << (unsigned int)it->first << "\t" << it->second << "\t" 
	  << info_value((float)(it->second)/tot) << endl;
    }
}

void UnigramTextClassifier::dump(char* fname)
{
  ofstream instr(fname);
  dump(instr);
  instr.close();
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
      my_freqs[ch] = frequency;
      my_corpus_total+= frequency;
      in.getline(text,256); // ignore rest of line
    }
}


void UnigramTextClassifier::read(char* fname)
{
  ifstream instr(fname);
  read(instr);
  instr.close();
}

float UnigramTextClassifier::score (istream& in) 
{
  float br = bits_required(in);
  long tot = total()*8;
  float sc = 1 - br/tot;
  return (sc >= 0 ? sc : 0.0) ;
}

float UnigramTextClassifier::score(char* fname)
{
  ifstream instr(fname);
  float sc = score(instr);
  instr.close();
  return sc;
}


float UnigramTextClassifier::bits_required(unsigned char ch) 
{
  frequency_map m = this->freqs();
  long tot = this->corpus_total();
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
      my_total++;
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

float UnigramTextClassifier::lg(float n) 
{
  const float log2 = log(2.0);
  return log(n)/log2;
}

float UnigramTextClassifier::info_value(float n) 
{
  return -lg(n);
}

string UnigramTextClassifier::ctime_string() 
{
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime(&rawtime);
  char tmpbuf[128];
  strftime(tmpbuf,128,"%Y-%m-%d %H:%M:%S",timeinfo);
  return string(tmpbuf);
}

