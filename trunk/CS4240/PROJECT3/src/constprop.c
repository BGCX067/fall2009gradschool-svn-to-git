#include "globals.h"
#include "constprop.h"
#include "code.h"
#include "cfg.h"
#include "dfg.h"


int constProp(FUNC *f)
{ BLOCK *blk = f->block;
  int change = FALSE;
  int result = FALSE;
  while( blk != NULL)
  { result = blockConstProp(blk);
    if(change == FALSE) change = result;
    blk = blk->next;
  }
  condToUncond(f);
/*  createFuncDFG(f);*/
  return change;
}

int blockConstProp(BLOCK * blk) 
{ Inst *inst = blk->inst;
  OPERAND def, use1, use2;
  int defFlag = FALSE;
  float fval1 = 0, fval2 = 0, ftotal = 0;
  int ival1 = 0, ival2 = 0, itotal = 0;
  int change = FALSE;
  int result = FALSE;
  int iFlag = 0;
  int fFlag = 0;

  while(inst != NULL)
  { ftotal = 0;
    itotal = 0;
    defFlag = 0;
    iFlag = FALSE;
    fFlag = FALSE;
	def.name = NULL;
    switch(inst->instType)
	{
	  case BinOpI:
	    def.name = ((BinOpInst *)inst->inst)->dst.name;
	    use1.name = ((BinOpInst *)inst->inst)->src1.name;
	    use2.name = ((BinOpInst *)inst->inst)->src2.name;
		if(IsFloat(use1.name,&fval1))
		{ defFlag = defFlag | 0x1;
		  ival1 = (int)fval1;
		}
		if(IsFloat(use2.name,&fval2))
		{ ival2 = (int)fval2;
		  defFlag = defFlag | 0x2;
		}
		switch(((BinOpInst *)inst->inst)->opc)
		{
		  case PLUS:
		    if((((BinOpInst *)inst->inst)->type == i1) || (((BinOpInst *)inst->inst)->type == i8) || (((BinOpInst *)inst->inst)->type == i32))
			{ iFlag = TRUE;
              itotal = ival1+ival2;
			}
		    if(((BinOpInst *)inst->inst)->type == double_float)
			{ fFlag = TRUE;
              ftotal = fval1+fval2;
			}
			break;
          case MINUS:
		    if((((BinOpInst *)inst->inst)->type == i1) || (((BinOpInst *)inst->inst)->type == i8) || (((BinOpInst *)inst->inst)->type == i32))
			{ iFlag = TRUE;
              itotal = ival1-ival2;
			}
		    if(((BinOpInst *)inst->inst)->type == double_float)
			{ fFlag = TRUE;
              ftotal = fval1-fval2;
			}
            break;
          case TIMES:
		    if((((BinOpInst *)inst->inst)->type == i1) || (((BinOpInst *)inst->inst)->type == i8) || (((BinOpInst *)inst->inst)->type == i32))
			{ iFlag = TRUE;
              itotal = ival1*ival2;
			}
		    if(((BinOpInst *)inst->inst)->type == double_float)
			{ fFlag = TRUE;
              ftotal = fval1*fval2;
			}
            break;
          case OVER:
		    if((((BinOpInst *)inst->inst)->type == i1) || (((BinOpInst *)inst->inst)->type == i8) || (((BinOpInst *)inst->inst)->type == i32))
			{ iFlag = TRUE;
              itotal = ival1/ival2;
			}
		    if(((BinOpInst *)inst->inst)->type == double_float)
			{ fFlag = TRUE;
              ftotal = fval1/fval2;
			}
            break;
          case MOD:
		    if((((BinOpInst *)inst->inst)->type == i1) || (((BinOpInst *)inst->inst)->type == i8) || (((BinOpInst *)inst->inst)->type == i32))
			{ iFlag = TRUE;
              itotal = ival1%ival2;
			}
		    if(((BinOpInst *)inst->inst)->type == double_float)
			{ fFlag = TRUE;
		      ftotal = fval1 - (int)(fval1/fval2)*fval2;
			}
            break;
		  default:
		    break;
		}
		if(defFlag == 3)
		{ if(fFlag == TRUE)
		  {
		    result = replaceWithConstFloat(inst,def.name,blk,ftotal);
		    if (change == FALSE) change = result;
		  }
		  if(iFlag == TRUE)
		  {
		    result = replaceWithConstInt(inst,def.name,blk,itotal);
		    if (change == FALSE) change = result;
		  }
		}
	    break;
	  case CMPI:
	    def.name = ((CMPInst *)inst->inst)->dst.name;
	    use1.name = ((CMPInst *)inst->inst)->src1.name;
	    use2.name = ((CMPInst *)inst->inst)->src2.name;
		if(IsFloat(use1.name,&fval1))
		{ defFlag = defFlag | 0x1;
		}
		if(IsFloat(use2.name,&fval2))
		{ defFlag = defFlag | 0x2;
		}
		switch(((CMPInst *)inst->inst)->cond)
		{
		  case EQ:
		    if(fval1 == fval2)
			  ftotal = 1;
			else
			  ftotal = 0;
            break;
          case NEQ:
		    if(fval1 != fval2)
			  ftotal = 1;
			else
			  ftotal = 0;
            break;
          case LE:
		    if(fval1 <= fval2)
			  ftotal = 1;
			else
			  ftotal = 0;
            break;
          case GE:
		    if(fval1 >= fval2)
			  ftotal = 1;
			else
			  ftotal = 0;
            break;
          case LT:
		    if(fval1 < fval2)
			  ftotal = 1;
			else
			  ftotal = 0;
            break;
          case GT:
		    if(fval1 > fval2)
			  ftotal = 1;
			else
			  ftotal = 0;
            break;
          default:
            break;      
		}
		if(defFlag == 3)
		{ result = replaceWithConstFloat(inst,def.name,blk,ftotal);
		  if (change == FALSE) change = result;
		}
	    break;
	  default:
		break;
	}
	inst = inst->next;
  }
  return change;
}

int replaceWithConstFloat(Inst *instruction, char *def, BLOCK *block, float num)
{ OPERAND use1;
  OPERAND use2;
  BLOCK *blk = block;
  Inst *inst = instruction;
  int callFlag = FALSE;
  int change = FALSE;
  char *tmp = NULL;
  while(blk)
  {
  while(inst != NULL)
  {
	use1.name = NULL;
	use2.name = NULL;
	tmp = NULL;
    switch(inst->instType)
	{
	  case LDI:
	    use1.name = ((LoadInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((LoadInst *)inst->inst)->src.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
	    break;
	  case AssignI:
        use1.name = ((AssignInst *)inst->inst)->dst.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((AssignInst *)inst->inst)->src.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case STI:
        use1.name = ((StoreInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((StoreInst *)inst->inst)->src.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;

      case CondBrI:
        use1.name = ((CondBrInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((CondBrInst *)inst->inst)->src.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case BinOpI:
        use1.name = ((BinOpInst *)inst->inst)->src1.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((BinOpInst *)inst->inst)->src1.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        use2.name = ((BinOpInst *)inst->inst)->src2.name;
		if(def && use2.name && (strcmp(def,use2.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((BinOpInst *)inst->inst)->src2.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case CMPI:
        use1.name = ((CMPInst *)inst->inst)->src1.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((CMPInst *)inst->inst)->src1.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        use2.name = ((CMPInst *)inst->inst)->src2.name;
		if(def && use2.name && (strcmp(def,use2.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((CMPInst *)inst->inst)->src2.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
		/*
      case BitI:
        use1.name = ((BitInst *)inst->inst)->src1.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((BitInst *)inst->inst)->src1.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        use2.name = ((BitInst *)inst->inst)->src2.name;
		if(def && use2.name && (strcmp(def,use2.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((BitInst *)inst->inst)->src2.name = tmp;
	      FLoatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
		*/
      case RetI:
        if(((RetInst *)inst->inst)->typeList != NULL)
		{
          use1.name = ((RetInst *)inst->inst)->src.name;
		  if(def && use1.name && (strcmp(def,use1.name)==0))
	      { tmp =  (char *)malloc(256);
	        ((RetInst *)inst->inst)->src.name = tmp;
	        FloatToChar(tmp,num);
		    change = TRUE;
	      }
		}
        break;
      case ToFloatI:
        use1.name = ((ToFloatInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((ToFloatInst *)inst->inst)->src.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case ToIntI:
        use1.name = ((ToIntInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((ToIntInst *)inst->inst)->src.name = tmp;
	      FloatToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      default:
        break;
	}
	callFlag = FALSE;
	inst = inst->next;
  }
  blk = blk->next;
  if(blk) inst = blk->inst;
  }
  return change;
}

int replaceWithConstInt(Inst *instruction, char *def, BLOCK *block, int num)
{ OPERAND use1;
  OPERAND use2;
  BLOCK *blk = block;
  Inst *inst = instruction;
  int callFlag = FALSE;
  int change = FALSE;
  char *tmp = NULL;
  while(blk)
  {
  while(inst != NULL)
  {
	use1.name = NULL;
	use2.name = NULL;
	tmp = NULL;
    switch(inst->instType)
	{
	  case LDI:
	    use1.name = ((LoadInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((LoadInst *)inst->inst)->src.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
	    break;
	  case AssignI:
        use1.name = ((AssignInst *)inst->inst)->dst.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((AssignInst *)inst->inst)->src.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case STI:
        use1.name = ((StoreInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((StoreInst *)inst->inst)->src.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;

      case CondBrI:
        use1.name = ((CondBrInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((CondBrInst *)inst->inst)->src.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case BinOpI:
        use1.name = ((BinOpInst *)inst->inst)->src1.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((BinOpInst *)inst->inst)->src1.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        use2.name = ((BinOpInst *)inst->inst)->src2.name;
		if(def && use2.name && (strcmp(def,use2.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((BinOpInst *)inst->inst)->src2.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case CMPI:
        use1.name = ((CMPInst *)inst->inst)->src1.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((CMPInst *)inst->inst)->src1.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        use2.name = ((CMPInst *)inst->inst)->src2.name;
		if(def && use2.name && (strcmp(def,use2.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((CMPInst *)inst->inst)->src2.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case RetI:
        if(((RetInst *)inst->inst)->typeList != NULL)
		{
          use1.name = ((RetInst *)inst->inst)->src.name;
		  if(def && use1.name && (strcmp(def,use1.name)==0))
	      { tmp =  (char *)malloc(256);
	        ((RetInst *)inst->inst)->src.name = tmp;
	        IntToChar(tmp,num);
		    change = TRUE;
	      }
		}
        break;
      case ToFloatI:
        use1.name = ((ToFloatInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((ToFloatInst *)inst->inst)->src.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      case ToIntI:
        use1.name = ((ToIntInst *)inst->inst)->src.name;
		if(def && use1.name && (strcmp(def,use1.name)==0))
	    { tmp =  (char *)malloc(256);
	      ((ToIntInst *)inst->inst)->src.name = tmp;
	      IntToChar(tmp,num);
		  change = TRUE;
	    }
        break;
      default:
        break;
	}
	callFlag = FALSE;
	inst = inst->next;
  }
  blk = blk->next;
  if(blk) inst = blk->inst;
  }
  return change;
}

void condToUncond(FUNC *f)
{ BLOCK *blk = f->block;
  while( blk != NULL)
  { changeToUncond(blk);
    blk = blk->next;
  }
}

void changeToUncond(BLOCK *blk)
{
  Inst *inst = blk->inst;
  Inst *tmp1 = NULL;
  Inst *tmp2 = NULL;
  OPERAND def, use1, use2;
  int val = 0;
  while(inst != NULL)
  { def.name = NULL;
    use1.name = NULL;
    use2.name = NULL;
    switch(inst->instType)
	{
	  case CondBrI:
	    def.name = ((CondBrInst *)inst->inst)->src.name;
	    use1.name = ((CondBrInst *)inst->inst)->dstTrue.name;
	    use2.name = ((CondBrInst *)inst->inst)->dstFalse.name;
		if(IsInt(def.name,&val))
		{
		  tmp1 = inst;
		  if(val == 1)
		    tmp2 = appendUncondBr(use1.name,blk);
		  else
		    tmp2 = appendUncondBr(use2.name,blk);
		  tmp1->prev->next = tmp2;
		  tmp2->prev = tmp1->prev;
		}
	    break;
	  default:
		break;
	}
	inst = inst->next;
  }
}

