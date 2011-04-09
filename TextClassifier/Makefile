CC = g++
CFLAGS = -Wall -g

all:	ilearn hamspam	classify doc

TextClassifier.o:	TextClassifier.h TextClassifier.cpp
	$(CC) $(CFLAGS) -c TextClassifier.cpp

UnigramTextClassifier.o:	UnigramTextClassifier.h UnigramTextClassifier.cpp
	$(CC) $(CFLAGS) -c UnigramTextClassifier.cpp

NgramTextClassifier.o:	NgramTextClassifier.h NgramTextClassifier.cpp
	$(CC) $(CFLAGS) -c NgramTextClassifier.cpp

ilearn:	UnigramTextClassifier.o ilearn.cpp
	$(CC) $(CFLAGS) UnigramTextClassifier.o ilearn.cpp -o ilearn

ilearn2:	NgramTextClassifier.o ilearn.cpp
	$(CC) $(CFLAGS) NgramTextClassifier.o ilearn2.cpp -o ilearn2

hamspam:	UnigramTextClassifier.o hamspam.cpp
	$(CC) $(CFLAGS) UnigramTextClassifier.o hamspam.cpp -o hamspam

hamspam2:	NgramTextClassifier.o hamspam.cpp
	$(CC) $(CFLAGS) NgramTextClassifier.o hamspam.cpp -o hamspam2

classify:	UnigramTextClassifier.o classify.cpp
	$(CC) $(CFLAGS) UnigramTextClassifier.o classify.cpp -o classify

clean:
	rm -f core *.o *~

doc:	UnigramTextClassifier.h doxygen.cfg
	doxygen doxygen.cfg