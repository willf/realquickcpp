CC = g++
CFLAGS = -Wall -g

all:	ilearn hamspam

UnigramTextClassifier.o:	UnigramTextClassifier.h UnigramTextClassifier.cpp
	$(CC) $(CFLAGS) -c UnigramTextClassifier.cpp

ilearn:	UnigramTextClassifier.o ilearn.cpp
	$(CC) $(CFLAGS) UnigramTextClassifier.o ilearn.cpp -o ilearn

hamspam:	UnigramTextClassifier.o hamspam.cpp
	$(CC) $(CFLAGS) UnigramTextClassifier.o hamspam.cpp -o hamspam

clean:
	rm -f core *.o *~

doc:	UnigramTextClassifier.h doxygen.cfg
	doxygen doxygen.cfg