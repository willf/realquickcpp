#include <iostream>
#include "TextClassifier.h"
#include "NgramTextClassifier.h" 

using namespace std;

int main(int argc,char *argv[]) 
{ 
  NgramTextClassifier ham = NgramTextClassifier(atoi(argv[1]));
  NgramTextClassifier spam = NgramTextClassifier(atoi(argv[1]));
  cout << "Reading data... ham is " << argv[2] << "; spam is: " << argv[3] << " ";
  ifstream hamstr(argv[2]);
  ifstream spamstr(argv[3]);
  ham.read(hamstr);
  spam.read(spamstr);
  hamstr.close();
  spamstr.close();
  cout << "...read\n";
  int hams = 0;
  int spams = 0;
  int total = 0;
  for (int i=4; i<argc; i++)
    {
      total++; 
      ifstream prstr(argv[i]);
      float hc = ham.score(prstr);
      prstr.close();
      ifstream pr2str(argv[i]);
      float sc = spam.score(pr2str);
      pr2str.close();
      // cout << "ham score: " << hc << "; spam score: " << sc << endl;
      if (hc>sc) 
	{ hams++; cout << "h" << flush; }
      else  
	{ spams++; cout << "s" << flush; }
    }
  cout << "\nTotal: " << total << " Ham: " << hams << " Spam: " << spams << endl;
}
