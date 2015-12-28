%{

/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#include <iostream>
#include <string>
#include <sstream>

#include "IParseTreeNode.h"
#include "ParseTreeNode.h"
#include "StringNode.h"
#include "NameNode.h"
#include "NumberNode.h"
    
using namespace std;

void yyerror(char *);
int yylex();

int lineNumber = 1;

IParseTreeNode* currentParseTree = NULL;
    
#define DEBUGMODE 0
#define BUSTEDMODE 0

#if DEBUGMODE

#define DEBUG_OUTPUT(str) \
    do { \
        cout << __LINE__  << "     " << str << endl; \
    } while (false)

#if BUSTEDMODE
#define DEBUG_OUTPUT_BUSTED(str) \
    do { \
        cout << str << " line number: " << __LINE__  << endl; \
    } while (false)
#else

#define DEBUG_OUTPUT_BUSTED(str) \
    do { \
    } while (false)

#endif

#else

#define DEBUG_OUTPUT(str) \
    do { \
    } while (false)
    
#define DEBUG_OUTPUT_BUSTED(str) \
    do { \
    } while (false)

#endif

%}

%union
{
    float val;
    char* str;
    IParseTreeNode* parseTreeNode;
}

%token KEYW_DO
%token KEYW_END
%token KEYW_WHILE
%token KEYW_IF
%token KEYW_THEN
%token KEYW_FUNC
%token KEYW_REPEAT
%token KEYW_UNTIL
%token KEYW_ELSEIF
%token KEYW_ELSE
%token KEYW_LOCAL
%token KEYW_RETURN
%token KEYW_BREAK
%token KEYW_FOR
%token KEYW_IN
%token DOT
%token COMMA
%token COLON
%token SEMICOLON
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE
%token LPAREN
%token RPAREN
%token NILVAL
%token FALSEVAL
%token TRUEVAL
%token PLUS
%token MINUS
%token MULTPLY
%token DIVIDE
%token POWER
%token MODULO
%token CONCAT
%token LESSTHAN
%token LESSTHANOREQUAL
%token GREATERTHAN
%token GREATERTHANOREQUAL
%token EQUALITY
%token INEQUALITY
%token AND
%token OR
%token NEGATIVE
%token NOT
%token POUND
%token DQUOTE
%token ASSIGNMENT
%token VARARGS


%type <parseTreeNode> chunk
%type <parseTreeNode> block
%type <parseTreeNode> stat
%type <parseTreeNode> elsestatement
%type <parseTreeNode> laststat
%type <parseTreeNode> funcname
%type <parseTreeNode> varlist
%type <parseTreeNode> var
%type <parseTreeNode> namelist
%type <parseTreeNode> explist
%type <parseTreeNode> exp
%type <parseTreeNode> prefixexp
%type <parseTreeNode> functioncall
%type <parseTreeNode> args
%type <parseTreeNode> function
%type <parseTreeNode> funcbody
%type <parseTreeNode> parlist
%type <parseTreeNode> tableconstructor
%type <parseTreeNode> fieldlist
%type <parseTreeNode> field
%type <parseTreeNode> fieldsep
%type <parseTreeNode> binop
%type <parseTreeNode> unop
%type <parseTreeNode> Name
%type <parseTreeNode> String

%token <val> NUMBER
%token <str> TEXT

%start chunk

%%

chunk:
stat
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 1");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| stat SEMICOLON
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 2");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(";", $1->getLineNumber(), true));
    currentParseTree = node;
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| stat chunk
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 3");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| stat SEMICOLON chunk
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 4");
     IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(";", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| chunk laststat
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 5");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| chunk laststat SEMICOLON
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 6");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode(";", $1->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| laststat
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 5");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| laststat SEMICOLON
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 6");
    IParseTreeNode* node = new ParseTreeNode("chunk", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(";", $1->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

block:
chunk
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO block 1");
    IParseTreeNode* node = new ParseTreeNode("block", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

stat:
varlist ASSIGNMENT explist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 1");
    IParseTreeNode* node = new ParseTreeNode("stat", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode("=", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| functioncall
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 2");
    IParseTreeNode* node = new ParseTreeNode("stat", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_DO block KEYW_END
{   
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 3");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("do", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    node->addNodeRight(emb);    
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_WHILE exp KEYW_DO block KEYW_END
{   
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 4");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("while", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    emb->addNodeRight(new ParseTreeNode("do", $2->getLineNumber(), true));
    emb->addNodeRight($4);
    node->addNodeRight(emb);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_REPEAT block KEYW_UNTIL exp
{   
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 5");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("repeat", $2->getLineNumber(), true));
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode("until", $2->getLineNumber(), true));
    node->addNodeRight($4);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_IF exp KEYW_THEN block KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 6");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("if", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    emb->addNodeRight(new ParseTreeNode("then", $2->getLineNumber(), true)); 
    emb->addNodeRight($4);
    node->addNodeRight(emb);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_IF exp KEYW_THEN block elsestatement KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 7");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("if", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    emb->addNodeRight(new ParseTreeNode("then", $2->getLineNumber(), true));
    emb->addNodeRight($4);
    emb->addNodeRight($5);
    node->addNodeRight(emb);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_FOR Name ASSIGNMENT exp COMMA exp COMMA exp KEYW_DO block KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 8");    
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("for", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    emb->addNodeRight(new ParseTreeNode("=", $2->getLineNumber(), true));
    emb->addNodeRight($4);
    emb->addNodeRight(new ParseTreeNode(",", $2->getLineNumber(), true));
    emb->addNodeRight($6);
    emb->addNodeRight(new ParseTreeNode(",", $2->getLineNumber(), true));
    emb->addNodeRight($8);
    emb->addNodeRight(new ParseTreeNode("do", $2->getLineNumber(), true));
    emb->addNodeRight($10);
    node->addNodeRight(emb);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_FOR Name ASSIGNMENT exp COMMA exp KEYW_DO block KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 9");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("for", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    emb->addNodeRight(new ParseTreeNode("=", $2->getLineNumber(), true));
    emb->addNodeRight($4);
    emb->addNodeRight(new ParseTreeNode(",", $2->getLineNumber(), true));
    emb->addNodeRight($6);
    emb->addNodeRight(new ParseTreeNode("do", $2->getLineNumber(), true));
    emb->addNodeRight($8);
    node->addNodeRight(emb);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_FOR namelist KEYW_IN explist KEYW_DO block KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 10");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("for", $2->getLineNumber(), true);
    emb->addNodeRight($2);
    emb->addNodeRight(new ParseTreeNode("in", $2->getLineNumber(), true));
    emb->addNodeRight($4);
    emb->addNodeRight(new ParseTreeNode("do", $2->getLineNumber(), true));
    emb->addNodeRight($6);
    node->addNodeRight(emb);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_FUNC funcname funcbody
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 11");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("function", $2->getLineNumber(), true));
    node->addNodeRight($2);
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_LOCAL KEYW_FUNC Name funcbody
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 12");
    IParseTreeNode* node = new ParseTreeNode("stat", $3->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("local", $3->getLineNumber(), true));
    node->addNodeRight(new ParseTreeNode("function", $3->getLineNumber(), true));
    node->addNodeRight($3);
    node->addNodeRight($4);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_LOCAL namelist ASSIGNMENT explist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 13");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("local", $2->getLineNumber(), true));
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode("=", $2->getLineNumber(), true));
    node->addNodeRight($4);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_LOCAL namelist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 13");
    IParseTreeNode* node = new ParseTreeNode("stat", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("local", $2->getLineNumber(), true));
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

elsestatement:
KEYW_ELSEIF exp KEYW_THEN block
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO elsestatement 1");
    IParseTreeNode* node = new ParseTreeNode("elseif", $2->getLineNumber(), true);
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode("then", $2->getLineNumber(), true));
    node->addNodeRight($4);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_ELSEIF exp KEYW_THEN block elsestatement
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO elsestatement 1");
    IParseTreeNode* node = new ParseTreeNode("elseif", $2->getLineNumber(), true);
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode("then", $2->getLineNumber(), true));
    node->addNodeRight($4);
    node->addNodeRight($5);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_ELSE block
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO elsestatement 2");
    IParseTreeNode* node = new ParseTreeNode("else", $2->getLineNumber(), true);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

laststat:
KEYW_RETURN
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO laststat 1");
    IParseTreeNode* node = new ParseTreeNode("laststat", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("return", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_RETURN explist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO laststat 2");
    IParseTreeNode* node = new ParseTreeNode("laststat", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("return", $2->getLineNumber(), true));
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| KEYW_BREAK
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO laststat 3");
    IParseTreeNode* node = new ParseTreeNode("laststat", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("break", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

funcname:
Name
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcname 1");
    IParseTreeNode* node = new ParseTreeNode("funcname", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| funcname COMMA Name
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcname 2");
    IParseTreeNode* node = new ParseTreeNode("funcname", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(",", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| funcname COLON Name
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcname 3");
    IParseTreeNode* node = new ParseTreeNode("funcname", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(":", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

varlist:
var
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO varlist 1");
    IParseTreeNode* node = new ParseTreeNode("varlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| var COMMA varlist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO varlist 2");
    IParseTreeNode* node = new ParseTreeNode("varlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(",", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

var:
Name
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO var 1");
    IParseTreeNode* node = new ParseTreeNode("var", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| prefixexp LBRACKET exp RBRACKET
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO var 2");
    IParseTreeNode* node = new ParseTreeNode("var", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode("[", $1->getLineNumber(), true));
    node->addNodeRight($3);
    node->addNodeRight(new ParseTreeNode("]", $1->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| prefixexp DOT Name
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO var 3");
    IParseTreeNode* node = new ParseTreeNode("var", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(".", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

namelist:
Name
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO namelist 1");
    IParseTreeNode* node = new ParseTreeNode("namelist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| Name COMMA namelist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO namelist 2");
    IParseTreeNode* node = new ParseTreeNode("namelist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(",", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

explist:
explist COMMA exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO explist 1");
    IParseTreeNode* node = new ParseTreeNode("explist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(",", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO explist 2");
    IParseTreeNode* node = new ParseTreeNode("explist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

exp:
NILVAL
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 1");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("nil", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| FALSEVAL
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 2");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("false", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| TRUEVAL
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 3");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("true", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| NUMBER
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 4");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new NumberNode(lineNumber, $1));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| String
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 5");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| VARARGS
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 6");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("...", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| function
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 7");
    IParseTreeNode* node = new ParseTreeNode("exp", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| prefixexp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 8");
    IParseTreeNode* node = new ParseTreeNode("exp", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| tableconstructor
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 9");
    IParseTreeNode* node = new ParseTreeNode("exp", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| exp binop exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 10");
    IParseTreeNode* node = new ParseTreeNode("binop", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| unop exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 11");
    IParseTreeNode* node = new ParseTreeNode("unop", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

prefixexp:
var
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO prefixexp 1");
    IParseTreeNode* node = new ParseTreeNode("prefixexp", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| functioncall
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO prefixexp 2");
    IParseTreeNode* node = new ParseTreeNode("prefixexp", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| LPAREN exp RPAREN
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO prefixexp 3");
    IParseTreeNode* node = new ParseTreeNode("prefixexp", $2->getLineNumber(), false);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

functioncall:
prefixexp args
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO functioncall 1");
    IParseTreeNode* node = new ParseTreeNode("functioncall", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| prefixexp COLON Name args
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO functioncall 2");
    IParseTreeNode* node = new ParseTreeNode("functioncall", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(":", $1->getLineNumber(), true));
    node->addNodeRight($3);
    node->addNodeRight($4);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

args:
LPAREN RPAREN
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 1");
    //~ IParseTreeNode* node = new ParseTreeNode("args", lineNumber, false);
    //~ currentParseTree = node;
    //~ $$ = node;
    //~ DEBUG_OUTPUT($$->generateOutputFormat());
}
| LPAREN explist RPAREN
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 2");
    IParseTreeNode* node = new ParseTreeNode("args", $2->getLineNumber(), false);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| tableconstructor
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 3");
    IParseTreeNode* node = new ParseTreeNode("args", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| String
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 4");
    IParseTreeNode* node = new ParseTreeNode("args", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

function:
KEYW_FUNC funcbody
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO function 1");
    IParseTreeNode* node = new ParseTreeNode("function", $2->getLineNumber(), false);
    node->addNodeRight($2);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

funcbody:
LPAREN RPAREN block KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 1");
    IParseTreeNode* node = new ParseTreeNode("funcbody", $3->getLineNumber(), false);
    // node->addNodeRight(new ParseTreeNode("(", $3->getLineNumber(), true));
    // node->addNodeRight(new ParseTreeNode(")", $3->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| LPAREN RPAREN KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 2");
    //~ IParseTreeNode* node = new ParseTreeNode("funcbody", lineNumber, false);
    //~ // node->addNodeRight(new ParseTreeNode("(", lineNumber, true));
    //~ // node->addNodeRight(new ParseTreeNode(")", lineNumber, true));
    //~ node->addNodeRight(new ParseTreeNode("end", lineNumber, true));
    //~ currentParseTree = node;
    //~ $$ = node;
    //~ DEBUG_OUTPUT($$->generateOutputFormat());
}
| LPAREN parlist RPAREN block KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 3");
    IParseTreeNode* node = new ParseTreeNode("funcbody", $2->getLineNumber(), false);
    // node->addNodeRight(new ParseTreeNode("(", $2->getLineNumber(), true));
    node->addNodeRight($2);
    // node->addNodeRight(new ParseTreeNode(")", $4->getLineNumber(), true));
    node->addNodeRight($4);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| LPAREN parlist RPAREN KEYW_END
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 4");
    IParseTreeNode* node = new ParseTreeNode("funcbody", $2->getLineNumber(), false);
    // node->addNodeRight(new ParseTreeNode("(", $2->getLineNumber(), true));
    node->addNodeRight($2);
    // node->addNodeRight(new ParseTreeNode(")", $2->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

parlist:
namelist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 1");
    IParseTreeNode* node = new ParseTreeNode("parlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| namelist COMMA
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 2");
    IParseTreeNode* node = new ParseTreeNode("parlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode(",", $1->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| namelist VARARGS
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 3");
    IParseTreeNode* node = new ParseTreeNode("parlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode("...", $1->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| VARARGS
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 4");
    IParseTreeNode* node = new ParseTreeNode("parlist", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("...", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

tableconstructor:
LBRACE RBRACE
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO tableconstructor 1");
    IParseTreeNode* node = new ParseTreeNode("tableconstructor", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("{", lineNumber, true));
    node->addNodeRight(new ParseTreeNode("}", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| LBRACE fieldlist RBRACE
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO tableconstructor 2");
    IParseTreeNode* node = new ParseTreeNode("tableconstructor", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("{", $2->getLineNumber(), true));
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode("}", $2->getLineNumber(), true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

fieldlist:
field
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldlist 1");
    IParseTreeNode* node = new ParseTreeNode("fieldlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| field fieldsep fieldlist
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldlist 2");
    IParseTreeNode* node = new ParseTreeNode("fieldlist", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight($2);
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

field:
LBRACKET exp RBRACKET ASSIGNMENT exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO field 1");
    IParseTreeNode* node = new ParseTreeNode("field", $2->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("[", $2->getLineNumber(), true));
    node->addNodeRight($2);
    node->addNodeRight(new ParseTreeNode("]", $2->getLineNumber(), true));
    node->addNodeRight(new ParseTreeNode("=", $2->getLineNumber(), true));
    node->addNodeRight($5);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| Name ASSIGNMENT exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO field 2");
    IParseTreeNode* node = new ParseTreeNode("field", $1->getLineNumber(), false);
    node->addNodeRight($1);
    node->addNodeRight(new ParseTreeNode("=", $1->getLineNumber(), true));
    node->addNodeRight($3);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| exp
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO field 3");
    IParseTreeNode* node = new ParseTreeNode("field", $1->getLineNumber(), false);
    node->addNodeRight($1);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

fieldsep:
COMMA
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldsep 1");
    IParseTreeNode* node = new ParseTreeNode("fieldsep", lineNumber, false);
    node->addNodeRight(new ParseTreeNode(",", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| SEMICOLON
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldsep 2");
    IParseTreeNode* node = new ParseTreeNode("fieldsep", lineNumber, false);
    node->addNodeRight(new ParseTreeNode(";", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

binop:
PLUS
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("+", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| MINUS
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("-", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| MULTPLY
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 3");
    IParseTreeNode* node = new ParseTreeNode("*", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| DIVIDE
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("/", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| POWER
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("^", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| MODULO
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("%", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| CONCAT
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("..", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| LESSTHAN
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("<", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| LESSTHANOREQUAL
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("<=", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| GREATERTHAN
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode(">", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| GREATERTHANOREQUAL
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode(">=", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| EQUALITY
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("==", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| INEQUALITY
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("~=", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| AND
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("and", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| OR
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("or", lineNumber, true);
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};


unop:
NEGATIVE
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO unop 1");
    IParseTreeNode* node = new ParseTreeNode("unop", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("-", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| NOT
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO unop 1");
    IParseTreeNode* node = new ParseTreeNode("unop", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("not", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
}
| POUND
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO unop 1");
    IParseTreeNode* node = new ParseTreeNode("unop", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("#", lineNumber, true));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

Name:
TEXT
{
    // TODO: Test that it isn't a reserved word.
    DEBUG_OUTPUT_BUSTED("JUMPED TO Name 1");
    IParseTreeNode* node = new NameNode(lineNumber, string($1));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};

String:
DQUOTE TEXT DQUOTE
{
    DEBUG_OUTPUT_BUSTED("JUMPED TO String 1");
    IParseTreeNode* node = new StringNode(lineNumber, string($2));
    currentParseTree = node;
    $$ = node;
    DEBUG_OUTPUT($$->generateOutputFormat());
};
