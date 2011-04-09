#include <iostream>
#include "UnigramTextClassifier.h" 

using namespace std;
using namespace TextClassifier;

int main(int argc,char *argv[]) 
{ 
  UnigramTextClassifier ham = UnigramTextClassifier();
  UnigramTextClassifier spam = UnigramTextClassifier();
  ham.read(argv[1]);
  spam.read(argv[2]);
  int hams = 0;
  int spams = 0;
  int total = 0;
  for (int i=3; i<argc; i++)
    {
      total++; 
      if (ham.score(argv[i]) > spam.score(argv[i])) 
	hams++;
      else  
	spams++;
    }
  cout << "\nTotal: " << total << " Ham: " << hams << " Spam: " << spams << endl;
}
