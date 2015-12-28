%{
#include "aicop.tab.h"
#include <cstring>

using namespace std;

extern int lineNumber;
%}

%%

[a-zA-Z0-9\-\$]+        { yylval.str = strdup(yytext); return SYMBOL; }

"\n"                ;
"\r"                ;
(" "|"\t")+         ;

","                 { return COMMA; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }

%%
