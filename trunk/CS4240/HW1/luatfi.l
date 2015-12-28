%{
#include "IParseTreeNode.h"
#include "luatfi.tab.h"
#include <cstring>

using namespace std;

extern int lineNumber;
%}

%%

"\n"                { lineNumber++; }
(" "|"\t")+         ;
--.*\n              { lineNumber++; }

 /* keywords */
"do"                { return KEYW_DO; }
"end"               { return KEYW_END; }
"while"             { return KEYW_WHILE; }
"if"                { return KEYW_IF; }
"then"              { return KEYW_THEN; }
"function"          { return KEYW_FUNC; }
"repeat"            { return KEYW_REPEAT; }
"until"             { return KEYW_UNTIL; }
"elseif"            { return KEYW_ELSEIF; }
"else"              { return KEYW_ELSE; }
"local"             { return KEYW_LOCAL; }
"return"            { return KEYW_RETURN; }
"break"             { return KEYW_BREAK; }
"for"               { return KEYW_FOR; }
"in"                { return KEYW_IN; }

 /* punctuations */
"."                 { return DOT; }
","                 { return COMMA; }
":"                 { return COLON; }
";"                 { return SEMICOLON; }
"["                 { return LBRACKET; }
"]"                 { return RBRACKET; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }


 /* values */
"nil"               { return NILVAL; }
"false"             { return FALSEVAL; }
"true"              { return TRUEVAL; }

 /* binops */
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MULTPLY; }
"/"                 { return DIVIDE; }
"^"                 { return POWER; }
"%"                 { return MODULO; }
".."                { return CONCAT; }
"<"                 { return LESSTHAN; }
"<="                { return LESSTHANOREQUAL; }
">"                 { return GREATERTHAN; }
">="                { return GREATERTHANOREQUAL; }
"=="                { return EQUALITY; }
"~="                { return INEQUALITY; }
"-"                 { return NEGATIVE; }
"and"               { return AND; }
"or"                { return OR; }

 /* unops */
"not"               { return NOT; }
"#"                 { return POUND; }

 /* Other Operators */
"="                 { return ASSIGNMENT; }
"..."               { return VARARGS; }

 /* Other Regular Expressions */
[0-9]+(\.[0-9]+)?   { yylval.val = atof(yytext); return NUMBER; }
[a-zA-Z0-9]+        { yylval.str = strdup(yytext); return TEXT; }
\"                  { yylval.str = strdup(yytext); return DQUOTE; }


%%
