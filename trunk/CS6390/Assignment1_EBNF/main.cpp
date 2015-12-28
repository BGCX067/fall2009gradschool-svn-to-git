/*
  Puyan Lotfi
  CS6390
  Assignment 1: EBNF Parser
  Spencer Rugaber
*/

#include <iostream>
#include <cstdlib>

using namespace std;

#define YYYDEBUG 1

#ifdef YYDEBUG
extern int yydebug;
#endif

extern FILE* yyin;


int yyparse();

int main(int argc, char** argv)
{
#ifdef YYDEBUG
    yydebug = 1;
#endif

    if (argc > 1)
    {
        char* filename = argv[1];
        if (yyin = fopen(filename, "r"))
        {
            yyparse();
            fclose(yyin);
        }
        else
        {
            cout << "File \"" << filename << "\" does not exist." << endl;
            exit(1);
        }
    }
    else
    {
        yyparse();
    }
    
    
    
    
    return 0;
}

void yyerror (char* s)  /* Called by yyparse on error */
{
  cout << "yyparse error: " << s << endl;
  exit(1);
}

