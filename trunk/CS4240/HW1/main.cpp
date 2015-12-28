/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "IParseTreeNode.h"

using namespace std;

#define YYYDEBUG 1

#ifdef YYDEBUG
extern int yydebug;
#endif

extern FILE* yyin;

extern IParseTreeNode* currentParseTree;

int yyparse();

int main(int argc, char** argv)
{
#ifdef YYDEBUG
    yydebug = 1;
#endif

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            char* filename = argv[i];
            if (yyin = fopen(filename, "r"))
            {
                cout << "File \"" << filename << "\" is being translated..." << endl;
                yyparse();
                fclose(yyin);
                
                char* extensionStart= strstr(filename, ".lua");
                string outfilename = "";
                
                if (NULL == extensionStart)
                {
                    outfilename = string(filename) + ".ast";
                }
                else
                {
                    ostringstream ost;
                    
                    for (char* p = filename; p != extensionStart; p++)
                    {
                        ost << *p;
                    }
                    
                    ost << ".ast";
                    
                    outfilename = ost.str();
                }
                
                cout << "Writing output to: \"" << outfilename << "\"." << endl << endl;
                
                ofstream outfile;
                outfile.open (outfilename.c_str());
                outfile << currentParseTree->generateOutputFormat();
                outfile.close();
                
            }
            else
            {
                cout << "File \"" << filename << "\" does not exist!" << endl << endl;
            }
        }
    }
    else
    {
        cout << "./luac file1.lua file2.lua ... filen.lua" << endl << endl;
    }
    
    
    return 0;
}

void yyerror (char* s)  /* Called by yyparse on error */
{
  cout << "yyparse error: " << s << endl;
  exit(1);
}

