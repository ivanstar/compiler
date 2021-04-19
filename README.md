# Compiler : lexical-syntax-analyzer

This compiler program utilizing Finite State Machines(FSM) and consists of a lexical analyzer, syntactical analyzer, and parser.  All of which takes C++ programming language and translates it into pseudo assembly code. The compiler reads the code from an external file (e.g. text file) and parses its contents from the file and translates it into assembly code.

It will verify if the external file has appropriate syntax and if ther are any syntax errors it will generate an error message. 

## Lexical Analyzer Conventions
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

## Syntactical Analyzer Rules
```
GRAMMAR	                     RULE
<Statement>	              <Declarative> | <Assignment> |
                                   if ( <Conditional> ) then <Statement> else <Statement> endif |
                            while ( <Conditional> ) do <Statement> whileend

<Declarative>	              <Type> <ID> <MoreID>; | <Type> <Assignment>
                            <Type>	int | float | bool
                            <ID>	id
                     
<Assignment>	              <ID> = <Expression>;

<Expression>	              <Term> + <Term> | <Term> - <Term> | <Term>

<Term>	                     <Factor> * <Factor> | <Factor> / <Factor> | <Factor>

<Factor>	              ( <Expression> ) | <ID> | <Num>

<Num>	                     number | true(1) | false(0)

<MoreID>	              , <ID> <MoreID> | empty

<Relop>	              < | > | <= | >= | == | !=

<Conditional> 	       <Expression> <Relop> <Expression> | <Expression>
```
