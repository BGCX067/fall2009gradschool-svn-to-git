#include "globals.h"
#include "cse.h"
#include "code.h"
#include "cfg.h"
#include "dfg.h"

Inst *findFrom(Inst *inst)
{ Inst *tmp = inst;

  while(tmp)
  {
    if (tmp->instType == BinOpI || tmp->instType == BitI)
      break;
    
    tmp = tmp->next;
  }
  
  return tmp;
}

int compareSrc(Inst *from, Inst *to, InstKind instType)
{ char *src11, *src12, *src21, *src22;
  
  if (instType == BinOpI)
  { src11 = ((BinOpInst *)from->inst)->src1.name;
    src12 = ((BinOpInst *)from->inst)->src2.name;
    src21 = ((BinOpInst *)to->inst)->src1.name;
    src22 = ((BinOpInst *)to->inst)->src2.name;
  }
  else if (instType == BitI)
  { src11 = ((BitInst *)from->inst)->src1.name;
    src12 = ((BitInst *)from->inst)->src2.name;
    src21 = ((BitInst *)to->inst)->src1.name;
    src22 = ((BitInst *)to->inst)->src2.name;
  }
  
  if (((strcmp(src11, src21) == 0) && (strcmp(src12, src22) == 0))
   || ((strcmp(src11, src22) == 0) && (strcmp(src12, src21) == 0)))
     return TRUE;
  else
     return FALSE;
}

void replace(Inst *from, Inst *to, InstKind instType)
{ Inst *inst = to->next;
  OPERAND use1;
  OPERAND use2;
  BLOCK *blk = to->parent;
  char *rep; 
  char *def;
  
  if (instType == BinOpI)
  { rep = ((BinOpInst *)from->inst)->dst.name;
    def = ((BinOpInst *)to->inst)->dst.name;
  }
  else if (instType == BitI)
  { rep = ((BitInst *)from->inst)->dst.name;
    def = ((BitInst *)to->inst)->dst.name;
  }

  char *tmp = NULL;
  
  deleteInst(to);


  while(blk)
  {
    while(inst)
    { use1.name = NULL;
      use2.name = NULL;
      tmp = NULL;
      
      switch(inst->instType)
      {
      case LDI:
        use1.name = ((LoadInst *)inst->inst)->src.name;

        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((LoadInst *)inst->inst)->src.name = tmp;
        }
        break;
        
      case AssignI:
        use1.name = ((AssignInst *)inst->inst)->dst.name;

        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((AssignInst *)inst->inst)->src.name = tmp;
        }
        break;
      case STI:
        use1.name = ((StoreInst *)inst->inst)->src.name;

        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((StoreInst *)inst->inst)->src.name = tmp;
        }
        break;

      case CondBrI:
        use1.name = ((CondBrInst *)inst->inst)->src.name;

        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((CondBrInst *)inst->inst)->src.name = tmp;
        }
        break;
      case BinOpI:
        use1.name = ((BinOpInst *)inst->inst)->src1.name;

        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((BinOpInst *)inst->inst)->src1.name = tmp;
        }

        use2.name = ((BinOpInst *)inst->inst)->src2.name;

        if(def && use2.name && (strcmp(def,use2.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((BinOpInst *)inst->inst)->src2.name = tmp;
        }
        
        break;
      case CMPI:
        use1.name = ((CMPInst *)inst->inst)->src1.name;

        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((CMPInst *)inst->inst)->src1.name = tmp;
        }
        
        use2.name = ((CMPInst *)inst->inst)->src2.name;
        
        if(def && use2.name && (strcmp(def,use2.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((CMPInst *)inst->inst)->src2.name = tmp;
        }
        
        break;

      case BitI:
        use1.name = ((BitInst *)inst->inst)->src1.name;
        
        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((BitInst *)inst->inst)->src1.name = tmp;
        }

        use2.name = ((BitInst *)inst->inst)->src2.name;

        if(def && use2.name && (strcmp(def,use2.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((BitInst *)inst->inst)->src2.name = tmp;
        }
        break;

      case RetI:
        if(((RetInst *)inst->inst)->typeList != NULL)
        {
          use1.name = ((RetInst *)inst->inst)->src.name;

          if(def && use1.name && (strcmp(def,use1.name)==0))
          { tmp =  (char *)malloc(256);
            strcpy(tmp, rep);
            ((RetInst *)inst->inst)->src.name = tmp;
	        }
        }
        
        break;
      case CallI:
      { LLVMCallList argList = ((CallInst *)inst->inst)->argList;

        while(argList)
        { if(strcmp(def, argList->name) == 0)
          { tmp = (char *)malloc(256);
            strcpy(tmp, rep);
            argList->name = tmp;
          }
          argList = argList->next;
        }
      }

        break;
      case ToFloatI:
        use1.name = ((ToFloatInst *)inst->inst)->src.name;
        
        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((ToFloatInst *)inst->inst)->src.name = tmp;
        }
        break;
      case ToIntI:
        use1.name = ((ToIntInst *)inst->inst)->src.name;
        if(def && use1.name && (strcmp(def,use1.name)==0))
        { tmp =  (char *)malloc(256);
          strcpy(tmp, rep);
          ((ToIntInst *)inst->inst)->src.name = tmp;
        }
        break;
      default:
        break;
      }

      inst = inst->next;
    }
    
    blk = blk->next;
    if(blk) inst = blk->inst;
  }
}

void findTo(Inst *from)
{ Inst *tmp = from->next;
  Inst *to = NULL;
  InstKind instType = from->instType;
  TokenType opc;
  
  if (from->instType == BinOpI)
    opc = ((BinOpInst *)from->inst)->opc;
  else if(from->instType == BitI)
    opc = ((BitInst *)from->inst)->opc; 

  while(tmp)
  {
    if (tmp->instType == instType)
      if (instType == BinOpI)
      {
        if(((BinOpInst *)tmp->inst)->opc == opc)
          if(compareSrc(from, tmp, BinOpI))
          { to = tmp;
            replace(from, to, BinOpI);
          }
      }
      else if (instType == BitI)
      {
        if(((BitInst *)tmp->inst)->opc == opc)
          if(compareSrc(from, tmp, BitI))
          { to = tmp;
            replace(from, to, BitI);
          }
      }

    tmp = tmp->next;
  }
}

void localCSE(BLOCK *blk)
{ Inst *inst = blk->inst;
  Inst *from;
  
  while (inst) {
    from = findFrom(inst);
    
    if (from == NULL) break;
    
    findTo(from);
    
    inst = from->next;
  }
}

int cse(FUNC *f)
{ BLOCK *blk = f->block;

  while( blk != NULL)
  { localCSE(blk);

    blk = blk->next;
  }

  return FALSE;
}
