#ifndef DFG_H
#define DFG_H

#include "code.h"

extern int DFGTrace;

typedef struct pointerToInstruction
{ Inst *inst;
  struct pointerToInstruction *next;
  struct pointerToInstruction *prev;
}InstructionPointer;

/* Structure to hold DFG nodes */
typedef struct dfgnode 
{ char * regName; /* the register name of this def-usr chain*/
  InstructionPointer *def; /*every value is defined in one place*/
  InstructionPointer *use; /*a doubly linked list*/
  struct dfgnode *prev; /*the previous DFG node*/
  struct dfgnode *next; /*the next DFG node*/
} DFGNode;

/* Function prototypes */
void createModuleDFG(MODULE *m);
void createFuncDFG(FUNC *f);
void createUseChain(Inst *inst, DFGNode *dfgNode, char *def, BLOCK *block);
DFGNode * DFGBuild(BLOCK *blk);
DFGNode * DFGCreate(BLOCK * blk);
DFGNode * newDFGNode();
InstructionPointer * newInstructionNode();
void freeDFG(DFGNode *dfg);

#endif
