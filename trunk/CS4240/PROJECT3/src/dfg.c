#include "dfg.h"

DFGNode *DFGCreate(BLOCK * blk)
{

}

void createModuleDFG(MODULE *m)
{ FUNC *f = m->function;
  if(DFGTrace) 
    printf("\n-------------------- Start of DFG -------------------------\n");
  while(f != NULL)
  { if(DFGTrace) 
      printf("\nFunction Name: %s\n",f->name);
    createFuncDFG(f);
	f = f->next;
  }
  if(DFGTrace) 
    printf("\n----------------------- End of DGF ------------------------\n\n");
}

void createFuncDFG(FUNC *f)
{ BLOCK *blk = f->block;
  while( blk != NULL)
  { if(DFGTrace)
      printf("\tBasic Block Name: %s\n",blk->name);
    DFGBuild(blk);
    blk = blk->next;
  }
}

DFGNode * DFGBuild(BLOCK *blk)
{ Inst *inst = blk->inst;
  BLOCK *block = blk;
  OPERAND def;
  int defFlag = FALSE;
  blk->dfg = NULL;
  DFGNode *dfgNode = blk->dfg;
  DFGNode *temp = NULL;
  while(inst != NULL)
  { switch(inst->instType)
	{
	  case AssignI:
	    def.name = ((AssignInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
	  case UncondBrI:
	    def.name = ((UncondBrInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
	  case LDI:
	    def.name = ((LoadInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
	  case LDArrayI:
	    def.name = ((LoadArrayInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
	  case BinOpI:
	    def.name = ((BinOpInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
	  case BitI:
	    def.name = ((BitInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
	  case CMPI:
	    def.name = ((CMPInst *)inst->inst)->dst.name;
	    defFlag = TRUE;
	    break;
		/*
	  case AllocI:
	    def.name = ((AllocInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case AllocArrayStackI:
	    def.name = ((AllocArrayStackInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
		*/
	  case InitSI:
	    def.name = ((InitStringInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case LDStringI:
	    def.name = ((LDStringInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
		/*
	  case AllocStructI:
	    def.name = ((AllocStructInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case AllocArrayI:
	    def.name = ((AllocArrayInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
		*/
	  case CallI:
	    if(((CallInst *)inst->inst)->dst.name != NULL)
		{ def.name = ((CallInst *)inst->inst)->dst.name;
		  defFlag = TRUE;
		}
		break;
	  case GetPtrI:
	    def.name = ((GetPtrInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case GetPtrArrayI:
	    def.name = ((GetPtrArrayInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case ExtractI:
	    def.name = ((ExtractInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case ToFloatI:
	    def.name = ((ToFloatInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  case ToIntI:
	    def.name = ((ToIntInst *)inst->inst)->dst.name;
		defFlag = TRUE;
		break;
	  default:
	    defFlag = FALSE;
	    break;
	}
	if(defFlag == TRUE)
	{ if(dfgNode == NULL)
	  { temp = newDFGNode();
	    temp->prev = NULL;
		temp->next = NULL;
		temp->regName = malloc(strlen(def.name));
	    strcpy(temp->regName,def.name);
		temp->def = newInstructionNode();
		temp->def->inst = inst;
		dfgNode = temp;
		createUseChain(inst,temp, def.name, block);
	  }
	  else
	  { temp = dfgNode;
	    while(temp->next) temp = temp->next;
	    temp->next = newDFGNode();
		temp->next->regName = malloc(strlen(def.name));
	    strcpy(temp->next->regName,def.name);
		temp->next->def = newInstructionNode();
		temp->next->def->inst = inst;
		temp->next->prev = temp;
		temp->next->next = NULL;
		createUseChain(inst,temp->next, def.name, block);
	  }
	}
	defFlag = FALSE;
	inst = inst->next;
  }
  blk->dfg = dfgNode;
  if(DFGTrace) printDFG(blk);
}

void createUseChain(Inst *instruction, DFGNode *dfgNode, char *def, BLOCK *block)
{ OPERAND use1;
  OPERAND use2;
  BLOCK *blk = block;
  Inst *inst = instruction;
  InstructionPointer *temp;
  LLVMCallList t;
  int callFlag = FALSE;
  int useFlag = FALSE;
  dfgNode->use = NULL;
  while(blk)
  {
  while(inst != NULL)
  {
	use1.name = NULL;
	use2.name = NULL;
    switch(inst->instType)
	{
	  case LDI:
	    use1.name = ((LoadInst *)inst->inst)->src.name;
	    useFlag = TRUE;
	    break;
	  case AssignI:
        use1.name = ((AssignInst *)inst->inst)->src.name;
		useFlag = TRUE;
        break;
      case UncondBrI:
        use1.name = ((UncondBrInst *)inst->inst)->dst.name;
		useFlag = TRUE;
        break;
      case STI:
        use1.name = ((StoreInst *)inst->inst)->src.name;
        use2.name = ((StoreInst *)inst->inst)->dst.name;
		useFlag = TRUE;
        break;
      case STArrayI:
        use1.name = ((StoreArrayInst *)inst->inst)->src.name;
        use1.name = ((StoreArrayInst *)inst->inst)->dst.name;
		useFlag = TRUE;
        break;
      case CondBrI:
        use1.name = ((CondBrInst *)inst->inst)->src.name;
		useFlag = TRUE;
        break;
      case BinOpI:
        use1.name = ((BinOpInst *)inst->inst)->src1.name;
        use2.name = ((BinOpInst *)inst->inst)->src2.name;
		useFlag = TRUE;
        break;
      case CMPI:
        use1.name = ((CMPInst *)inst->inst)->src1.name;
        use2.name = ((CMPInst *)inst->inst)->src2.name;
		useFlag = TRUE;
        break;
      case BitI:
        use1.name = ((BitInst *)inst->inst)->src1.name;
        use2.name = ((BitInst *)inst->inst)->src2.name;
		useFlag = TRUE;
        break;
      case LDStringI:
        use1.name = ((LDStringInst *)inst->inst)->src.name;
		useFlag = TRUE;
        break;
      case RetI:
        if(((RetInst *)inst->inst)->typeList != NULL)
          use1.name = ((RetInst *)inst->inst)->src.name;
		useFlag = TRUE;
        break;
		
      case CallI:
		t = ((CallInst *)inst->inst)->argList;
		while(t)
		{ use1.name = t->name;
		  if(strcmp(def,use1.name)==0)
		  { callFlag = TRUE;
		    break;
		  }
		  t = t->next;
		}
		useFlag = TRUE;
        break;
	
      case GetPtrI:
        use1.name = ((GetPtrInst *) inst->inst)->src.name;
		useFlag = TRUE;
        break;
      case GetPtrArrayI:
        use1.name = ((GetPtrArrayInst *) inst->inst)->src.name;
        use2.name = ((GetPtrArrayInst *) inst->inst)->index;
		useFlag = TRUE;
        break;
      case ExtractI:
        use1.name = ((ExtractInst *) inst->inst)->src.name;
		useFlag = TRUE;
        break;
		
      case PrintI:
		t = ((PrintInst *)inst->inst)->argList;
		while(t)
		{ use1.name = t->name;
		  if(strcmp(def,use1.name)==0)
		  { callFlag = TRUE;
		    break;
		  }
		  t = t->next;
		}
		useFlag = TRUE;
        break;

      case LDStructI:
        use1.name = ((LoadStructInst *) inst->inst)->src.name;
		useFlag = TRUE;
        break;
      case ToFloatI:
        use1.name = ((ToFloatInst *)inst->inst)->src.name;
		useFlag = TRUE;
        break;
      case ToIntI:
        use1.name = ((ToIntInst *)inst->inst)->src.name;
		useFlag = TRUE;
        break;
      default:
        Error = TRUE;
		useFlag = FALSE;
        break;
	}
	if(useFlag == TRUE)
	{
	  if((def && use1.name && strcmp(def,use1.name)==0)||( def && use2.name && strcmp(def,use2.name)==0) || (callFlag==TRUE))
	  { 
	    if(dfgNode->use == NULL)
	    { temp = newInstructionNode();
	      temp->inst = inst;
	      temp->prev = NULL;
		  temp->next = NULL;
		  dfgNode->use = temp;
	    }
	    else
	    { temp = dfgNode->use;
	      while(temp->next) temp = temp->next;
		  temp->next = newInstructionNode();
		  temp->next->inst = inst;
		  temp->next->prev = temp;
		  temp->next->next = NULL;
	    }
	  }
	}
	callFlag = FALSE;
	useFlag = FALSE;
	inst = inst->next;
  }
  blk = blk->next;
  if(blk) inst = blk->inst;
  }
}

DFGNode * newDFGNode()
{ DFGNode *dfgNode = NULL;
  dfgNode = (DFGNode *)malloc(sizeof(DFGNode));
  return dfgNode;
}

InstructionPointer * newInstructionNode()
{ InstructionPointer *inst = NULL;
  inst = (InstructionPointer *)malloc(sizeof(InstructionPointer));
  inst->inst = NULL;
  inst->next = NULL;
  inst->prev = NULL;
  return inst;
}

void freeDFG(DFGNode *dfgNode)
{
 DFGNode *dfg = dfgNode;
 DFGNode *temp = NULL;
 InstructionPointer *inst = NULL;
 while(dfg)
 {
   temp = dfg;
   dfg = dfg->next;
   free(temp->regName);
   free(temp->def);
   while(temp->use)
   {
     inst = temp->use;
	 temp->use = temp->use->next;
	 free(inst);
   }
   free(temp);
   temp = NULL;
 }
}
