#include "globals.h"
#include "code.h"
#include "rmunreachable.h"

int findPred(FUNC *f, BLOCK *targetBlk)
{ int found = FALSE;
  BLOCK *blk = f->block;

  while (blk)
  { 
    switch (blk->lastInst->instType)
    {
      case UncondBrI:
      { UncondBrInst* uncondBrInst = (UncondBrInst*)blk->lastInst->inst;

        if (strcmp(uncondBrInst->dst.name, targetBlk->name) == 0)
          found = TRUE;
      }

        break;
      case CondBrI:
      { CondBrInst* condBrInst = (CondBrInst*)blk->lastInst->inst;
        
        if (strcmp(condBrInst->dstTrue.name, targetBlk->name) == 0
         || strcmp(condBrInst->dstFalse.name, targetBlk->name) == 0)
          found = TRUE;
      }

        break;
      default:
        break;
    }
      
    if (found == TRUE) break;
    
    blk = blk->next;
  }

  return found;
}

int rmUnreachable(FUNC *f)
{ BLOCK *blk = f->block;
  
  while (blk)
  {
    if (strcmp(blk->name, "entry") != 0 && findPred(f, blk) == FALSE)
      blk = deleteBlk(blk);
    else
      blk = blk->next;
  }
  
  return FALSE;
}
