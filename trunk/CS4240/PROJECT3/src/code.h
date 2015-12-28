/****************************************************/
/* File: code.h                                     */
/* Code emitting utilities for the LUA compiler     */
/* Haicheng                                         */
/****************************************************/

#ifndef _CODE_H_
#define _CODE_H_

#include <stdarg.h>
#include "globals.h"

/*inst type, each one relates with one structure type*/
typedef enum {AssignI, DeclareFunI, UncondBrI, STI, LDI, LDArrayI, ToIntI,
              CondBrI, BinOpI, CMPI, ToFloatI, LDStructI, GetPtrArrayI,
              AllocI, BitI, InitSI, LDStringI, RetI, AllocStructI, STArrayI,
              AllocArrayI, AllocArrayStackI, CallI, GetPtrI, PrintI, ExtractI} InstKind;

/*scalar type of LLVM, varLen is useless now*/
typedef enum {i1, i1_star, i8, double_float, i8_star, varLen, i32, i32_star, double_star, i8_star2, tab} LLVMType;

typedef struct opecode
{ char *name;
} OPECODE;

typedef struct operand
{ char *name;
} OPERAND;

typedef struct prefix
{ char *name;
} PREFIX;

typedef struct initStringInst
{ OPERAND dst;
  char *string;
  int len;
} InitStringInst;

typedef struct ldStringInst
{ OPERAND dst;
  OPERAND src;
  int len;
} LDStringInst;

typedef struct assignInst
{ OPERAND src;
  OPERAND dst;
  PREFIX prefix;
  LLVMType type;
} AssignInst;

typedef struct tofloatInst
{ OPERAND src;
  OPERAND dst;
} ToFloatInst;

typedef struct tointInst
{ OPERAND src;
  OPERAND dst;
} ToIntInst;

typedef struct uncondBrInst
{ OPERAND dst;
} UncondBrInst;

typedef struct condBrInst
{ OPERAND dstTrue;
  OPERAND dstFalse;
  OPERAND src;
} CondBrInst;

typedef struct storeInst
{ OPERAND src;
  OPERAND dst;
  LLVMType srcType;
  LLVMType dstType;
} StoreInst;

typedef struct storeArrayInst
{ OPERAND src;
  OPERAND dst;
  LLVMType tabType;
  int dimen;
} StoreArrayInst;

typedef struct loadInst
{ OPERAND src;
  OPERAND dst;
  LLVMType srcType;
} LoadInst;

typedef struct loadarrayInst
{ OPERAND src;
  OPERAND dst;
  LLVMType tabType;
  int dimen;
} LoadArrayInst;

typedef struct allocInst
{ OPERAND dst;
  LLVMType type;
} AllocInst;

typedef struct allocArrayStackInst
{ OPERAND dst;
  LLVMType type;
  int dimen;
} AllocArrayStackInst;

typedef struct cmpInst
{ OPERAND src1;
  OPERAND src2;
  OPERAND dst;
  int cond;
  LLVMType type;
} CMPInst;

typedef struct binopInst
{ TokenType opc;
  OPERAND src1;
  OPERAND src2;
  OPERAND dst;
  LLVMType type;
} BinOpInst;

typedef struct bitInst
{ TokenType opc;
  OPERAND src1;
  OPERAND src2;
  OPERAND dst;
  LLVMType type;
} BitInst;

/*doubly linked list for inst*/
typedef struct LLVMInst
{ void *inst;/*points to one kind of inst structure*/
  InstKind instType;
  struct LLVMInst * prev;
  struct LLVMInst * next;
  void *parent; /*points to parent basic block*/
} Inst;

/*global used to malloc and global variables*/
typedef struct LLVMGlobal
{ Inst * lastInst;
  Inst * inst;
  void *parent; 
} GLOBAL;

struct cfgnode; // Forward declair to avoid circular include.

/*data structure for basic block, it is also a doubly linked list*/
typedef struct LLVMBlk
{ Inst * lastInst;/*current last inst of the basic block*/
  Inst * inst;/*points to the doubly linked list of inst*/
  Inst * exitInst;/*the return or break inst of the basic block, the exit of the basic block*/
  struct LLVMBlk * prev;
  struct LLVMBlk * next;  
  struct dfgnode *dfg;
  struct cfgnode *cfg;
  int ignore;
  int breadcrumb;
  void *parent; /*points to the parent func*/
  char *name;/*name of this basic block*/
} BLOCK;

/*stores the information of parameter of a func, a single linked list*/
typedef struct ParTypeRec
{ LLVMType type;
  LLVMType typePtr;
  LLVMType tabType;
  int tabDimen;
  char * name;/*the name of parameter*/
  struct ParTypeRec *next;
} * LLVMArgTypeList;
/*stores the information of return value of a func, a single linked list*/
typedef struct LLVMRetTypeRec
{ LLVMType type;
  LLVMType typePtr;
  LLVMType tabType;
  int tabDimen;
  struct LLVMRetTypeRec *next;
} * LLVMRetTypeList;

typedef struct retInst
{ OPERAND src;
  LLVMRetTypeList typeList;
} RetInst;

typedef struct loadstructInst
{ OPERAND src;
  OPERAND dst;
  LLVMRetTypeList typeList;
} LoadStructInst;

typedef struct getptrInst
{ OPERAND src;
  OPERAND dst;
  LLVMRetTypeList typeList;
  int index;
} GetPtrInst;

typedef struct getptrArrayInst
{ OPERAND src;
  OPERAND dst;
  LLVMType type;
  int dimen;
  char * index;
} GetPtrArrayInst;

typedef struct extractInst
{ OPERAND src;
  OPERAND dst;
  LLVMRetTypeList typeList;
  int index;
} ExtractInst;

typedef struct CallRec
{ LLVMType type;
  LLVMType typePtr;
  LLVMType tabType;
  int tabDimen;
  char * name;
  struct CallRec * next;
} * LLVMCallList;

typedef struct callInst
{ LLVMCallList argList;
  LLVMRetTypeList retList;
  OPERAND src;
  OPERAND dst;
  int isStruct;
} CallInst;

typedef struct printInst
{ LLVMCallList argList;
} PrintInst;

struct cfg;

/*data structure for function, it is also a doubly linked list*/
typedef struct LLVMFunc
{ BLOCK *lastBlock;/*the last block of the func*/
  BLOCK *block;/*points to the block doubly linked list*/
  BLOCK *currBlock;/*the basic block currently working with*/
  struct LLVMFunc * prev;
  struct LLVMFunc * next; 
  struct cfg* funcCFG;
  void *parent; /*points to the parent module*/
  LLVMRetTypeList retType;/*see its def*/
  LLVMArgTypeList parType;/*see its def*/
  char *name;/*the name of the func*/
} FUNC;

typedef struct allocStructInst
{ OPERAND dst;
  LLVMRetTypeList typeList;
} AllocStructInst;

typedef struct allocArrayInst
{ OPERAND dst;
  LLVMType eleType;
  int dimen;
} AllocArrayInst;
/*data structure for module, it is the root of LLVM IR, it includes one global and several funcs*/
typedef struct LLVMMODULE
{ FUNC * function;
  FUNC * lastFunc;
  GLOBAL * global;
} MODULE;

/*mainFunc points to main function, currFunc is the Func currently working with*/
extern FUNC * mainFunc, * currFunc;
/*used to name basic block, temp variable, string constant, print format, tab(array)*/
extern int blkID, tmpID, stringID, printID, tabID;

extern int f2a, scat, scmp, b2a;

GLOBAL * newGlobal(MODULE * m);

MODULE * newModule();

/* code emitting utilities */

/*scalar inst could be used directly, struct related inst need to be defined by you guys, like appendAllocClass...*/
Inst * appendComment( char * c, void *blk, int isGlobal);

Inst * appendInit( char *dst, int val, LLVMType type, char *prefix, void *blk, int isGlobal);

FUNC * appendFunc(char * funcName, LLVMRetTypeList retType, LLVMArgTypeList parType, MODULE * m);

FUNC * insertFunc(char * funcName, LLVMRetTypeList retType, LLVMArgTypeList parType, FUNC * f);

BLOCK * appendBlk(char * blkName, FUNC * func);

Inst * appendUncondBr(char * targetName, BLOCK * blk);

Inst *appendCondBr(char * dstTrue, char * dstFalse, char * src, BLOCK * blk);

Inst * appendST(LLVMType dstType, char *dst, LLVMType srcType, char * src, BLOCK *blk);

Inst * insertST(LLVMType dstType, char *dst, LLVMType srcType, char * src, Inst *inst);

Inst * insertSTArray(LLVMType tabType, int dimen, char *dst, char * src, Inst *inst);

Inst * appendSTArray(LLVMType tabType, int dimen, char *dst, char * src, BLOCK *blk);

Inst * appendLD(char *dst, LLVMType srcType, char *src, BLOCK *blk);

Inst * appendLDArray(char *dst, LLVMType tabType, int dimen, char *src, BLOCK *blk);

Inst * appendCMP(char * dst, LLVMType type, char * src1, char * src2, TokenType opc, BLOCK *blk);

Inst * appendBit(TokenType opc, LLVMType type, char *dst, char * src1, char *src2, BLOCK *blk);

Inst * appendBinOp(TokenType opc, char *dst, LLVMType type, char *src1, char *src2, BLOCK *blk);

Inst * appendInitString(char *dst, char *s, int len, GLOBAL*g);

Inst * appendLDString(char *dst, char *src, int len, BLOCK *blk);

Inst * insertAlloc(char *name, LLVMType type, Inst *inst);

Inst * insertAllocArray(char *name, LLVMType type, int dimen, Inst *inst);

Inst * appendAllocStruct(char *name, LLVMRetTypeList typeList, GLOBAL *g);

Inst * appendAllocArray(char *tabName, LLVMType tabType, int dimen, GLOBAL *g);

Inst * appendRet(LLVMRetTypeList retType, char * src, BLOCK * blk);

Inst * appendGetPtr(char * dst, char * src, LLVMRetTypeList retType, int index, BLOCK * blk);

Inst * appendGetPtrArray(char *dst, char *src, LLVMType type, int dimen, char *id, BLOCK * blk);

Inst * appendExtract(char * dst, char * src, LLVMRetTypeList retType, int index, BLOCK * blk);

Inst * appendCall(char * dst, LLVMRetTypeList retList, char * src, LLVMCallList callList, BLOCK * blk, int isStruct);

Inst * appendToFloat(char *to, char *from, BLOCK * blk);

Inst * appendToInt(char *to, char *from, BLOCK * blk);

Inst * appendPrint(LLVMCallList argList, BLOCK * blk);

Inst * appendLDstruct(char * dst, LLVMRetTypeList retType, char * src, BLOCK * blk);

void printModule(MODULE *m);

Inst * deleteInst(Inst *inst);

BLOCK * deleteBlk(BLOCK *blk);

int IsFloat(char *buf, float *num);

int IsInt(char *buf, int *num);

int IntToChar(char *buf, int num);

int FloatToChar(char *buf, float num);

#endif
