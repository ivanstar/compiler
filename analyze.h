/*
  CPSC 323-03 - Project 2 - Syntatical Analyzer
  By : Ivan Tu
  File : analyze.h

  This header file contains class delcarations to in order to create an object. Three lexical
	definitions were used in project 1. Additionally, helper functions were implemented in order to
	be able to process units in the std list library.

*/
#define TYPE 0
#define SEPERATOR 1
#define OPERATOR 2
#define INTEGER 3
#define KEYWORD 4
#define IDENTIFIER 5
#define END 6

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <utility>
#include <iterator>

using namespace std;

class analyze {
private:
	list<pair<int, string>> list_stream;
	list<pair<int, string>>::iterator it;

public:
	analyze(ifstream &inFile);

	/*  Lexical Analysis Declaration*/
	bool isSeparator(char);
	bool isOperator(char);
	bool isKeyword(string);


	/* Helper Functions */
   void print();
   bool moveOneFor();
   void reset();
   pair<int, string> getNext();
   pair<int, string> begin();
   pair<int, string> peek();

};
