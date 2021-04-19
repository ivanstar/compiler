# lexical-syntax-analyzer

This program will stream in a text file containing syntax in C++, parse its contents and perform a series of lexical and syntactical analysis.

Lexical Analyzer Conventions
```
The lexical units of a program are identifiers, keywords, integers, reals, operators and other separators. 
Blanks, tabs and newlines  (collectively, "white space") as described below are ignored except 
as they serve to separate tokens. 
Some white space is required to separate otherwise adjacent identifiers, keywords, reals and integers.
<Identifier> is a sequence of letters and   “#”. 
The first character must be a letter and two consecutive #s are not allowed. 
Upper and lower cases are same. 
<Integer>  is an unsigned decimal integer i.e., a sequence of decimal digits.
<floating> is integer followed by “.”and integer, e.g., 123.00 
Some identifiers are reserved for use as keywords, and may not be used otherwise:
       e.g.,  int, if, else, fi,  while, return, read, write  etc
```
