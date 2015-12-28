
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KEYW_DO = 258,
     KEYW_END = 259,
     KEYW_WHILE = 260,
     KEYW_IF = 261,
     KEYW_THEN = 262,
     KEYW_FUNC = 263,
     KEYW_REPEAT = 264,
     KEYW_UNTIL = 265,
     KEYW_ELSEIF = 266,
     KEYW_ELSE = 267,
     KEYW_LOCAL = 268,
     KEYW_RETURN = 269,
     KEYW_BREAK = 270,
     KEYW_FOR = 271,
     KEYW_IN = 272,
     DOT = 273,
     COMMA = 274,
     COLON = 275,
     SEMICOLON = 276,
     LBRACKET = 277,
     RBRACKET = 278,
     LBRACE = 279,
     RBRACE = 280,
     LPAREN = 281,
     RPAREN = 282,
     NILVAL = 283,
     FALSEVAL = 284,
     TRUEVAL = 285,
     PLUS = 286,
     MINUS = 287,
     MULTPLY = 288,
     DIVIDE = 289,
     POWER = 290,
     MODULO = 291,
     CONCAT = 292,
     LESSTHAN = 293,
     LESSTHANOREQUAL = 294,
     GREATERTHAN = 295,
     GREATERTHANOREQUAL = 296,
     EQUALITY = 297,
     INEQUALITY = 298,
     AND = 299,
     OR = 300,
     NEGATIVE = 301,
     NOT = 302,
     POUND = 303,
     DQUOTE = 304,
     ASSIGNMENT = 305,
     VARARGS = 306,
     NUMBER = 307,
     TEXT = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 67 "luatfi.y"

    float val;
    char* str;
    IParseTreeNode* parseTreeNode;



/* Line 1676 of yacc.c  */
#line 113 "luatfi.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


