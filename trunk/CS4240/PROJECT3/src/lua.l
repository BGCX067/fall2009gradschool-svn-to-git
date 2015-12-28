/****************************************************/
/* File: lua.l                                      */
/* Lex specification for LUA                        */
/* Haicheng                                         */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
//char b4TokenString[MAXTOKENLEN+1];
char nameTokenString[MAXTOKENLEN+1];
char numTokenString[MAXTOKENLEN+1];
char stringTokenString[MAXTOKENLEN+1];
#define next() (current = input())
#define save_and_next(c) (save(c), next())
#define currIsNewline()	(current == '\n' || current == '\r')
#define copy()  strncpy(tokenString,yytext,MAXTOKENLEN)

%}

digit       [0-9]
decimal     {digit}*("."{digit}+)?([eE][-+]?{digit}+)?
hexadecimal 0x[0-9a-fA-F]+
letter      [a-zA-Z]
name        ({letter}|"_")+({letter}|{digit}|"_")*
newline     \n
whitespace  [ \t]+

%%

"and"           {copy(); return AND;}
"break"         {copy(); return BREAK;}
"do"            {copy(); return DO;}
"else"          {copy(); return ELSE;}
"elseif"        {copy(); return ELSEIF;}
"end"           {copy(); return END;}
"false"         {copy(); return False;}
"for"           {copy(); return FOR;}
"function"      {copy(); return FUNCTION;}
"if"            {copy(); return IF;}
"in"            {copy(); return IN;}
"local"         {copy(); return LOCAL;}
"nil"           {copy(); return NIL;}
"not"           {copy(); return NOT;}
"or"            {copy(); return OR;}
"repeat"        {copy(); return REPEAT;}
"return"        {copy(); return RETURN;}
"then"          {copy(); return THEN;}
"true"          {copy(); return True;}
"until"         {copy(); return UNTIL;}
"while"         {copy(); return WHILE;}
"+"             {copy(); return PLUS;}
"-"             {copy(); return MINUS;}
"*"             {copy(); return TIMES;}
"/"             {copy(); return OVER;}
"%"             {copy(); return MOD;}
"^"             {copy(); return POW;}
"#"             {copy(); return POUND;}
"=="            {copy(); return EQ;}
"~="            {copy(); return NEQ;}
"<="            {copy(); return LE;}
">="            {copy(); return GE;}
"<"             {copy(); return LT;}
">"             {copy(); return GT;}
"="             {copy(); return ASSIGN;}
"("             {copy(); return LPAREN;}
")"             {copy(); return RPAREN;}
"{"             {copy(); return LCBRACK;}
"}"             {copy(); return RCBRACK;}
"["             {copy(); return LSBRACK;}
"]"             {copy(); return RSBRACK;}
";"             {copy(); return SEMI;}
":"             {copy(); return COLON;}
","             {copy(); return COMMA;}
"."             {copy(); return DOT;}
".."            {copy(); return DDOT;}
"..."           {copy(); return TDOT;}
{hexadecimal}   {copy(); return NUMBER;}
{decimal}       {copy(); return NUMBER;}
{name}          {copy(); return NAME;}
\"              {return read_string('\"');}
\'              {return read_string('\'');}
"[["            {return read_long_string(0);}
"[="            {int sep = skip_sep(1, '['); return read_long_string(sep);}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"--"            { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                  } while (c != '\n');
                  lineno++;
                }
"--[["          { read_long_string(0); }
"--[="          { int sep = skip_sep(1, '['); read_long_string(sep);}
.               {return ERROR;}

%%

void save (char c) {
  tokenString[strlen(tokenString)] = c;
}

int skip_sep (int count, int s) {
  char current;
  next();
  while (current == '=') {
    next();
    count++;
  }
  return (current == s) ? count : - 1;
}

int read_long_string(int sep) {
  char current;
  int cont = 0;
  (void)(cont);  /* avoid warnings when `cont' is not used */
  int i;
  memset(tokenString, '\0', MAXTOKENLEN);

  if (sep < 0)
    return ERROR;

  next();  /* skip 2nd `[' */

  if (currIsNewline())  /* string starts with a newline? */
  { lineno++;  /* skip it */
    next();
  }

  for (;;) {
    switch (current) {
      case EOF:
        return ERROR;
      case ']': {
        if ((cont = skip_sep(0, ']')) == sep) {
          goto endloop;
        }
        else {
          next();
          save(']');
          for( i = 0; i < cont; i++)
            save('=');
          save(']');
        }
        break;
      }
      case '\n':
      case '\r': {
        save('\n');
        next();
        lineno++;
        break;
      }
      default: {
        save_and_next(current);
      }
    }
  } endloop:

  return STRING;
}


int read_string (int del) {
  char current;
  memset(tokenString, '\0', MAXTOKENLEN);
  next();
  while (current != del) {
    switch (current) {
      case EOF:
      case '\n':
      case '\r':
        return ERROR;
      case '\\': {
        int c;
        next();  /* do not save the `\' */
        switch (current) {
          case 'a': c = '\a'; break;
          case 'b': c = '\b'; break;
          case 'f': c = '\f'; break;
          case 'n': c = '\n'; break;
          case 'r': c = '\r'; break;
          case 't': c = '\t'; break;
          case 'v': c = '\v'; break;
          case '\n':  /* go through */
          case '\r': save('\n'); lineno++; continue;
          case EOF: return ERROR;
          default: {
            if (!isdigit(current))
              save_and_next(current);  /* handles \\, \", \', and \? */
            else {  /* \xxx */
              int i = 0;
              c = 0;
              do {
                c = 10*c + (current-'0');
                next();
              } while (++i<3 && isdigit(current));
              if (c > 255)
                return ERROR;
              save(c);
            }
            continue;
          }
        }
        save_and_next(c);
        continue;
      }
      default:
        save_and_next(current);
    }
  }
  return STRING;
}

TokenType getToken(void)
{ TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();

  switch(currentToken)
  {  case STRING:
       strncpy(stringTokenString,tokenString,MAXTOKENLEN);
       break;
     case NAME:
       strncpy(nameTokenString,yytext,MAXTOKENLEN);
       strncpy(tokenString,yytext,MAXTOKENLEN);
       break;
     case NUMBER:
       strncpy(numTokenString,yytext,MAXTOKENLEN);
       strncpy(tokenString,yytext,MAXTOKENLEN);
       break;
     default:
       strncpy(tokenString,yytext,MAXTOKENLEN);
       break;
  }
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }

  return currentToken;
}
