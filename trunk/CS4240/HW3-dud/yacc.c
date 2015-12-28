/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     NUMBER = 259,
     STRING = 260,
     AND = 261,
     BREAK = 262,
     DO = 263,
     ELSE = 264,
     ELSEIF = 265,
     END = 266,
     FALSE = 267,
     FOR = 268,
     FUNCTION = 269,
     IF = 270,
     IN = 271,
     LOCAL = 272,
     NIL = 273,
     NOT = 274,
     OR = 275,
     REPEAT = 276,
     RETURN = 277,
     THEN = 278,
     TRUE = 279,
     UNTIL = 280,
     WHILE = 281,
     SEMI = 282,
     EQUALS = 283,
     COMMA = 284,
     DOT = 285,
     OPEN_BRACK = 286,
     CLOSE_BRACK = 287,
     DOTDOT = 288,
     DOTDOTDOT = 289,
     OPEN_PAR = 290,
     CLOSE_PAR = 291,
     OPEN_SQUIG = 292,
     CLOSE_SQUIG = 293,
     COLON = 294,
     PLUS = 295,
     MINUS = 296,
     STAR = 297,
     FSLASH = 298,
     CARET = 299,
     PERCENT = 300,
     LESS = 301,
     LESS_EQUAL = 302,
     MORE = 303,
     MORE_EQUAL = 304,
     EQUAL_EQUAL = 305,
     SQUIG_EQUAL = 306,
     SHARP = 307
   };
#endif
/* Tokens.  */
#define NAME 258
#define NUMBER 259
#define STRING 260
#define AND 261
#define BREAK 262
#define DO 263
#define ELSE 264
#define ELSEIF 265
#define END 266
#define FALSE 267
#define FOR 268
#define FUNCTION 269
#define IF 270
#define IN 271
#define LOCAL 272
#define NIL 273
#define NOT 274
#define OR 275
#define REPEAT 276
#define RETURN 277
#define THEN 278
#define TRUE 279
#define UNTIL 280
#define WHILE 281
#define SEMI 282
#define EQUALS 283
#define COMMA 284
#define DOT 285
#define OPEN_BRACK 286
#define CLOSE_BRACK 287
#define DOTDOT 288
#define DOTDOTDOT 289
#define OPEN_PAR 290
#define CLOSE_PAR 291
#define OPEN_SQUIG 292
#define CLOSE_SQUIG 293
#define COLON 294
#define PLUS 295
#define MINUS 296
#define STAR 297
#define FSLASH 298
#define CARET 299
#define PERCENT 300
#define LESS 301
#define LESS_EQUAL 302
#define MORE 303
#define MORE_EQUAL 304
#define EQUAL_EQUAL 305
#define SQUIG_EQUAL 306
#define SHARP 307




/* Copy the first part of user declarations.  */
#line 1 "lua.y"


extern "C"
{
	int yyparse(void);
	int yylex(void);  
	int yywrap()
	{
		return 1;
	}
}



#define YYSTYPE void*

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lex_val.h"
#include "lex_name_val.h"
#include "lex_number_val.h"
#include "lex_string_val.h"

#include "base_node.h"
#include "chunk_node.h"
#include "expression_node.h"
#include "expression_node_binary_operation.h"
#include "expression_node_bool.h"
#include "expression_node_dots.h"
#include "expression_node_nil.h"
#include "expression_node_number.h"
#include "expression_node_prefix.h"
#include "expression_node_string.h"
#include "expression_node_table_constructor.h"
#include "expression_node_unary_operation.h"
#include "field_node.h"
#include "field_node_bracket.h"
#include "field_node_expression.h"
#include "field_node_name.h"
#include "function_body_node.h"
#include "function_call_node.h"
#include "prefix_node.h"
#include "prefix_node_function_call.h"
#include "prefix_node_parenthesis.h"
#include "prefix_node_variable.h"
#include "statement_node.h"
#include "statement_node_assign.h"
#include "statement_node_break.h"
#include "statement_node_do.h"
#include "statement_node_function_definition.h"
#include "statement_node_funtion_call.h"
#include "statement_node_generic_for.h"
#include "statement_node_if.h"
#include "statement_node_local_function_definition.h"
#include "statement_node_local_variable_declaration.h"
#include "statement_node_numeric_for.h"
#include "statement_node_repeate.h"
#include "statement_node_return.h"
#include "statement_node_while.h"
#include "variable_node.h"
#include "variable_node_name.h"
#include "variable_node_prefix_bracket.h"
#include "variable_node_prefix_dot.h"

extern "C"
{
	//extern ChunkNode topNode;

	void yyerror(const char *str)
	{	
		extern int linenum;
		fprintf(stderr,"Error: parse error at line %d\n", linenum);
	}
}

class COptElseIfs
{
	public:
		ExpressionNodeList Expressions;
		ChunkNodeList Chunks;
};
typedef COptElseIfs* OptElseIfs;


class CParamsList
{
	public:
		LexNameValList Names;
		bool Dots;
};
typedef CParamsList* ParamsList;






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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 309 "yacc.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   487

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  179

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    13,    16,    17,    19,
      20,    22,    26,    28,    32,    38,    43,    51,    57,    58,
      61,    62,    73,    76,    77,    85,    89,    94,    98,   101,
     102,   105,   107,   108,   110,   113,   117,   118,   121,   125,
     126,   128,   133,   137,   140,   144,   145,   148,   152,   153,
     155,   157,   159,   161,   163,   165,   167,   169,   173,   176,
     178,   180,   184,   187,   191,   193,   194,   196,   198,   204,
     206,   207,   210,   213,   214,   216,   220,   222,   223,   226,
     230,   234,   235,   239,   240,   246,   250,   252,   254,   256,
     258,   260,   262,   264,   266,   268,   270,   272,   274,   276,
     278,   280,   282,   284,   286,   288,   290
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    55,    -1,    56,    57,    -1,    60,    58,
      56,    -1,    -1,    65,    58,    -1,    -1,    27,    -1,    -1,
      55,    -1,    69,    28,    74,    -1,    78,    -1,     8,    59,
      11,    -1,    26,    76,     8,    59,    11,    -1,    21,    59,
      25,    76,    -1,    15,    76,    23,    59,    61,    62,    11,
      -1,    10,    76,    23,    59,    61,    -1,    -1,     9,    59,
      -1,    -1,    13,     3,    28,    76,    29,    76,    63,     8,
      59,    11,    -1,    29,    76,    -1,    -1,    13,    72,    16,
      74,     8,    59,    11,    -1,    14,    67,    81,    -1,    17,
      14,     3,    81,    -1,    17,    72,    64,    -1,    28,    74,
      -1,    -1,    22,    66,    -1,    74,    -1,    -1,     7,    -1,
       3,    68,    -1,    30,     3,    68,    -1,    -1,    71,    70,
      -1,    29,    71,    70,    -1,    -1,     3,    -1,    77,    31,
      76,    32,    -1,    77,    30,     3,    -1,     3,    73,    -1,
      29,     3,    73,    -1,    -1,    76,    75,    -1,    29,    76,
      75,    -1,    -1,    18,    -1,    12,    -1,    24,    -1,     4,
      -1,     5,    -1,    34,    -1,    77,    -1,    85,    -1,    76,
      92,    76,    -1,    93,    76,    -1,    71,    -1,    78,    -1,
      35,    76,    36,    -1,    77,    79,    -1,    35,    80,    36,
      -1,    74,    -1,    -1,    85,    -1,     5,    -1,    35,    82,
      36,    59,    11,    -1,    83,    -1,    -1,    72,    84,    -1,
      29,    34,    -1,    -1,    34,    -1,    37,    86,    38,    -1,
      87,    -1,    -1,    90,    88,    -1,    90,    91,    89,    -1,
      91,    90,    88,    -1,    -1,    90,    91,    89,    -1,    -1,
      31,    76,    32,    28,    76,    -1,     3,    28,    76,    -1,
      76,    -1,    29,    -1,    27,    -1,    40,    -1,    41,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,    33,    -1,
      46,    -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,
      51,    -1,     6,    -1,    20,    -1,    41,    -1,    19,    -1,
      52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   111,   124,   134,   139,   146,   151,   158,
     163,   169,   177,   184,   191,   199,   207,   226,   239,   247,
     254,   259,   271,   278,   283,   293,   302,   311,   320,   327,
     332,   340,   347,   352,   358,   367,   377,   382,   391,   401,
     406,   413,   421,   429,   438,   448,   453,   462,   472,   477,
     483,   489,   495,   502,   509,   515,   522,   529,   538,   546,
     553,   560,   567,   575,   581,   588,   593,   603,   613,   621,
     628,   636,   645,   652,   657,   666,   672,   679,   684,   693,
     702,   712,   717,   727,   733,   741,   749,   756,   762,   768,
     775,   782,   789,   796,   803,   810,   817,   824,   831,   838,
     845,   852,   859,   866,   873,   880,   887
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "NUMBER", "STRING", "AND",
  "BREAK", "DO", "ELSE", "ELSEIF", "END", "FALSE", "FOR", "FUNCTION", "IF",
  "IN", "LOCAL", "NIL", "NOT", "OR", "REPEAT", "RETURN", "THEN", "TRUE",
  "UNTIL", "WHILE", "SEMI", "EQUALS", "COMMA", "DOT", "OPEN_BRACK",
  "CLOSE_BRACK", "DOTDOT", "DOTDOTDOT", "OPEN_PAR", "CLOSE_PAR",
  "OPEN_SQUIG", "CLOSE_SQUIG", "COLON", "PLUS", "MINUS", "STAR", "FSLASH",
  "CARET", "PERCENT", "LESS", "LESS_EQUAL", "MORE", "MORE_EQUAL",
  "EQUAL_EQUAL", "SQUIG_EQUAL", "SHARP", "$accept", "top", "chunk",
  "chunk_rep_stat", "chunk_opt_laststat", "chunk_opt_semi", "block",
  "stat", "stat_rep_elseif", "stat_opt_else", "stat_opt_exp",
  "stat_opt_explist", "laststat", "laststat_opt_explist", "funcname",
  "funcname_rep_name", "varlist", "varlist_rep_var", "var", "namelist",
  "namelist_rep_name", "explist", "explist_rep_exp", "exp", "prefixexp",
  "functioncall", "args", "args_opt_explist", "funcbody",
  "funcbody_opt_parlist", "parlist", "parlist_opt_dots",
  "tableconstructor", "tableconstructor_opt_fieldlist", "fieldlist",
  "fieldlist_rep_field", "fieldlist_rep_field2", "field", "fieldsep",
  "binop", "unop", 0
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
     305,   306,   307
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    56,    56,    57,    57,    58,    58,
      59,    60,    60,    60,    60,    60,    60,    61,    61,    62,
      62,    60,    63,    63,    60,    60,    60,    60,    64,    64,
      65,    66,    66,    65,    67,    68,    68,    69,    70,    70,
      71,    71,    71,    72,    73,    73,    74,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    77,
      77,    77,    78,    79,    80,    80,    79,    79,    81,    82,
      82,    83,    84,    84,    83,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    90,    91,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     0,     2,     0,     1,     0,
       1,     3,     1,     3,     5,     4,     7,     5,     0,     2,
       0,    10,     2,     0,     7,     3,     4,     3,     2,     0,
       2,     1,     0,     1,     2,     3,     0,     2,     3,     0,
       1,     4,     3,     2,     3,     0,     2,     3,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     1,
       1,     3,     2,     3,     1,     0,     1,     1,     5,     1,
       0,     2,     2,     0,     1,     3,     1,     0,     2,     3,
       3,     0,     3,     0,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,    40,     5,     0,     0,     0,     0,     5,     0,     0,
       0,     2,     7,     9,     0,    59,     0,    12,    10,     0,
      45,     0,    36,     0,    52,    53,    50,    49,   105,    51,
      54,    77,   104,   106,    59,     0,    55,    60,    56,     0,
      45,     0,    29,     0,     0,     0,     1,    33,    32,     3,
       9,     8,     5,     0,     0,    37,    67,     0,     0,    65,
      62,    66,    13,     0,     0,    43,     0,     0,    34,    70,
      25,    40,     0,    86,     0,    76,    81,   102,   103,     5,
      95,    89,    90,    91,    92,    93,    94,    96,    97,    98,
      99,   100,   101,     0,    58,     0,     0,    27,     0,     5,
      61,    30,    31,    48,     6,     4,    11,    59,    42,     0,
      64,     0,     0,    45,     0,    36,    74,    73,     0,    69,
       0,     0,    75,    88,    87,    78,    83,    18,    57,    26,
      28,    15,     0,     0,    46,    38,    41,    63,     0,    44,
       5,    35,     0,    71,     5,    85,     0,    79,    81,     0,
      20,    14,    48,    23,     0,    72,     0,     0,    80,    83,
       0,     5,     0,    47,     0,     0,    24,    68,    84,    82,
       5,    19,    16,    22,     5,    18,     0,    17,    21
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    18,    12,    49,    52,    19,    13,   150,   162,
     165,    97,    50,   101,    23,    68,    14,    55,    34,    21,
      65,   102,   134,   103,    36,    37,    60,   111,    70,   118,
     119,   143,    38,    74,    75,   125,   147,   148,   126,    93,
      39
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -52
static const yytype_int16 yypact[] =
{
      68,   -52,    68,     6,    18,   101,    19,    68,   101,   101,
      34,   -52,     9,    21,    22,    -5,    10,    81,   -52,    35,
      -3,    42,    38,    16,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,    25,   -52,   -52,   -52,   160,    10,   -52,   -52,   101,
      36,    61,    44,    45,   206,   225,   -52,   -52,   101,   -52,
      21,   -52,    68,   101,     7,   -52,   -52,    70,   101,   101,
     -52,   -52,   -52,   101,    71,   -52,   101,    72,   -52,     2,
     -52,    56,   101,   436,    49,   -52,   -10,   -52,   -52,    68,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   101,   436,    16,   101,   -52,   101,    68,
     -52,   -52,   -52,   257,   -52,   -52,   -52,    -5,   -52,   289,
     -52,    55,   321,    36,    84,    38,   -52,    66,    60,   -52,
     101,   353,   -52,   -52,   -52,   -52,    25,    87,   436,   -52,
     -52,   436,    90,   101,   -52,   -52,   -52,   -52,   101,   -52,
      68,   -52,    73,   -52,    68,   436,    80,   -52,   -10,   101,
     100,   -52,   257,   385,   103,   -52,   104,   101,   -52,    25,
     417,    68,   105,   -52,   101,   109,   -52,   -52,   436,   -52,
      68,   -52,   -52,   436,    68,    87,   110,   -52,   -52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,   122,    74,   -52,    77,    -1,   -52,   -51,   -52,
     -52,   -52,   -52,   -52,   -52,    14,   -52,    23,     0,    -2,
      20,   -39,   -21,    30,     1,    11,   -52,   -52,    37,   -52,
     -52,   -52,    -4,   -52,   -52,   -14,   -22,   115,     4,   -52,
     -52
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -61
static const yytype_int16 yytable[] =
{
      15,    16,    15,    16,    42,    40,    43,    15,    16,    20,
       1,    17,    61,    17,   106,    56,    47,   123,    17,   124,
     110,    22,    40,   -39,    54,    63,    64,   114,    71,    24,
      25,    48,    61,    41,    46,    35,   116,    26,    44,    45,
      57,    58,     9,    27,    28,    59,    62,    31,    51,    29,
      53,    69,    15,    16,   107,    16,    72,   130,    66,    30,
       9,    73,    31,    17,    95,    64,    32,   117,    67,    94,
      98,     1,    96,   108,   113,   115,     2,    33,   127,    15,
      16,     3,     4,     5,   120,     6,   -60,   122,   109,     7,
      17,   137,   140,   112,     8,   142,   144,   149,   132,    15,
      16,   151,   121,     9,     1,    24,    25,   155,   157,   161,
      17,   -60,   -60,    26,   166,   167,   172,   174,   -60,    27,
      28,   178,    11,   128,   177,    29,   105,   104,   131,   141,
     135,   163,   129,   139,   158,    30,     9,   169,    31,   154,
      15,    16,    32,   156,    15,    16,    76,     0,     0,     0,
     145,    17,   159,    33,     0,    17,    73,     0,     0,     0,
     171,    15,    16,   152,     0,     0,    77,     0,   153,   175,
      15,    16,    17,   176,    15,    16,     0,     0,     0,   160,
      78,    17,     0,    79,     0,    17,     0,   168,     0,    73,
       0,     0,     0,    80,   173,     0,     0,     0,     0,     0,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    77,     0,    99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,     0,     0,     0,
       0,    77,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,    78,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    80,     0,
       0,   100,     0,    77,     0,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    78,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
      80,     0,     0,     0,     0,    77,     0,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   136,    80,     0,     0,     0,     0,    77,     0,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    78,     0,     0,     0,     0,     0,     0,     0,     0,
     138,     0,     0,     0,    80,     0,     0,     0,     0,    77,
       0,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146,    80,     0,     0,     0,
       0,    77,     0,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    78,     0,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,    80,     0,
       0,     0,     0,    77,     0,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    78,     0,     0,
     170,     0,    77,     0,     0,     0,     0,     0,     0,     0,
      80,     0,     0,     0,     0,     0,    78,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    80,
       0,     0,     0,     0,     0,     0,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
       0,     0,     2,     2,     6,     3,     7,     7,     7,     3,
       3,     0,    16,     2,    53,     5,     7,    27,     7,    29,
      59,     3,     3,    28,    29,    28,    29,    66,     3,     4,
       5,    22,    36,    14,     0,     5,    34,    12,     8,     9,
      30,    31,    35,    18,    19,    35,    11,    37,    27,    24,
      28,    35,    52,    52,    54,    54,    31,    96,    16,    34,
      35,    31,    37,    52,     3,    29,    41,    69,    30,    39,
      25,     3,    28,     3,     3,     3,     8,    52,    79,    79,
      79,    13,    14,    15,    28,    17,     5,    38,    58,    21,
      79,    36,     8,    63,    26,    29,    36,    10,    99,    99,
      99,    11,    72,    35,     3,     4,     5,    34,    28,     9,
      99,    30,    31,    12,    11,    11,    11,     8,    37,    18,
      19,    11,     0,    93,   175,    24,    52,    50,    98,   115,
     107,   152,    95,   113,   148,    34,    35,   159,    37,   140,
     140,   140,    41,   144,   144,   144,    31,    -1,    -1,    -1,
     120,   140,   148,    52,    -1,   144,   126,    -1,    -1,    -1,
     161,   161,   161,   133,    -1,    -1,     6,    -1,   138,   170,
     170,   170,   161,   174,   174,   174,    -1,    -1,    -1,   149,
      20,   170,    -1,    23,    -1,   174,    -1,   157,    -1,   159,
      -1,    -1,    -1,    33,   164,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,     6,    -1,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    20,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    33,    -1,
      -1,    36,    -1,     6,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,     6,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,    -1,    -1,    -1,     6,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,     6,
      -1,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,
      -1,     6,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    -1,     6,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    20,    -1,    -1,
      23,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    20,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,    13,    14,    15,    17,    21,    26,    35,
      54,    55,    56,    60,    69,    71,    77,    78,    55,    59,
       3,    72,     3,    67,     4,     5,    12,    18,    19,    24,
      34,    37,    41,    52,    71,    76,    77,    78,    85,    93,
       3,    14,    72,    59,    76,    76,     0,     7,    22,    57,
      65,    27,    58,    28,    29,    70,     5,    30,    31,    35,
      79,    85,    11,    28,    29,    73,    16,    30,    68,    35,
      81,     3,    31,    76,    86,    87,    90,     6,    20,    23,
      33,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    92,    76,     3,    28,    64,    25,     8,
      36,    66,    74,    76,    58,    56,    74,    71,     3,    76,
      74,    80,    76,     3,    74,     3,    34,    72,    82,    83,
      28,    76,    38,    27,    29,    88,    91,    59,    76,    81,
      74,    76,    59,    29,    75,    70,    32,    36,    29,    73,
       8,    68,    29,    84,    36,    76,    32,    89,    90,    10,
      61,    11,    76,    76,    59,    34,    59,    28,    88,    91,
      76,     9,    62,    75,    29,    63,    11,    11,    76,    89,
      23,    59,    11,    76,     8,    59,    59,    61,    11
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 106 "lua.y"
    {
		//topNode = (ChunkNode)$$;
	}
    break;

  case 3:
#line 112 "lua.y"
    {
		StatementNodeList statementNodes = (StatementNodeList)(yyvsp[(1) - (2)]);			
		StatementNode lastStatementNode = (StatementNode)(yyvsp[(2) - (2)]);
		if (lastStatementNode != NULL)
		{
			statementNodes->push_back(lastStatementNode);
		}
		
		(yyval) = (void*)new CChunkNode(statementNodes);
	}
    break;

  case 4:
#line 125 "lua.y"
    {
		StatementNode statementNode = (StatementNode)(yyvsp[(1) - (3)]);			
		StatementNodeList statementNodes = (StatementNodeList)(yyvsp[(3) - (3)]);	
		statementNodes->push_front(statementNode);	
		(yyval) = (void*)statementNodes;
	}
    break;

  case 5:
#line 134 "lua.y"
    {
		(yyval) = (void*)new CStatementNodeList();
	}
    break;

  case 6:
#line 140 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(1) - (2)]);
	}
    break;

  case 7:
#line 146 "lua.y"
    {
		(yyval) = (void*)NULL;	
	}
    break;

  case 8:
#line 152 "lua.y"
    {
		(yyval) = (void*)NULL; //dont care about semi in ABS
	}
    break;

  case 9:
#line 158 "lua.y"
    {
		(yyval) = (void*)NULL;
	}
    break;

  case 10:
#line 164 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(1) - (1)]);	
	}
    break;

  case 11:
#line 170 "lua.y"
    {
		VariableNodeList vars = (VariableNodeList)(yyvsp[(1) - (3)]);
		ExpressionNodeList exps = (ExpressionNodeList)(yyvsp[(3) - (3)]);	
		(yyval) = (void*)new CStatementNodeAssign(vars, exps);
	}
    break;

  case 12:
#line 178 "lua.y"
    {
		FunctionCallNode functioncall = (FunctionCallNode)(yyvsp[(1) - (1)]);	
		(yyval) = (void*)new CStatementNodeFuntionCall(functioncall);
	}
    break;

  case 13:
#line 185 "lua.y"
    {
		ChunkNode chunk = (ChunkNode)(yyvsp[(2) - (3)]);	
		(yyval) = (void*)new CStatementNodeDo(chunk);
	}
    break;

  case 14:
#line 192 "lua.y"
    {
		ExpressionNode expression = (ExpressionNode)(yyvsp[(2) - (5)]);
		ChunkNode chunk = (ChunkNode)(yyvsp[(4) - (5)]);
		(yyval) = (void*)new CStatementNodeWhile(expression, chunk);
	}
    break;

  case 15:
#line 200 "lua.y"
    {
		ChunkNode chunk = (ChunkNode)(yyvsp[(2) - (4)]);
		ExpressionNode expression = (ExpressionNode)(yyvsp[(4) - (4)]);
		(yyval) = (void*)new CStatementNodeRepeate(chunk, expression);
	}
    break;

  case 16:
#line 208 "lua.y"
    {
		ExpressionNode ifExpression = (ExpressionNode)(yyvsp[(2) - (7)]);
		ChunkNode ifChunk = (ChunkNode)(yyvsp[(4) - (7)]);

		OptElseIfs optElseIfs = (OptElseIfs)(yyvsp[(5) - (7)]);
		optElseIfs->Expressions->push_front(ifExpression);
		optElseIfs->Chunks->push_front(ifChunk);

		ChunkNode elseChunk = (ChunkNode)(yyvsp[(6) - (7)]);		
		if (elseChunk != NULL)
		{
			optElseIfs->Chunks->push_back(elseChunk);
		}

		(yyval) = (void*)new CStatementNodeIf(optElseIfs->Expressions, optElseIfs->Chunks);
	}
    break;

  case 17:
#line 227 "lua.y"
    {
		ExpressionNode expression = (ExpressionNode)(yyvsp[(2) - (5)]);
		ChunkNode chunk = (ChunkNode)(yyvsp[(4) - (5)]);

		OptElseIfs optElseIfs = (OptElseIfs)(yyvsp[(5) - (5)]);
		optElseIfs->Expressions->push_front(expression);
		optElseIfs->Chunks->push_front(chunk);
		(yyval) = (void*)optElseIfs;		
	}
    break;

  case 18:
#line 239 "lua.y"
    {
		OptElseIfs optElseIfs = new COptElseIfs();
		optElseIfs->Expressions = new CExpressionNodeList();
		optElseIfs->Chunks = new CChunkNodeList();
		(yyval) = (void*)optElseIfs;
	}
    break;

  case 19:
#line 248 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(2) - (2)]);
	}
    break;

  case 20:
#line 254 "lua.y"
    {
		(yyval) = (void*)NULL;
	}
    break;

  case 21:
#line 260 "lua.y"
    {
		 LexNameVal name = (LexNameVal)(yyvsp[(2) - (10)]);
		 ExpressionNode exp1 = (ExpressionNode)(yyvsp[(4) - (10)]);
		 ExpressionNode exp2 = (ExpressionNode)(yyvsp[(6) - (10)]);
		 ExpressionNode exp3 = (ExpressionNode)(yyvsp[(7) - (10)]);
		 ChunkNode chunk = (ChunkNode)(yyvsp[(9) - (10)]);

		(yyval) = (void*)new CStatementNodeNumericFor(name, exp1, exp2, exp3, chunk);
	}
    break;

  case 22:
#line 272 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(2) - (2)]);
	}
    break;

  case 23:
#line 278 "lua.y"
    {
		(yyval) = (void*)NULL;
	}
    break;

  case 24:
#line 284 "lua.y"
    {
		LexNameValList names = (LexNameValList)(yyvsp[(2) - (7)]);
		ExpressionNodeList expressions = (ExpressionNodeList)(yyvsp[(4) - (7)]);
		ChunkNode chunk = (ChunkNode)(yyvsp[(6) - (7)]);

		(yyval) = (void*)new CStatementNodeGenericFor(names, expressions, chunk);
	}
    break;

  case 25:
#line 294 "lua.y"
    {
		LexNameValList names = (LexNameValList)(yyvsp[(2) - (3)]);
		FunctionBodyNode bodyNode = (FunctionBodyNode)(yyvsp[(3) - (3)]);

		(yyval) = (void*)new CStatementNodeFunctionDefinition(names, bodyNode);
	}
    break;

  case 26:
#line 303 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(3) - (4)]);
		FunctionBodyNode bodyNode = (FunctionBodyNode)(yyvsp[(4) - (4)]);

		(yyval) = (void*)new CStatementNodeLocalFunctionDefinition(name, bodyNode);
	}
    break;

  case 27:
#line 312 "lua.y"
    {
		LexNameValList names = (LexNameValList)(yyvsp[(2) - (3)]);
		ExpressionNodeList expressions = (ExpressionNodeList)(yyvsp[(3) - (3)]);

		(yyval) = (void*)new CStatementNodeLocalVariableDeclaration(names, expressions);
	}
    break;

  case 28:
#line 321 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(2) - (2)]);
	}
    break;

  case 29:
#line 327 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeList();
	}
    break;

  case 30:
#line 333 "lua.y"
    {		
		ExpressionNodeList expressions = (ExpressionNodeList)(yyvsp[(2) - (2)]);

		(yyval) = (void*)new CStatementNodeReturn(expressions);
	}
    break;

  case 31:
#line 341 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(1) - (1)]);
	}
    break;

  case 32:
#line 347 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeList();;
	}
    break;

  case 33:
#line 353 "lua.y"
    {
		(yyval) = (void*)new CStatementNodeBreak();
	}
    break;

  case 34:
#line 359 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(1) - (2)]);
		LexNameValList names = (LexNameValList)(yyvsp[(2) - (2)]);
		names->push_front(name);
		(yyval) = names;
	}
    break;

  case 35:
#line 368 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(2) - (3)]);
		LexNameValList names = (LexNameValList)(yyvsp[(3) - (3)]);
		names->push_front(name);
		(yyval) = names;
	}
    break;

  case 36:
#line 377 "lua.y"
    {
		(yyval) = (void*)new CLexNameValList();
	}
    break;

  case 37:
#line 383 "lua.y"
    {
		VariableNode var = (VariableNode)(yyvsp[(1) - (2)]);
		VariableNodeList vars = (VariableNodeList)(yyvsp[(2) - (2)]);
		vars->push_front(var);
		(yyval) = vars;
	}
    break;

  case 38:
#line 392 "lua.y"
    {
		VariableNode var = (VariableNode)(yyvsp[(2) - (3)]);
		VariableNodeList vars = (VariableNodeList)(yyvsp[(3) - (3)]);
		vars->push_front(var);
		(yyval) = vars;
	}
    break;

  case 39:
#line 401 "lua.y"
    {
		(yyval) = (void*)new CVariableNodeList();
	}
    break;

  case 40:
#line 407 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CVariableNodeName(name);
	}
    break;

  case 41:
#line 414 "lua.y"
    {
		PrefixNode prefix = (PrefixNode)(yyvsp[(1) - (4)]);
		ExpressionNode expression = (ExpressionNode)(yyvsp[(3) - (4)]);
		(yyval) = (void*)new CVariableNodePrefixBracket(prefix, expression);
	}
    break;

  case 42:
#line 422 "lua.y"
    {
		PrefixNode prefix = (PrefixNode)(yyvsp[(1) - (3)]);
		LexNameVal name = (LexNameVal)(yyvsp[(3) - (3)]);
		(yyval) = (void*)new CVariableNodePrefixDot(prefix, name);
	}
    break;

  case 43:
#line 430 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(1) - (2)]);
		LexNameValList names = (LexNameValList)(yyvsp[(2) - (2)]);
		names->push_front(name);
		(yyval) = (void*)names;
	}
    break;

  case 44:
#line 439 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(2) - (3)]);
		LexNameValList names = (LexNameValList)(yyvsp[(3) - (3)]);
		names->push_front(name);
		(yyval) = (void*)names;
	}
    break;

  case 45:
#line 448 "lua.y"
    {
		(yyval) = (void*)new CLexNameValList();
	}
    break;

  case 46:
#line 454 "lua.y"
    {
		ExpressionNode expression = (ExpressionNode)(yyvsp[(1) - (2)]);
		ExpressionNodeList expressions = (ExpressionNodeList)(yyvsp[(2) - (2)]);
		expressions->push_front(expression);
		(yyval) = (void*)expressions;
	}
    break;

  case 47:
#line 463 "lua.y"
    {
		ExpressionNode expression = (ExpressionNode)(yyvsp[(2) - (3)]);
		ExpressionNodeList expressions = (ExpressionNodeList)(yyvsp[(3) - (3)]);
		expressions->push_front(expression);
		(yyval) = (void*)expressions;
	}
    break;

  case 48:
#line 472 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeList();
	}
    break;

  case 49:
#line 478 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeNil();
	}
    break;

  case 50:
#line 484 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeBool(false);
	}
    break;

  case 51:
#line 490 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeBool(true);
	}
    break;

  case 52:
#line 496 "lua.y"
    {
		LexNumberVal number = (LexNumberVal)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CExpressionNodeNumber(number);
	}
    break;

  case 53:
#line 503 "lua.y"
    {
		LexStringVal string = (LexStringVal)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CExpressionNodeString(string);
	}
    break;

  case 54:
#line 510 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeDots();
	}
    break;

  case 55:
#line 516 "lua.y"
    {
		PrefixNode prefix = (PrefixNode)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CExpressionNodePrefix(prefix);
	}
    break;

  case 56:
#line 523 "lua.y"
    {
		FieldNodeList fields = (FieldNodeList)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CExpressionNodeTableConstructor(fields);
	}
    break;

  case 57:
#line 530 "lua.y"
    {
		ExpressionNode exp1 = (ExpressionNode)(yyvsp[(1) - (3)]);
		BinaryOperationType biop = (BinaryOperationType)(int)(yyvsp[(2) - (3)]);
		ExpressionNode exp2 = (ExpressionNode)(yyvsp[(3) - (3)]);
		(yyval) = (void*)new CExpressionNodeBinaryOperation(biop, exp1, exp2);
	}
    break;

  case 58:
#line 539 "lua.y"
    {
		UnaryOperationType uop = (UnaryOperationType)(int)(yyvsp[(1) - (2)]);
		ExpressionNode exp = (ExpressionNode)(yyvsp[(2) - (2)]);
		(yyval) = (void*)new CExpressionNodeUnaryOperation(uop, exp);
	}
    break;

  case 59:
#line 547 "lua.y"
    {
		VariableNode var = (VariableNode)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CPrefixNodeVariable(var);
	}
    break;

  case 60:
#line 554 "lua.y"
    {
		FunctionCallNode functionCallNode = (FunctionCallNode)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CPrefixNodeFunctionCall(functionCallNode);
	}
    break;

  case 61:
#line 561 "lua.y"
    {
		ExpressionNode expressionNode = (ExpressionNode)(yyvsp[(1) - (3)]);
		(yyval) = (void*)new CPrefixNodeParenthesis(expressionNode);
	}
    break;

  case 62:
#line 568 "lua.y"
    {
		PrefixNode prefix = (PrefixNode)(yyvsp[(1) - (2)]);
		ExpressionNodeList args = (ExpressionNodeList)(yyvsp[(2) - (2)]);
		(yyval) = (void*)new CFunctionCallNode(prefix, args);
	}
    break;

  case 63:
#line 576 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(2) - (3)]);
	}
    break;

  case 64:
#line 582 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(1) - (1)]);
	}
    break;

  case 65:
#line 588 "lua.y"
    {
		(yyval) = (void*)new CExpressionNodeList();
	}
    break;

  case 66:
#line 594 "lua.y"
    {
		FieldNodeList fields = (FieldNodeList)(yyvsp[(1) - (1)]);
 		ExpressionNodeTableConstructor tblNode = new CExpressionNodeTableConstructor(fields);
		ExpressionNodeList expNodes = new CExpressionNodeList();
		expNodes->push_front(tblNode);
		(yyval) = expNodes;
	}
    break;

  case 67:
#line 604 "lua.y"
    {
		LexStringVal str = (LexStringVal)(yyvsp[(1) - (1)]);
 		ExpressionNodeString strNode = new CExpressionNodeString(str);
		ExpressionNodeList expNodes = new CExpressionNodeList();
		expNodes->push_front(strNode);
		(yyval) = expNodes;
	}
    break;

  case 68:
#line 614 "lua.y"
    {
		ParamsList parms = (ParamsList)(yyvsp[(2) - (5)]);
		ChunkNode chunk = (ChunkNode)(yyvsp[(4) - (5)]);
		(yyval) = (void*)new CFunctionBodyNode(parms->Names, parms->Dots, chunk);		
	}
    break;

  case 69:
#line 622 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(1) - (1)]);
	}
    break;

  case 70:
#line 628 "lua.y"
    {
		ParamsList parms = new CParamsList();
		parms->Names = new CLexNameValList();
		parms->Dots = false;
		(yyval) = (void*)parms;
	}
    break;

  case 71:
#line 637 "lua.y"
    {
		ParamsList parms = new CParamsList();
		parms->Names = (LexNameValList)(yyvsp[(1) - (2)]);
		parms->Dots = (bool)(yyvsp[(2) - (2)]);
		(yyval) = (void*)parms;
	}
    break;

  case 72:
#line 646 "lua.y"
    {
		(yyval) = (void*)true;
	}
    break;

  case 73:
#line 652 "lua.y"
    {
		(yyval) = (void*)false;
	}
    break;

  case 74:
#line 658 "lua.y"
    {
		ParamsList parms = new CParamsList();
		parms->Names = new CLexNameValList();
		parms->Dots = true;
		(yyval) = (void*)parms;
	}
    break;

  case 75:
#line 667 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(2) - (3)]);
	}
    break;

  case 76:
#line 673 "lua.y"
    {
		(yyval) = (void*)(yyvsp[(1) - (1)]);
	}
    break;

  case 77:
#line 679 "lua.y"
    {
		(yyval) = (void*)new CFieldNodeList();
	}
    break;

  case 78:
#line 685 "lua.y"
    {
		FieldNode field = (FieldNode)(yyvsp[(1) - (2)]);
		FieldNodeList fieldList = (FieldNodeList)(yyvsp[(2) - (2)]);
		fieldList->push_front(field);
		(yyval) = (void*)fieldList;
	}
    break;

  case 79:
#line 694 "lua.y"
    {
		FieldNode field = (FieldNode)(yyvsp[(1) - (3)]);
		FieldNodeList fieldList = (FieldNodeList)(yyvsp[(3) - (3)]);
		fieldList->push_front(field);
		(yyval) = (void*)fieldList;
	}
    break;

  case 80:
#line 703 "lua.y"
    {
		FieldNode field = (FieldNode)(yyvsp[(2) - (3)]);
		FieldNodeList fieldList = (FieldNodeList)(yyvsp[(3) - (3)]);
		fieldList->push_front(field);
		(yyval) = (void*)fieldList;
	}
    break;

  case 81:
#line 712 "lua.y"
    {
		(yyval) = (void*)new CFieldNodeList();
	}
    break;

  case 82:
#line 718 "lua.y"
    {
		FieldNode field = (FieldNode)(yyvsp[(1) - (3)]);
		FieldNodeList fieldList = (FieldNodeList)(yyvsp[(3) - (3)]);
		fieldList->push_front(field);
		(yyval) = (void*)fieldList;
	}
    break;

  case 83:
#line 727 "lua.y"
    {
		(yyval) = (void*)new CFieldNodeList();
	}
    break;

  case 84:
#line 734 "lua.y"
    {
		ExpressionNode exp1 = (ExpressionNode)(yyvsp[(2) - (5)]);
		ExpressionNode exp2 = (ExpressionNode)(yyvsp[(4) - (5)]);
		(yyval) = (void*)new CFieldNodeBracket(exp1, exp2);
	}
    break;

  case 85:
#line 742 "lua.y"
    {
		LexNameVal name = (LexNameVal)(yyvsp[(1) - (3)]);
		ExpressionNode exp = (ExpressionNode)(yyvsp[(3) - (3)]);
		(yyval) = (void*)new CFieldNodeName(name, exp);
	}
    break;

  case 86:
#line 750 "lua.y"
    {
		ExpressionNode exp = (ExpressionNode)(yyvsp[(1) - (1)]);
		(yyval) = (void*)new CFieldNodeExpression(exp);
	}
    break;

  case 87:
#line 757 "lua.y"
    {
		(yyval) = (void*)NULL;
	}
    break;

  case 88:
#line 763 "lua.y"
    {
		(yyval) = (void*)NULL;
	}
    break;

  case 89:
#line 769 "lua.y"
    {
		BinaryOperationType ret = Plus;
		(yyval) = (void*)ret;
	}
    break;

  case 90:
#line 776 "lua.y"
    {
		BinaryOperationType ret = Minus;
		(yyval) = (void*)ret;
	}
    break;

  case 91:
#line 783 "lua.y"
    {
		BinaryOperationType ret = Times;
		(yyval) = (void*)ret;
	}
    break;

  case 92:
#line 790 "lua.y"
    {
		BinaryOperationType ret = Divide;
		(yyval) = (void*)ret;
	}
    break;

  case 93:
#line 797 "lua.y"
    {
		BinaryOperationType ret = Raise;
		(yyval) = (void*)ret;
	}
    break;

  case 94:
#line 804 "lua.y"
    {
		BinaryOperationType ret = Modulus;
		(yyval) = (void*)ret;
	}
    break;

  case 95:
#line 811 "lua.y"
    {
		BinaryOperationType ret = Concat;
		(yyval) = (void*)ret;
	}
    break;

  case 96:
#line 818 "lua.y"
    {
		BinaryOperationType ret = Less;
		(yyval) = (void*)ret;
	}
    break;

  case 97:
#line 825 "lua.y"
    {
		BinaryOperationType ret = LessEqual;
		(yyval) = (void*)ret;
	}
    break;

  case 98:
#line 832 "lua.y"
    {
		BinaryOperationType ret = More;
		(yyval) = (void*)ret;
	}
    break;

  case 99:
#line 839 "lua.y"
    {
		BinaryOperationType ret = MoreEqual;
		(yyval) = (void*)ret;
	}
    break;

  case 100:
#line 846 "lua.y"
    {
		BinaryOperationType ret = Equal;
		(yyval) = (void*)ret;
	}
    break;

  case 101:
#line 853 "lua.y"
    {
		BinaryOperationType ret = NotEqual;
		(yyval) = (void*)ret;
	}
    break;

  case 102:
#line 860 "lua.y"
    {
		BinaryOperationType ret = And;
		(yyval) = (void*)ret;
	}
    break;

  case 103:
#line 867 "lua.y"
    {
		BinaryOperationType ret = Or;
		(yyval) = (void*)ret;
	}
    break;

  case 104:
#line 874 "lua.y"
    {	
		UnaryOperationType ret = Negate;
		(yyval) = (void*)ret;
	}
    break;

  case 105:
#line 881 "lua.y"
    {	
		UnaryOperationType ret = Not;
		(yyval) = (void*)ret;
	}
    break;

  case 106:
#line 888 "lua.y"
    {	
		UnaryOperationType ret = Lenght;
		(yyval) = (void*)ret;
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2631 "yacc.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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



