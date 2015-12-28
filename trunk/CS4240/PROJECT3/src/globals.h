/****************************************************/
/* File: globals.h                                 */
/* Global types and vars for LUA compiler          */
/* must come before other include files            */
/* Haicheng                                        */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header")
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself
 */

#ifndef YYPARSER

/* the name of the following file may change */
#include "lua.tab.h"

/* ENDFILE is implicitly defined by Yacc/Bison,
 * and not included in the tab.h file
 */
#define ENDFILE 0

#endif

#define Nil 0

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef BOOL
#define BOOL int
#endif


/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 21

/* Yacc/Bison generates its own integer values
 * for tokens
 */
typedef int TokenType; 

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code;

extern int lineno; /* source line number for listing */
extern int firstTime;

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {AssignK, FunCallK, DoK, WhileK, RepeatK, IfK, ElseIfK, ElseK, ForNumK, 
              FunK, LocFunK, LocAssignK, ReturnK, BreakK} StmtKind;
typedef enum {BoolConstK, RealConstK, StringConstK, VarLenK, PreK, TabK, 
              BinOpK, UnOpK, IdK, VarK, FunBodyK, FieldK} ExpKind;

/* ExpType is used for type checking */
typedef enum {NilTy, Boolean, Number, String, Function, Table} ExpType;

#define MAXCHILDREN 12

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/*useless*/
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/*symbol table entry*/
typedef struct BucketListRec
   { char * name;/*symbol name*/
     LineList lines;/*useless*/
     int memloc ; /* useless memory location for variable */
     struct BucketListRec * next;/*used for maintain hash list*/
     ExpType type;/*the type of symbol, ie String, Boolean, Number, Function, Table*/
     ExpType tabType;/*if the type is table, it stores the element type*/
     int tabEleNum;/*if the type is table, it stores the element num*/
     int tabDimen;
     /*if this entry type is function, it points to the symbol table belonging to this func*/
     void *ptr;
     char *loc;/*it stores the heap address of the symbol*/
     int isPar;/*whether this symbol is a parameter of function*/
   } * BucketList;

/*ret type info of a function, it is list*/
typedef struct RetTypeRec
   { ExpType type;/*Boolean? String? Number? Table? ...*/
     ExpType tabType;/*if it is a table, it records the table element type*/
     int tabEleNum;/*if it is a table, it records the table element number*/
     int tabDimen;
     struct RetTypeRec *next;/*maintain a list*/
   } * RetTypeList;
/*fun parameter info, it is list*/
typedef struct ArgTypeRec
   { BucketList arg;/*it points to a symbol table entry belonging to this function parameter*/
     struct ArgTypeRec *next;/*maintain a list*/
   } * ArgTypeList;
/*useless*/
typedef struct VarArgTypeRec
   { ExpType type;
     ExpType tabType;
     int tabEleNum;
     struct VarArgTypeRec *next;
   } * VarArgTypeList;
/*symbol table*/
typedef struct HashTableRec
   { BucketList table[SIZE];/*hash table used to store symbols*/
      /*used to maintain the tree structure of symbol table*/
     struct HashTableRec * child;
     struct HashTableRec * sibling;
     struct HashTableRec * parent;
     
     /*if this table belong to a func, retType stores ret value info and argtype stores arg value info, see their def*/
     RetTypeList retType;
     ArgTypeList argType;
     /*useless*/
     VarArgTypeList varArgType;
     /*it points to a LLVMRetTypeList type pointer, see the def of LLVMRetTypeList(in code.h), only useful in func symtab*/
     void * llvmPtr;
   } HashTable;
   
/*LLVM variables store the func call return values. see the def of tree node*/
typedef struct CallRetRec
   { char *regName;/*LLVM temp variable's name, ie %main.bb67.tmp433*/
     int type;/*ret value's type, in LLVM way, ie double_float, i8_star...*/
     int typePtr;/*ret value's pointer type, in LLVM way, ie double_star, i8_star2*/
     int tabType;/*if the ret val is a table, it records the table element type*/
     int tabEleNum;/*if the ret val is a table, it records the table element num*/
     int tabDimen;
     struct CallRetRec *next;/*used to establish a chain*/
   } * CallRetList;

 /*node of syntax tree, most important data structure, it is initialized in util.c*/
 typedef struct treeNode
   { /*child and sibling are used to build syntax tree*/
     struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     
     int lineno;/*useless*/
     
     NodeKind nodekind;/*stmt or exp*/
     
     /*detail node kind info*/
     union { StmtKind stmt; ExpKind exp;} kind;
     
     /*node attribute info*/
     union { TokenType op;/*used for binop and unop: PLUS, MINUS...*/
             int boolVal;/*boolean constant value, only used in bool constant node*/
             double realVal;/*float constant value, only used in number constant node (interger treated as float)*/
             char * name; /*used for store identifier's name, only used in IdK node*/} attr;
             
     /* for type checking of exps, all exp node(include fun call node) should have a type after type inference */
     ExpType type; 
     /*only used in array, record the array element type, set in type infer*/
     ExpType tabType;
     /*only used in array, record the length of the array, set in type infer*/
     int tabEleNum;
     /*record child num of the node, set in bison*/
     int tabDimen;
     
     int childNum;
     /*record child num of the node, set in flex*/
     int siblingNum;
     /*if this node is a funK, it points to the associate symtab*/
     HashTable * funSymTab;
     /*useless*/
     void *ptr;
     /*used in code gen, it stores the LLVM variable for this node, all exp node should have its own LLVM variable*/
     char *regName;
     /*used in assignK of array now, it contains the address of x[i]. it is used and set in code gen. oo programming may use it*/
     char *ptrName;
     /*used in code gen, it stores the LLVM variable storing the return value of function call, see the def of CallRetList*/
     CallRetList retRegs;
   } TreeNode; 
   
/*useless*/
typedef struct TableEleRec
   { TreeNode *index;
     struct TableEleRec *next;
   } * TableEleList;
/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
