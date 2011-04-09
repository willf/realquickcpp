#include <map>
#include <iostream>
#include <fstream>
#include <time.h>
#include "UnigramTextClassifer.h"

using namespace std;

UnigramTextClassifier::UnigramTextClassifier() 
{
  _total = 0;
  _classification = "Unknown"; 
}
UnigramTextClassifier::UnigramTextClassifier(const string classification) 
{
  _total = 0;
  _classification = classification; 
}
void UnigramTextClassifier::learn(istream& in)
{
  char ch; // note: in.get requires char, not unsigned char
  while (in.get(ch))
    {
      _freqs[ch]++;
      _total++;
    }
}

void UnigramTextClassifier::learn(char* fname)
{
  ifstream instr(fname);
  learn(instr);
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
  //cout << "class head?\n" << text << endl;
  in.getline(text,256,'\n'); // get class
  //cout << "class?\n" << text << endl;
  classification = (string)text;
  this->setClassification(classification);
  in.getline(text,256); // throw away 'total' line
  //cout << "total?\n" << text << endl;
  
  //cout << classification << endl;
  
  while (true)
    {
      in.getline(text,256,'\t'); 
      if (text[0]==0) break;
      ch = (unsigned char)atoi(text);
      in.getline(text,256,'\t');
      frequency = atol(text);
      // cout << ch << "\t" << frequency << endl;
      _freqs[ch] = frequency;
      _total+= frequency;
      in.getline(text,256); // ignore rest of line
    }
}

void UnigramTextClassifier::read(char* fname)
{
  ifstream instr(fname);
  read(instr);
  instr.close();
}

void UnigramTextClassifier::dump(ostream& out) 
{
  frequency_map m = this->freqs();
  long tot = this->total();
  out << "// UnigramTextClassifier created this file from " << tot
       << " characters. It was created on " + ctime_string() << ".\n";
  out << "Classification\t" << this->classification() << endl;
  out << "Total\t" << tot << endl;
  for (frequency_map::iterator it=m.begin(); it != m.end(); it++) 
    {
      out << (unsigned int)it->first << "\t" << it->second << "\t" 
	  << info_value((float)(it->second+1)/(tot+256)) << endl;
    }
}

void UnigramTextClassifier::dump(char* fname)
{
  ofstream instr(fname);
  dump(instr);
  instr.close();
}

float UnigramTextClassifier::bits_required(unsigned char ch) 
{
  frequency_map m = this->freqs();
  long tot = this->total() + 256;
  long frequency = m[ch] + 1;
  return info_value((float)frequency/tot);
}

float UnigramTextClassifier::bits_required(istream& in)
{
  char ch; // note: in.get requires char, not unsigned char
  float bits = 0;
  while (in.get(ch))
    {
      bits += bits_required((unsigned char)ch);
    }
  return bits;
}

float UnigramTextClassifier::bits_required(char* fname)
{
  ifstream instr(fname);
  return bits_required(instr);
  instr.close();
}

float UnigramTextClassifier::lg (float n) 
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
  time ( &rawtime );
  timeinfo = localtime(&rawtime );
  char tmpbuf[128];
  strftime(tmpbuf,128,"%Y-%m-%d %H:%M:%S",timeinfo);
  return string(tmpbuf);
}

int main(int argc,char *argv[]) 
{ 
  //UnigramTextClassifier x = UnigramTextClassifier("Ham");
  //float br; 
  //x.learn(cin);
  //x.dump(cout);
  //x.read(cin);
  //x.dump(cout);
  UnigramTextClassifier ham = UnigramTextClassifier();
  UnigramTextClassifier spam = UnigramTextClassifier();
  ham.read(argv[1]);
  spam.read(argv[2]);
  int hams = 0;
  int spams = 0;
  int total = 0;
  for (int i=3; i<argc; i++)
    {
      total++; cout << "."; 
      if (ham.bits_required(argv[i]) < spam.bits_required(argv[i]))
	{
	  hams++;
	}
      else 
	{
	  spams++;
	}
    }
  cout << "Total: " << total << "; Ham: " << hams << "; Spam: " << spams << endl;
}
