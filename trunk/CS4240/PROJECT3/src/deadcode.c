#include "globals.h"
#include "deadcode.h"
#include "code.h"
#include "cfg.h"
#include "dfg.h"

int deadCodeElimination(FUNC *f)
{ BLOCK *blk = f->block;
  int change = FALSE;
  int result = FALSE;
  while(blk)
  { result = eliminateDeadCode(blk);
    if(change == FALSE) change = result;
	blk = blk->next;
  }
/*  createFuncDFG(f);*/
  return change;
}

int eliminateDeadCode(BLOCK *blk)
{ DFGNode *dfgNode = blk->dfg;
  InstructionPointer *used;
  int flag = FALSE;
  int change = FALSE;
  while(dfgNode)
  { used = dfgNode->use;
    while(used)
	{ flag = TRUE;
	  used = used->next;
	  break;
	}
	if(flag == FALSE)
	{ blk->inst = deleteInst(dfgNode->def->inst);
	  change = TRUE;
	}
	dfgNode = dfgNode->next;
	flag = FALSE;
  }
  return change;
}
