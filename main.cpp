/*
  CPSC 323-03 - Project 2 - Syntatical Analyzer
  By : Ivan Tu
  File : main.cpp

	This main.cpp file contains function definitions for a syntatical analyzer. This program uitilizes std
	library list as a data storage mechanism. The program will take in an input file and parses into a list std library
	along with its corresponding value. If the syntax is correct it will output each production rule used to generate it

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
#include "analyze.h"
using namespace std;

//Declare std library list for data storage
list <string> result;

/* Prototype Syntatical Declarations */
bool statement(analyze &list);
bool declaritive(analyze &list);
bool type(analyze &list);
bool id(analyze &list);
bool moreIDs(analyze &list);
bool term(analyze &list);
bool factor(analyze &list);
bool num(analyze &list);
bool relop(analyze &list);
bool condition(analyze &list);
bool assign(analyze &list);
bool expression(analyze &list);
char copych(string);


int main()
{

  //Welcome/Description Message
  string phrase;
  cout << "This program will take in a file and perform syntatical analysis on the file." << endl;
  cout << "Enter the text file name to perform syntatical analyzer: ";
  cin >> phrase;


  //Declare file streaming for taking in a file
  ifstream inFile;
  inFile.open(phrase);

	//Check if the file is able to open.
	//If it does execute file processing otherwiset throw error handling
  if(inFile.is_open()){
    analyze analyze(inFile);

		//Loop through the list until the end
    while (analyze.begin().first != END){
      if(statement(analyze))
      {
				cout << endl;
        analyze.print();
				cout << endl;
        for(string syntax : result)
        {
          cout << syntax << endl;
        }
      }
      else
      {
				//Error handle for syntax that are not correct
        cout << "Error in Syntax" << endl;
        break;
      }
    }

		inFile.close();
  }
  else{
    //Error handling message for file that are not able to open
    cout << "Failed to open file..." << endl;
    cout <<  "Please make sure the filename is correct along with the extension e.g - filename.txt" << endl;
  }
 }


//Function to capture string
char copych(string str)
{
  char ch(0);
  if (str.size() > 1)
  {
    return 0;
  }
  str.copy(&ch, str.size());
  return ch;
}

//Function for checking ID - syntax
bool id(analyze &list)
{
	if (list.begin().first == IDENTIFIER)
	{
		result.push_front("<Identifier> -> id");
		list.getNext();
		return true;
	}
	return false;
}

//Function for additional IDs - syntax
bool moreIDs(analyze &list)
{
	if (copych(list.begin().second) == ',' && list.moveOneFor() && id(list) && moreIDs(list))
	{
		result.push_front("<MoreID> -> , <Identifier> <MoreID>");
		return true;
	}
	result.push_front("<MoreID> -> empty");
	return true;
}

//Function for type - syntax
bool type(analyze &list)
{
	auto pos = list.begin();
	if (pos.first == KEYWORD)
	{
		if (pos.second.compare("int") == 0 || pos.second.compare("float") == 0 || pos.second.compare("bool") == 0)
		{
			result.push_front("<Type> -> bool | int | float");
			list.getNext();
			return true;
		}
	}

	return false;
}
//Function for Number - syntax
bool num(analyze &list)
{
	if (list.begin().first == INTEGER)
	{
		result.push_front("<Num> -> num");
		list.getNext();
		return true;
	}
	if (list.begin().first == KEYWORD && list.begin().second.compare("true") == 0)
	{
		result.push_front("<Num> -> true");
		list.getNext();
		return true;
	}

	if (list.begin().first == KEYWORD && list.begin().second.compare("false") == 0)
	{
		result.push_front("<Num> -> false");
		list.getNext();
		return true;
	}
	return false;
}

//Function for Factors - syntax
bool factor(analyze &list)
{
	if (id(list))
	{
		result.push_front("<Factor> -> <Identifier>");
		return true;
	}
	if (num(list))
	{
		result.push_front("<Factor> -> <Num>");
		return true;
	}

	if (list.begin().first == SEPERATOR && copych(list.begin().second) == '(' && list.moveOneFor() && expression(list) && copych(list.begin().second) == '(' && list.moveOneFor())
	{
		result.push_front("<Factor> -> ( <Expression> )");
		return true;
	}
	return false;
}

//Function for Terms - syntax
bool term(analyze &list)
{
	bool factorTerm = factor(list);
	if (factorTerm)
	{
		result.push_front("<Term> -> <Factor>");
		return true;
	}

	if (factorTerm &&copych(list.begin().second) == '*' && list.moveOneFor() && factor(list))
		{
			result.push_front("<Term> -> <Factor> * <Factor>");
			return true;
		}

	if (factorTerm && copych(list.begin().second) == '/' && list.moveOneFor() && factor(list))
	{
		result.push_front("<Term> -> <Factor> / <Factor>");
		return true;
	}
	return false;
}

//Function for Conditionals - syntax
bool condition(analyze &list)
{
	bool conditionalExpr = expression(list);
	if (conditionalExpr && relop(list) && expression(list))
	{
		result.push_front("<Conditional> -> <Expression> <Relop> <Expression>");
		return true;
	}
	if (conditionalExpr)
	{
		result.push_front("<Conditional> -> <Expression>");
		return true;
	}
	return false;
}

//Function for Relop - syntax
bool relop(analyze &list)
{
	//Check if < is followed by =
	if (copych(list.begin().second) == '<')
	{
		list.getNext();
		if (copych(list.begin().second) == '=')
		{
			result.push_front("<Relop> -> <=");
			list.getNext();
			return true;
		}

		result.push_front("<Relop> -> <");
		return true;
	}

	///Check if >is followed by =
	if (copych(list.begin().second) == '>')
	{
		list.getNext();
		if (copych(list.begin().second) == '=')
		{
			result.push_front("<Relop> -> >=");
			list.getNext();
			return true;
		}
		result.push_front("<Relop> -> >");
		return true;
	}

	//Check if ! is followed by =
	if (copych(list.begin().second) == '!' && copych(list.peek().second) == '=')
	{
		result.push_front("<Relop> -> !=");
		list.getNext();
		list.getNext();
	}

	//Check if = is followed by =
	if (copych(list.begin().second) == '=' && copych(list.peek().second) == '=')
	{
		result.push_front("<Relop> -> !=");
		list.getNext();
		list.getNext();
	}

	return false;
}

//Function for Expressions - syntax
bool expression(analyze &list)
{
	bool termExpr = term(list);

	if (termExpr && copych(list.begin().second) == '+' && list.moveOneFor() && term(list))
	{
		result.push_front("<Expression> -> <Term> + <Term>");
		return true;
	}

	if (termExpr && copych(list.begin().second) == '-' && list.moveOneFor() && term(list))
	{
		result.push_front("<Expression> -> <Term> - <Term>");
		return true;
	}

	if (termExpr)
	{
		result.push_front("<Expression> -> <Term>");
		return true;
	}

	return false;
}

//Function for Assignments - syntax
bool assign(analyze &list)
{
	if (id(list) && copych(list.begin().second) == '=' && list.moveOneFor() && expression(list) && copych(list.begin().second) == ';' && list.moveOneFor())
	{
		result.push_front("<Assign> -> <Identifier> = <Expression> ;");
		return true;
	}

	list.reset();
	return false;
}

//Function for Declaratives - syntax
bool declaritive(analyze &list)
{
	if (type(list) && id(list) && moreIDs(list) && copych(list.begin().second) == ';' && list.moveOneFor())
	{
		result.push_front("<Declarative> -> <Type> <Identifier> <MoreID> ;");
		return true;
	}

	if (!result.empty() && *result.begin() == "<MoreID> -> empty")
	{
		result.pop_front();
	}
	if (!result.empty() && *result.begin() == "<Identifier> -> id")
	{
		result.pop_front();
	}
	if (!result.empty() && *result.begin() == "<Type> -> bool | int | float")
	{
		result.pop_front();
	}
	list.reset();

	if (type(list) && assign(list))
	{
		result.push_front("<Declarative> -> <Type> <Assign>");
		return true;
	}

	list.reset();
	return false;
}

//Function for Statements - syntax
bool statement(analyze &list)
{
	if (declaritive(list))
	{
		result.push_front("<Statement> -> <Declarative>");
		return true;
	}

	if (assign(list))
	{
		result.push_front("<Statment> -> <Assign>");
		return true;
	}

	if (list.begin().second.compare("if") == 0 && list.moveOneFor() && list.begin().second.compare("(") == 0 && list.moveOneFor() && condition(list) && list.begin().second.compare(")") == 0 && list.moveOneFor() && list.begin().second.compare("then") == 0 && list.moveOneFor())
	{
		cout << endl;
		list.print();
		if (statement(list) && list.begin().second.compare("else") == 0 && list.moveOneFor())
		{
			list.print();
			if (statement(list) && list.begin().second.compare("endif") == 0 && list.moveOneFor())
			{
				result.push_front("<Statment> -> if( <Conditional> )then <Statment> else <Statement> endif");
				return true;
			}
		}
	}

	if (list.begin().second.compare("while") == 0 && list.moveOneFor() && list.begin().second.compare("(") == 0 && list.moveOneFor() && condition(list) && list.begin().second.compare(")") == 0 && list.moveOneFor() && list.begin().second.compare("do") == 0 && list.moveOneFor())
	{
		cout << endl;
		list.print();
		if (statement(list) && list.begin().second.compare("whileend") == 0 && list.moveOneFor())
		{
			result.push_front("<Statment> -> while( <Conditional> )do <Statement> whileend");
			return true;
		}
	}

	return false;
}
