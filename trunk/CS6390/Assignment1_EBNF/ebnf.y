%{

/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#include <iostream>
#include <string>

using namespace std;

void yyerror(char *);
int yylex();
%}

%union
{
    float val;
    char* str;
}

%token LPAREN RPAREN LBRACKET RBRACKET ENDOFPRODUCTION DEFINITION SEPARATOR PLUS KLEENESTAR

%token IDENTIFIER STRING

%token <str> LIDENTIFIER RIDENTIFIER QUOTE TEXT METACHARACTER

%type <str> ebnfstring nonterminal terminal expression production ebnfgrammar sequence

%start ebnfgrammar

%%

ebnfgrammar:
production ebnfgrammar
{
    $$ = $1;
}
|
;

production:
nonterminal DEFINITION expression ENDOFPRODUCTION
{
    string temp = string($1) + "->" + string($3) + string(".");
    cout << "production:   " << temp << endl;
    $$ = strdup((char*)temp.c_str());
}
|
;

expression:
sequence
{
    string temp = string($1);
    cout << "expression:   " << temp << endl << endl;
    $$ = strdup($1);
} 
| sequence SEPARATOR expression
{
    string temp = string($1) + string("|") + string($3);
    cout << "expression:   " << temp << endl << endl;
    $$ = strdup((char*)temp.c_str());
}
|
;

sequence:
terminal
{
    string temp = string($1);
    cout << "sequence:     " << temp << endl;
    $$ = strdup((char*)temp.c_str());
}
| terminal sequence
{
    string temp = string($1) + string(" ") + string($2);
    cout << "sequence:     " << temp << endl;
    $$ = strdup((char*)temp.c_str());
};

terminal:
nonterminal
{
    string temp = string($1);
    cout << "terminal:     " << temp << endl;
    $$ = strdup($1);
} 
| ebnfstring
{
    string temp = string($1);
    cout << "terminal:     " << temp << endl;
    $$ = strdup($1);
}
| LBRACKET expression RBRACKET
{
    string temp = string("[") + string($2) + string("]");
    cout << "terminal:     " << temp << endl;
    $$ = strdup((char*)temp.c_str());
}
| LPAREN expression RPAREN
{
    string temp = string("(") + string($2) + string(")");
    cout << "terminal:     " << temp << endl;
    $$ = strdup((char*)temp.c_str());
}
| terminal KLEENESTAR
{
    string temp = string($1) + string("*");
    cout << "terminal:     " << temp << endl;
    $$ = strdup((char*)temp.c_str());
}
| terminal PLUS
{
    string temp = string($1) + string("+");
    cout << "terminal:     " << temp << endl;
    $$ = strdup((char*)temp.c_str());    
};

nonterminal:
TEXT
{
    string temp = string($1);
    cout << "non-terminal: " << temp << endl;
    $$ = strdup($1);
};

ebnfstring:
QUOTE TEXT QUOTE
{
    if (string($1) != string($3))
    {
        cerr << "Invalid EBNF string: " << $2 << endl;
        exit(0);
    }

    string temp = string("'") + $2 + string("'");
    cout << "string:       " << temp << endl;
    $$ = strdup((char*)temp.c_str());
}
| METACHARACTER
{
    string temp = $1;
    cout << "string:       " << temp << endl;
    $$ = strdup((char*)temp.c_str());
};
