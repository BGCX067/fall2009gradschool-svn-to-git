%{
/*
  Puyan Lotfi
  CS6390
  Assignment 1: EBNF Parser
  Spencer Rugaber
*/
    
#include "ebnf.tab.h"
#include <cstring>

using namespace std;
%}

%%

"\n"+                     ;
(" "|"\t")+               ;

[a-zA-Z0-9_~#&,/:=<>]+     { yylval.str = strdup(yytext); return TEXT; }
['"]                      { yylval.str = strdup(yytext); return QUOTE; }
'\|'                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\('                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\)'                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\{'                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\}'                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\['                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\]'                     { yylval.str = strdup(yytext); return METACHARACTER; }
'\.'                     { yylval.str = strdup(yytext); return METACHARACTER; }
'->'                     { yylval.str = strdup(yytext); return METACHARACTER; }

\*                        { return KLEENESTAR; }
[+]                       { return PLUS; }
\|                        { return SEPARATOR; }
[.;]                      { return ENDOFPRODUCTION; }
[(]                       { return LPAREN; }
[)]                       { return RPAREN; }
[[{]                      { return LBRACKET; }
[]}]                      { return RBRACKET; }
->                        { return DEFINITION; }
