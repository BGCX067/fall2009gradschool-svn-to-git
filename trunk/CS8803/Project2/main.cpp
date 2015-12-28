#include <iostream>
#include <list>
#include <utility>
#include <map>
#include <cstdlib>
#include <cstdio>
#include "frame.h"

using namespace std;

extern FILE* yyin;

int yyparse();

extern FrameRegistry GlobalFrameRegistry;
extern FrameRegistry GlobalPlanRegistry;
extern list<pair<string, string> > subplans;
extern Frame* currentParentFrame;

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            char* filename = argv[i];
            if ((yyin = fopen(filename, "r")))
            {
                cout << "File \"" << filename << "\" is being translated..." << endl;
                yyparse();
                fclose(yyin);
            }
        }
    }

    for (list<pair<string, string> >::iterator iter = subplans.begin();
         iter != subplans.end();
         iter++)
    {
        string filename = iter->second;
        currentParentFrame = GlobalPlanRegistry[iter->first].front();
        if ((yyin = fopen(filename.c_str(), "r")))
        {
            cout << "File \"" << filename << "\" is being translated..." << endl;
            yyparse();
            fclose(yyin);
        }
    }

    MatchPlansWithEvents();

    cout << endl << endl << endl << endl  << endl << "The End! And they lived happily ever after with Drugs, Death, and Destruction!" << endl << endl<< endl<< endl << endl;

    return 0;
}

void yyerror (char* s)  /* Called by yyparse on error */
{
  cout << "yyparse error: " << s << endl;
  exit(1);
}

