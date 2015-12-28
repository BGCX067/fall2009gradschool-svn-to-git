
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "luatfi.y"


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



/* Line 189 of yacc.c  */
#line 139 "luatfi.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 67 "luatfi.y"

    float val;
    char* str;
    IParseTreeNode* parseTreeNode;



/* Line 214 of yacc.c  */
#line 236 "luatfi.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 248 "luatfi.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   553

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    15,    18,    22,    24,
      27,    29,    33,    35,    39,    45,    50,    56,    63,    75,
      85,    93,    97,   102,   107,   110,   115,   121,   124,   126,
     129,   131,   133,   137,   141,   143,   147,   149,   154,   158,
     160,   164,   168,   170,   172,   174,   176,   178,   180,   182,
     184,   186,   188,   192,   195,   197,   199,   203,   206,   211,
     214,   218,   220,   222,   225,   230,   234,   240,   245,   247,
     250,   253,   255,   258,   262,   264,   268,   274,   278,   280,
     282,   284,   286,   288,   290,   292,   294,   296,   298,   300,
     302,   304,   306,   308,   310,   312,   314,   316,   318,   320,
     322
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    57,    -1,    57,    21,    -1,    57,    55,
      -1,    57,    21,    55,    -1,    55,    59,    -1,    55,    59,
      21,    -1,    59,    -1,    59,    21,    -1,    55,    -1,    61,
      50,    64,    -1,    67,    -1,     3,    56,     4,    -1,     5,
      65,     3,    56,     4,    -1,     9,    56,    10,    65,    -1,
       6,    65,     7,    56,     4,    -1,     6,    65,     7,    56,
      58,     4,    -1,    16,    78,    50,    65,    19,    65,    19,
      65,     3,    56,     4,    -1,    16,    78,    50,    65,    19,
      65,     3,    56,     4,    -1,    16,    63,    17,    64,     3,
      56,     4,    -1,     8,    60,    70,    -1,    13,     8,    78,
      70,    -1,    13,    63,    50,    64,    -1,    13,    63,    -1,
      11,    65,     7,    56,    -1,    11,    65,     7,    56,    58,
      -1,    12,    56,    -1,    14,    -1,    14,    64,    -1,    15,
      -1,    78,    -1,    60,    19,    78,    -1,    60,    20,    78,
      -1,    62,    -1,    62,    19,    61,    -1,    78,    -1,    66,
      22,    65,    23,    -1,    66,    18,    78,    -1,    78,    -1,
      78,    19,    63,    -1,    64,    19,    65,    -1,    65,    -1,
      28,    -1,    29,    -1,    30,    -1,    52,    -1,    79,    -1,
      51,    -1,    69,    -1,    66,    -1,    72,    -1,    65,    76,
      65,    -1,    77,    65,    -1,    62,    -1,    67,    -1,    26,
      65,    27,    -1,    66,    68,    -1,    66,    20,    78,    68,
      -1,    26,    27,    -1,    26,    64,    27,    -1,    72,    -1,
      79,    -1,     8,    70,    -1,    26,    27,    56,     4,    -1,
      26,    27,     4,    -1,    26,    71,    27,    56,     4,    -1,
      26,    71,    27,     4,    -1,    63,    -1,    63,    19,    -1,
      63,    51,    -1,    51,    -1,    24,    25,    -1,    24,    73,
      25,    -1,    74,    -1,    74,    75,    73,    -1,    22,    65,
      23,    50,    65,    -1,    78,    50,    65,    -1,    65,    -1,
      19,    -1,    21,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,
      53,    -1,    49,    53,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   158,   158,   168,   179,   189,   200,   210,   221,   230,
     242,   253,   264,   273,   284,   297,   309,   322,   336,   355,
     372,   387,   398,   410,   422,   434,   445,   457,   468,   477,
     487,   498,   507,   518,   531,   540,   553,   562,   574,   587,
     596,   609,   620,   631,   640,   649,   658,   667,   676,   685,
     694,   703,   712,   723,   735,   744,   753,   764,   774,   788,
     796,   805,   814,   825,   836,   847,   858,   870,   883,   892,
     902,   912,   923,   933,   946,   955,   968,   981,   992,  1003,
    1012,  1023,  1031,  1039,  1047,  1055,  1063,  1071,  1079,  1087,
    1095,  1103,  1111,  1119,  1127,  1135,  1146,  1155,  1164,  1175,
    1186
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYW_DO", "KEYW_END", "KEYW_WHILE",
  "KEYW_IF", "KEYW_THEN", "KEYW_FUNC", "KEYW_REPEAT", "KEYW_UNTIL",
  "KEYW_ELSEIF", "KEYW_ELSE", "KEYW_LOCAL", "KEYW_RETURN", "KEYW_BREAK",
  "KEYW_FOR", "KEYW_IN", "DOT", "COMMA", "COLON", "SEMICOLON", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "NILVAL", "FALSEVAL",
  "TRUEVAL", "PLUS", "MINUS", "MULTPLY", "DIVIDE", "POWER", "MODULO",
  "CONCAT", "LESSTHAN", "LESSTHANOREQUAL", "GREATERTHAN",
  "GREATERTHANOREQUAL", "EQUALITY", "INEQUALITY", "AND", "OR", "NEGATIVE",
  "NOT", "POUND", "DQUOTE", "ASSIGNMENT", "VARARGS", "NUMBER", "TEXT",
  "$accept", "chunk", "block", "stat", "elsestatement", "laststat",
  "funcname", "varlist", "var", "namelist", "explist", "exp", "prefixexp",
  "functioncall", "args", "function", "funcbody", "parlist",
  "tableconstructor", "fieldlist", "field", "fieldsep", "binop", "unop",
  "Name", "String", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    59,    59,
      59,    60,    60,    60,    61,    61,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    66,    67,    67,    68,
      68,    68,    68,    69,    70,    70,    70,    70,    71,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    74,    75,
      75,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    77,    78,
      79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     3,     2,     3,     1,     2,
       1,     3,     1,     3,     5,     4,     5,     6,    11,     9,
       7,     3,     4,     4,     2,     4,     5,     2,     1,     2,
       1,     1,     3,     3,     1,     3,     1,     4,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     1,     3,     2,     4,     2,
       3,     1,     1,     2,     4,     3,     5,     4,     1,     2,
       2,     1,     2,     3,     1,     3,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    28,    30,     0,
       0,    99,     0,     2,     8,     0,    54,     0,    12,    36,
      10,     0,     0,     0,    43,    44,    45,    96,    97,    98,
       0,    48,    46,    54,     0,    50,    55,    49,    51,     0,
      47,     0,     0,    31,     0,     0,    24,    39,    29,    42,
       0,    39,     0,     1,     6,     3,     4,     9,     0,     0,
       0,     0,     0,     0,    57,    61,    62,    13,     0,    63,
       0,    72,    78,     0,    74,    36,     0,     0,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,    53,     0,     0,     0,    21,     0,
       0,     0,     0,     0,     0,     0,    56,     7,     5,    11,
      35,    38,     0,     0,    59,     0,     0,    71,    68,     0,
       0,    73,    79,    80,     0,     0,   100,     0,    52,     0,
      32,    33,    15,    22,    23,    40,    41,     0,     0,    58,
      37,    60,    65,     0,    69,    70,     0,     0,    75,    77,
      14,    16,     0,     0,     0,     0,     0,    64,    67,     0,
       0,     0,    27,    17,     0,     0,    66,    76,     0,    20,
       0,     0,    25,     0,     0,    26,    19,     0,     0,    18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    13,   154,    14,    42,    15,    33,    46,
      48,    49,    35,    36,    64,    37,    69,   119,    38,    73,
      74,   124,    93,    39,    19,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -39
static const yytype_int16 yypact[] =
{
     253,   253,   303,   303,   -38,   253,    36,   303,   -39,   -38,
     303,   -39,   110,    20,    11,     4,     2,    68,   108,   -39,
     120,    53,    46,   256,   -39,   -39,   -39,   -39,   -39,   -39,
      22,   -39,   -39,   -39,   342,    68,   -39,   -39,   -39,   303,
     -39,   400,    59,   -39,    56,   -38,    70,    90,    99,   358,
     112,    32,   508,   -39,   106,   253,   120,   -39,   303,    -8,
     -38,   -38,   303,   246,   -39,   -39,   -39,   -39,    40,   -39,
     303,   -39,   358,   113,    83,    89,    91,   253,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   303,   358,   253,   -38,   -38,   -39,   303,
      46,   303,   -38,   303,   303,   303,   -39,   -39,   120,    99,
     -39,   -39,    50,   424,   -39,   114,    34,   -39,     5,   117,
     489,   -39,   -39,   -39,   288,   303,   -39,   143,   358,   102,
     -39,   -39,   358,   -39,    99,   -39,   358,    93,   466,   -39,
     -39,   -39,   -39,   146,   -39,   -39,   234,   101,   -39,   358,
     -39,   -39,   303,   253,   159,   253,   303,   -39,   -39,   161,
     303,   439,   -39,   -39,   163,   327,   -39,   358,   253,   -39,
     253,   303,   125,   165,   385,   -39,   -39,   253,   171,   -39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,    14,    26,   -39,    10,    -3,   -39,   119,     0,    13,
       7,    61,     3,     6,    75,   -39,   -32,   -39,   -15,    64,
     -39,   -39,   -39,   -39,   139,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -56
static const yytype_int16 yytable[] =
{
      16,    16,    65,    17,    17,    16,    18,    18,    17,    54,
      98,    18,    66,    16,    12,    11,    17,    54,    10,    18,
      65,    59,    50,     1,   144,     2,     3,    56,     4,     5,
      66,    44,    57,     6,     7,     8,     9,     1,   142,     2,
       3,    55,     4,     5,    45,    11,    10,     6,     7,     8,
       9,   102,   -34,    54,    58,    16,   145,    67,    17,    16,
      10,    18,    17,    34,    41,   109,    99,   116,   133,   108,
     115,    52,    68,    11,    23,    76,    63,    16,    96,    97,
      17,   118,   105,    18,    72,    68,    60,    11,    61,    11,
      62,   117,    23,    11,    63,    16,   155,    65,    17,    30,
      94,    18,   122,   127,   123,    54,   151,    66,   134,   102,
      53,   137,   103,   152,   153,   135,    16,    30,   103,    17,
     101,   129,    18,   113,     7,     8,   -55,   107,   -55,   104,
     -55,   120,   -55,   103,     7,     8,   152,   153,   121,   125,
     126,   141,   143,    43,   146,    47,    16,   150,    51,    17,
     157,   160,    18,    16,   128,    16,    17,   -55,    17,    18,
     132,    18,    75,   163,   136,   166,   138,   169,    16,   176,
      16,    17,   159,    17,    18,   179,    18,    16,   110,   162,
      17,   164,   175,    18,   100,    72,   149,   139,   148,     0,
       0,     0,     0,     0,   172,     0,   173,     0,     0,   111,
     112,     0,     0,   178,     0,     0,     0,    47,     0,     0,
       0,     0,     0,   161,     0,     0,     0,   165,     0,     0,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,     0,     0,   130,   131,     1,   158,     2,
       3,    47,     4,     5,     0,     0,     0,     6,     7,     8,
       9,     0,     0,     0,    22,     0,     1,     0,     2,     3,
      10,     4,     5,    75,    22,     0,     6,     7,     8,     9,
      23,     0,    10,   114,    24,    25,    26,     0,    70,    10,
      23,    71,    10,     0,    24,    25,    26,    11,     0,     0,
       0,     0,    27,    28,    29,    30,    22,    31,    32,    11,
       0,     0,    27,    28,    29,    30,    11,    31,    32,    11,
      70,    22,    23,     0,    10,     0,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,    23,     0,    10,
     170,    24,    25,    26,    27,    28,    29,    30,     0,    31,
      32,    11,     0,     0,     0,    77,   171,     0,     0,    27,
      28,    29,    30,     0,    31,    32,    11,     0,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,   177,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,     0,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,   168,   140,     0,     0,
       0,     0,     0,     0,     0,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   147,     0,     0,     0,     0,     0,     0,     0,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   106,     0,     0,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
       0,     1,    17,     0,     1,     5,     0,     1,     5,    12,
      42,     5,    17,    13,     0,    53,    13,    20,    26,    13,
      35,    19,     9,     3,    19,     5,     6,    13,     8,     9,
      35,     5,    21,    13,    14,    15,    16,     3,     4,     5,
       6,    21,     8,     9,     8,    53,    26,    13,    14,    15,
      16,    19,    50,    56,    50,    55,    51,     4,    55,    59,
      26,    55,    59,     2,     3,    58,    10,    27,   100,    55,
      63,    10,    26,    53,    24,    53,    26,    77,    19,    20,
      77,    68,    50,    77,    23,    26,    18,    53,    20,    53,
      22,    51,    24,    53,    26,    95,     3,   112,    95,    49,
      39,    95,    19,    77,    21,   108,     4,   112,   101,    19,
       0,   104,    19,    11,    12,   102,   116,    49,    19,   116,
      50,    95,   116,    62,    14,    15,    18,    21,    20,    17,
      22,    70,    24,    19,    14,    15,    11,    12,    25,    50,
      49,    27,   116,     4,    27,     6,   146,     4,     9,   146,
       4,    50,   146,   153,    93,   155,   153,    49,   155,   153,
      99,   155,    23,     4,   103,     4,   105,     4,   168,     4,
     170,   168,   146,   170,   168,     4,   170,   177,    59,   153,
     177,   155,   172,   177,    45,   124,   125,   112,   124,    -1,
      -1,    -1,    -1,    -1,   168,    -1,   170,    -1,    -1,    60,
      61,    -1,    -1,   177,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,   152,    -1,    -1,    -1,   156,    -1,    -1,
      -1,   160,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   171,    -1,    -1,    96,    97,     3,     4,     5,
       6,   102,     8,     9,    -1,    -1,    -1,    13,    14,    15,
      16,    -1,    -1,    -1,     8,    -1,     3,    -1,     5,     6,
      26,     8,     9,   124,     8,    -1,    13,    14,    15,    16,
      24,    -1,    26,    27,    28,    29,    30,    -1,    22,    26,
      24,    25,    26,    -1,    28,    29,    30,    53,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,     8,    51,    52,    53,
      -1,    -1,    46,    47,    48,    49,    53,    51,    52,    53,
      22,     8,    24,    -1,    26,    -1,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    26,
       3,    28,    29,    30,    46,    47,    48,    49,    -1,    51,
      52,    53,    -1,    -1,    -1,     3,    19,    -1,    -1,    46,
      47,    48,    49,    -1,    51,    52,    53,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     3,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     7,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    27,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     8,     9,    13,    14,    15,    16,
      26,    53,    55,    57,    59,    61,    62,    66,    67,    78,
      55,    56,     8,    24,    28,    29,    30,    46,    47,    48,
      49,    51,    52,    62,    65,    66,    67,    69,    72,    77,
      79,    65,    60,    78,    56,     8,    63,    78,    64,    65,
      63,    78,    65,     0,    59,    21,    55,    21,    50,    19,
      18,    20,    22,    26,    68,    72,    79,     4,    26,    70,
      22,    25,    65,    73,    74,    78,    53,     3,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    76,    65,     7,    19,    20,    70,    10,
      78,    50,    19,    19,    17,    50,    27,    21,    55,    64,
      61,    78,    78,    65,    27,    64,    27,    51,    63,    71,
      65,    25,    19,    21,    75,    50,    49,    56,    65,    56,
      78,    78,    65,    70,    64,    63,    65,    64,    65,    68,
      23,    27,     4,    56,    19,    51,    27,    23,    73,    65,
       4,     4,    11,    12,    58,     3,    19,     4,     4,    56,
      50,    65,    56,     4,    56,    65,     4,    65,     7,     4,
       3,    19,    56,    56,    65,    58,     4,     3,    56,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 159 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 1");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 169 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 2");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(";", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 180 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 3");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 190 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 4");
     IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(";", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 201 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 5");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 211 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 6");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(";", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 222 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 5");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 231 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO chunk 6");
    IParseTreeNode* node = new ParseTreeNode("chunk", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(";", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 243 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO block 1");
    IParseTreeNode* node = new ParseTreeNode("block", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 254 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 1");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("=", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 265 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 2");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 274 "luatfi.y"
    {   
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 3");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("do", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    node->addNodeRight(emb);    
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 285 "luatfi.y"
    {   
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 4");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("while", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (5)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("do", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(4) - (5)].parseTreeNode));
    node->addNodeRight(emb);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 298 "luatfi.y"
    {   
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 5");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("repeat", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (4)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("until", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(4) - (4)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 310 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 6");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("if", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (5)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("then", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true)); 
    emb->addNodeRight((yyvsp[(4) - (5)].parseTreeNode));
    node->addNodeRight(emb);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 323 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 7");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (6)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("if", (yyvsp[(2) - (6)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (6)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("then", (yyvsp[(2) - (6)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(4) - (6)].parseTreeNode));
    emb->addNodeRight((yyvsp[(5) - (6)].parseTreeNode));
    node->addNodeRight(emb);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 337 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 8");    
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (11)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("for", (yyvsp[(2) - (11)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (11)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("=", (yyvsp[(2) - (11)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(4) - (11)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode(",", (yyvsp[(2) - (11)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(6) - (11)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode(",", (yyvsp[(2) - (11)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(8) - (11)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("do", (yyvsp[(2) - (11)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(10) - (11)].parseTreeNode));
    node->addNodeRight(emb);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 356 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 9");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (9)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("for", (yyvsp[(2) - (9)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (9)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("=", (yyvsp[(2) - (9)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(4) - (9)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode(",", (yyvsp[(2) - (9)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(6) - (9)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("do", (yyvsp[(2) - (9)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(8) - (9)].parseTreeNode));
    node->addNodeRight(emb);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 373 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 10");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (7)].parseTreeNode)->getLineNumber(), false);
    IParseTreeNode* emb = new ParseTreeNode("for", (yyvsp[(2) - (7)].parseTreeNode)->getLineNumber(), true);
    emb->addNodeRight((yyvsp[(2) - (7)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("in", (yyvsp[(2) - (7)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(4) - (7)].parseTreeNode));
    emb->addNodeRight(new ParseTreeNode("do", (yyvsp[(2) - (7)].parseTreeNode)->getLineNumber(), true));
    emb->addNodeRight((yyvsp[(6) - (7)].parseTreeNode));
    node->addNodeRight(emb);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 388 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 11");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("function", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 399 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 12");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(3) - (4)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("local", (yyvsp[(3) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight(new ParseTreeNode("function", (yyvsp[(3) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (4)].parseTreeNode));
    node->addNodeRight((yyvsp[(4) - (4)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 411 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 13");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("local", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (4)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("=", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(4) - (4)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 423 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO stat 13");
    IParseTreeNode* node = new ParseTreeNode("stat", (yyvsp[(2) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("local", (yyvsp[(2) - (2)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 435 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO elsestatement 1");
    IParseTreeNode* node = new ParseTreeNode("elseif", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), true);
    node->addNodeRight((yyvsp[(2) - (4)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("then", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(4) - (4)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 446 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO elsestatement 1");
    IParseTreeNode* node = new ParseTreeNode("elseif", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true);
    node->addNodeRight((yyvsp[(2) - (5)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("then", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(4) - (5)].parseTreeNode));
    node->addNodeRight((yyvsp[(5) - (5)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 458 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO elsestatement 2");
    IParseTreeNode* node = new ParseTreeNode("else", (yyvsp[(2) - (2)].parseTreeNode)->getLineNumber(), true);
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 469 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO laststat 1");
    IParseTreeNode* node = new ParseTreeNode("laststat", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("return", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 478 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO laststat 2");
    IParseTreeNode* node = new ParseTreeNode("laststat", (yyvsp[(2) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("return", (yyvsp[(2) - (2)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 488 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO laststat 3");
    IParseTreeNode* node = new ParseTreeNode("laststat", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("break", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 499 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcname 1");
    IParseTreeNode* node = new ParseTreeNode("funcname", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 508 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcname 2");
    IParseTreeNode* node = new ParseTreeNode("funcname", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(",", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 519 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcname 3");
    IParseTreeNode* node = new ParseTreeNode("funcname", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(":", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 532 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO varlist 1");
    IParseTreeNode* node = new ParseTreeNode("varlist", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 541 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO varlist 2");
    IParseTreeNode* node = new ParseTreeNode("varlist", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(",", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 554 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO var 1");
    IParseTreeNode* node = new ParseTreeNode("var", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 563 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO var 2");
    IParseTreeNode* node = new ParseTreeNode("var", (yyvsp[(1) - (4)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (4)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("[", (yyvsp[(1) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (4)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("]", (yyvsp[(1) - (4)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 575 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO var 3");
    IParseTreeNode* node = new ParseTreeNode("var", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(".", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 588 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO namelist 1");
    IParseTreeNode* node = new ParseTreeNode("namelist", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 597 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO namelist 2");
    IParseTreeNode* node = new ParseTreeNode("namelist", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(",", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 610 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO explist 1");
    IParseTreeNode* node = new ParseTreeNode("explist", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(",", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 621 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO explist 2");
    IParseTreeNode* node = new ParseTreeNode("explist", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 632 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 1");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("nil", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 641 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 2");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("false", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 650 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 3");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("true", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 659 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 4");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new NumberNode(lineNumber, (yyvsp[(1) - (1)].val)));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 668 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 5");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 677 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 6");
    IParseTreeNode* node = new ParseTreeNode("exp", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("...", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 686 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 7");
    IParseTreeNode* node = new ParseTreeNode("exp", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 695 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 8");
    IParseTreeNode* node = new ParseTreeNode("exp", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 704 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 9");
    IParseTreeNode* node = new ParseTreeNode("exp", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 713 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 10");
    IParseTreeNode* node = new ParseTreeNode("binop", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 724 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO exp 11");
    IParseTreeNode* node = new ParseTreeNode("unop", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 736 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO prefixexp 1");
    IParseTreeNode* node = new ParseTreeNode("prefixexp", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 745 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO prefixexp 2");
    IParseTreeNode* node = new ParseTreeNode("prefixexp", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 754 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO prefixexp 3");
    IParseTreeNode* node = new ParseTreeNode("prefixexp", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 765 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO functioncall 1");
    IParseTreeNode* node = new ParseTreeNode("functioncall", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 775 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO functioncall 2");
    IParseTreeNode* node = new ParseTreeNode("functioncall", (yyvsp[(1) - (4)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (4)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(":", (yyvsp[(1) - (4)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (4)].parseTreeNode));
    node->addNodeRight((yyvsp[(4) - (4)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 789 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 1");
    //~ IParseTreeNode* node = new ParseTreeNode("args", lineNumber, false);
    //~ currentParseTree = node;
    //~ $$ = node;
    //~ DEBUG_OUTPUT($$->generateOutputFormat());
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 797 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 2");
    IParseTreeNode* node = new ParseTreeNode("args", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 806 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 3");
    IParseTreeNode* node = new ParseTreeNode("args", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 815 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO args 4");
    IParseTreeNode* node = new ParseTreeNode("args", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 826 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO function 1");
    IParseTreeNode* node = new ParseTreeNode("function", (yyvsp[(2) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(2) - (2)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 837 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 1");
    IParseTreeNode* node = new ParseTreeNode("funcbody", (yyvsp[(3) - (4)].parseTreeNode)->getLineNumber(), false);
    // node->addNodeRight(new ParseTreeNode("(", $3->getLineNumber(), true));
    // node->addNodeRight(new ParseTreeNode(")", $3->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (4)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 848 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 2");
    //~ IParseTreeNode* node = new ParseTreeNode("funcbody", lineNumber, false);
    //~ // node->addNodeRight(new ParseTreeNode("(", lineNumber, true));
    //~ // node->addNodeRight(new ParseTreeNode(")", lineNumber, true));
    //~ node->addNodeRight(new ParseTreeNode("end", lineNumber, true));
    //~ currentParseTree = node;
    //~ $$ = node;
    //~ DEBUG_OUTPUT($$->generateOutputFormat());
;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 859 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 3");
    IParseTreeNode* node = new ParseTreeNode("funcbody", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), false);
    // node->addNodeRight(new ParseTreeNode("(", $2->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (5)].parseTreeNode));
    // node->addNodeRight(new ParseTreeNode(")", $4->getLineNumber(), true));
    node->addNodeRight((yyvsp[(4) - (5)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 871 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO funcbody 4");
    IParseTreeNode* node = new ParseTreeNode("funcbody", (yyvsp[(2) - (4)].parseTreeNode)->getLineNumber(), false);
    // node->addNodeRight(new ParseTreeNode("(", $2->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (4)].parseTreeNode));
    // node->addNodeRight(new ParseTreeNode(")", $2->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 884 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 1");
    IParseTreeNode* node = new ParseTreeNode("parlist", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 893 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 2");
    IParseTreeNode* node = new ParseTreeNode("parlist", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode(",", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 903 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 3");
    IParseTreeNode* node = new ParseTreeNode("parlist", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (2)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("...", (yyvsp[(1) - (2)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 913 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO parlist 4");
    IParseTreeNode* node = new ParseTreeNode("parlist", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("...", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 924 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO tableconstructor 1");
    IParseTreeNode* node = new ParseTreeNode("tableconstructor", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("{", lineNumber, true));
    node->addNodeRight(new ParseTreeNode("}", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 934 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO tableconstructor 2");
    IParseTreeNode* node = new ParseTreeNode("tableconstructor", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("{", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("}", (yyvsp[(2) - (3)].parseTreeNode)->getLineNumber(), true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 947 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldlist 1");
    IParseTreeNode* node = new ParseTreeNode("fieldlist", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 956 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldlist 2");
    IParseTreeNode* node = new ParseTreeNode("fieldlist", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight((yyvsp[(2) - (3)].parseTreeNode));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 969 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO field 1");
    IParseTreeNode* node = new ParseTreeNode("field", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight(new ParseTreeNode("[", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(2) - (5)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("]", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight(new ParseTreeNode("=", (yyvsp[(2) - (5)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(5) - (5)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 982 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO field 2");
    IParseTreeNode* node = new ParseTreeNode("field", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (3)].parseTreeNode));
    node->addNodeRight(new ParseTreeNode("=", (yyvsp[(1) - (3)].parseTreeNode)->getLineNumber(), true));
    node->addNodeRight((yyvsp[(3) - (3)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 993 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO field 3");
    IParseTreeNode* node = new ParseTreeNode("field", (yyvsp[(1) - (1)].parseTreeNode)->getLineNumber(), false);
    node->addNodeRight((yyvsp[(1) - (1)].parseTreeNode));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1004 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldsep 1");
    IParseTreeNode* node = new ParseTreeNode("fieldsep", lineNumber, false);
    node->addNodeRight(new ParseTreeNode(",", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1013 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO fieldsep 2");
    IParseTreeNode* node = new ParseTreeNode("fieldsep", lineNumber, false);
    node->addNodeRight(new ParseTreeNode(";", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1024 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("+", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1032 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("-", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1040 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 3");
    IParseTreeNode* node = new ParseTreeNode("*", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1048 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("/", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1056 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("^", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1064 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("%", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1072 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("..", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1080 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("<", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1088 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("<=", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1096 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode(">", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1104 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode(">=", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1112 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("==", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1120 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("~=", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1128 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("and", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1136 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO binop 1");
    IParseTreeNode* node = new ParseTreeNode("or", lineNumber, true);
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1147 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO unop 1");
    IParseTreeNode* node = new ParseTreeNode("unop", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("-", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1156 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO unop 1");
    IParseTreeNode* node = new ParseTreeNode("unop", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("not", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1165 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO unop 1");
    IParseTreeNode* node = new ParseTreeNode("unop", lineNumber, false);
    node->addNodeRight(new ParseTreeNode("#", lineNumber, true));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1176 "luatfi.y"
    {
    // TODO: Test that it isn't a reserved word.
    DEBUG_OUTPUT_BUSTED("JUMPED TO Name 1");
    IParseTreeNode* node = new NameNode(lineNumber, string((yyvsp[(1) - (1)].str)));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1187 "luatfi.y"
    {
    DEBUG_OUTPUT_BUSTED("JUMPED TO String 1");
    IParseTreeNode* node = new StringNode(lineNumber, string((yyvsp[(2) - (3)].str)));
    currentParseTree = node;
    (yyval.parseTreeNode) = node;
    DEBUG_OUTPUT((yyval.parseTreeNode)->generateOutputFormat());
;}
    break;



/* Line 1455 of yacc.c  */
#line 3166 "luatfi.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



