/*
  CPSC 323-03 - Project 2 - Syntatical Analyzer
  By : Ivan Tu
  File : analyze.cpp

  This analyze.cpp file defines all of the function definitions in the header file.
	The constructor will take in a file and parse it with a value to mimic a table reference

*/
#define TYPE 0
#define SEPERATOR 1
#define OPERATOR 2
#define INTEGER 3
#define KEYWORD 4
#define IDENTIFIER 5
#define END 6

#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <list>
#include "analyze.h"

using namespace std;

analyze::analyze(ifstream &inFile){

  //Variable to store current char being processed
  char currentChar;

  while(!inFile.eof()){

    currentChar = inFile.get(); //Process each individual char into variable current char

    //Condition to check if the current char is a space or end of file, if it is then skip through it
    if(isspace(currentChar) || inFile.eof() || currentChar == '\n' || currentChar == '\t'){
      continue;
    }

    //Condition to check if the current is a comment, if it is process until the last comment symbol and continue
    if(currentChar == '!'){
      do {
          currentChar = inFile.get();
         } while (currentChar != '!');
      currentChar = inFile.get();
      continue;
    }

    //Declare temp string variable to store/process vector
    string temp;
    temp.push_back(currentChar);

    //Condition to check if current is operator by using isOperator function.
    //Function returns true if it is otherwise false.
    //Function definition is defined below
		//Process the currentChar into a list <pair> format with std library for table reference
    if(isOperator(currentChar)){
      list_stream.push_back(pair<int, string>(OPERATOR, temp));
      continue;
    }

    //Condition to check if current is separator by using isSeparator function.
    //Function returns true if it is otherwise false.
      //Function definition is defined below
			//Process the currentChar into a list <pair> format with std library for table reference
    if(isSeparator(currentChar)){
      list_stream.push_back(pair<int, string>(SEPERATOR, temp));
      continue;
    }


    //Condition to check for integers
    if(isdigit(currentChar)){
      while (isdigit(inFile.peek())){
        currentChar = inFile.get();
        temp.push_back(currentChar);
      }
      //Print out the variable in the vector
      list_stream.push_back(pair<int, string>(INTEGER, temp));
      continue;

    }

    //Condition to check for keyword by checking if it is a digit or letter.
    //if it is push into the vector
    while(isalnum(inFile.peek()) || inFile.peek() == '$'){
      currentChar = inFile.get();
      temp.push_back(currentChar);
    }

    //Condition to check contents is a keyword or identifier by using a isKeyword function
    //Function returns true if it is a keyword otherwise it is an identifier.
      //Function definition is defined below
			//Process the currentChar into a list <pair> format with std library for table reference
    if(isKeyword(temp)){
      list_stream.push_back(pair<int, string>(KEYWORD, temp));
			continue;
    }
    else{
      list_stream.push_back(pair<int, string>(IDENTIFIER, temp));
    }
  } // End loop

  it = list_stream.begin();
  list_stream.push_back(pair<int, string>(END, "$ - END"));
}

//Check if variable passed in is a separator
//Returns true if it is a separator otherwise return false
bool analyze::isSeparator(char input){
  //SEPARATORS 	=	'(){}[],.:;
  bool flag = false;
  char separators[10] = { '(', ')', ';', '{' , '}','[',']', ',','.',':'};
  for(int i = 0; i < 10; i++){
    if (separators[i] == input){
      flag = true;
    }
  }
  return flag;
}

//Check if variable passed in is a operator
//Returns true if it is a operator otherwise return false
bool analyze::isOperator(char input){
  bool flag = false;
//  char operators[] = "=*+-/><%";
  char operators[8] = { '=', '*', '+','-', '/', '>', '<', '%'};
  for(int i = 0; i < 8; i++){
    if (operators[i] == input){
      flag = true;
    }
  }
  return flag;
}

//Check if variable passed in is a keyword
//Returns true if it is a keyword otherwise return false
bool analyze::isKeyword(string identifier){
  bool flag = false;
  string keywords[20] = { "int", "float", "bool", "true", "false", "if", "else",
                          "then", "endif","while", "whilened", "do", "doend", "for",
                          "forend", "input", "output", "and", "or", "not"
                        };
  for (int i = 0; i < 20;i++){
    if(keywords[i] == identifier){
      flag = true;
    }
  }
  return flag;
}

/****** Helper functions ********/

void analyze::print()
{
  while (it != list_stream.begin())
  {
		cout << list_stream.front().second << " ";
		list_stream.pop_front();
	}
}


pair<int, string> analyze::begin()
{
  return *it;
}

pair<int, string> analyze::getNext()
{
  if(it != list_stream.end())
  {
    advance(it,1);
    return *it;
  }
  return pair<int, string>(END,NULL);
}

pair<int, string> analyze::peek()
{
  if(it != list_stream.end())
  {
    return *next(it,1);
  }
  return pair<int, string>(END,NULL);
}

bool analyze::moveOneFor()
{
  if (it != list_stream.end())
  {
    advance(it,1);
  }
  return true;
}


void analyze::reset()
{
  it = list_stream.begin();
}
