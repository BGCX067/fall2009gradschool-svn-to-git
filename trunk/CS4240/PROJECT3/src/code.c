/****************************************************/
/* File: code.c                                     */
/* LUA Code emitting utilities                      */
/* implementation for the LUA compiler              */
/* Haicheng                                         */
/****************************************************/

#include "globals.h"
#include "code.h"

FUNC * mainFunc, * currFunc;
int blkID = 0, tmpID = 0, stringID = 0, printID = 0, tabID = 0;
int f2a=FALSE, scat=FALSE, scmp=FALSE, b2a=FALSE;

void printLLVMType(LLVMType type)
{ switch(type) {
  case i1:
    fprintf(code, "i1");
    break;
  case i8:
    fprintf(code, "i8");
    break;
  case double_float:
    fprintf(code, "double");
    break;
  case i8_star:
    fprintf(code, "i8*");
    break;
  case i32:
    fprintf(code, "i32");
    break;
  case i32_star:
    fprintf(code, "i32*");
    break;
  case double_star:
    fprintf(code, "double*");
    break;
  case i8_star2:
    fprintf(code, "i8**");
    break;
  case i1_star:
    fprintf(code, "i1*");
    break;
  default:
    Error = TRUE;
    break;
  }
}

void printArrayTypePtr(LLVMType type, int dimen)
{ int i;

  for (i = 0; i < dimen; i++ ) 
    fprintf (code, "[256 x ");
  
  printLLVMType(type);
  
  for (i = 0; i < dimen; i++)
    fprintf(code, "]* ");
}

void printRetType(LLVMRetTypeList retList)
{ LLVMRetTypeList t = retList;

  if(retList == NULL)
  { fprintf(code, "void");
    return;
  }  
  
  if(retList->type == i32)
  { fprintf(code, "i32");
    return;
  }  
  
  fprintf(code, "{");
  
  if(t->type != tab)
    printLLVMType(t->type);
  else
    printArrayTypePtr(t->tabType, t->tabDimen);
      
  t = t->next;
  
  while(t != NULL)
  { fprintf(code, ", ");
  
    if(t->type != tab)
      printLLVMType(t->type);
    else
      printArrayTypePtr(t->tabType, t->tabDimen);
      
    t = t->next;
  }
  
  fprintf(code, "}");
  
  return;
}

void printArgType(LLVMArgTypeList argList)
{ LLVMArgTypeList t = argList;

  if(argList == NULL)
    return;
  
  if(t->type != tab)
    printLLVMType(t->type);
  else
    printArrayTypePtr(t->tabType, t->tabDimen);
    
  fprintf(code, " %%%s", t->name);
  t = t->next;
  
  while(t != NULL)
  { fprintf(code, ", ");
  
    if(t->type != tab)
      printLLVMType(t->type);
    else
      printArrayTypePtr(t->tabType, t->tabDimen);
    
    fprintf(code, " %%%s", t->name);
    t = t->next;
  }
  
  return;
}

void printCallList(LLVMCallList argList)
{ LLVMCallList t = argList;

  if(argList == NULL)
    return;
  
  if(t->type != tab)
    printLLVMType(t->type);
  else
    printArrayTypePtr(t->tabType, t->tabDimen);
    
  fprintf(code, " %s", t->name);
  t = t->next;
  
  while(t != NULL)
  { fprintf(code, ", ");
  
    if(t->type != tab)
      printLLVMType(t->type);
    else
      printArrayTypePtr(t->tabType, t->tabDimen);
    
    fprintf(code, " %s", t->name);
    t = t->next;
  }
  
  return;
}

void printAssign(AssignInst *inst)
{
  fprintf(code, "%s = %s ", inst->dst.name, inst->prefix.name);
  printLLVMType(inst->type);
  fprintf(code, " %s\n", inst->src.name);
}

void printUncondBr(UncondBrInst *inst)
{ fprintf(code, "br label %%%s\n", inst->dst.name);
}

void printST(StoreInst *inst)
{ fprintf(code, "store ");
  printLLVMType(inst->srcType);
  fprintf(code, " %s, ", inst->src.name);
  printLLVMType(inst->dstType);
  fprintf(code, " %s\n", inst->dst.name);
}

void printSTArray(StoreArrayInst *inst)
{ fprintf(code, "store ");
  printArrayTypePtr(inst->tabType, inst->dimen);
  fprintf(code, " %s, ", inst->src.name);
  printArrayTypePtr(inst->tabType, inst->dimen);
  fprintf(code, "* %s\n", inst->dst.name);
}

void printLD(LoadInst *inst)
{ fprintf(code, "%s = load ", inst->dst.name);
  printLLVMType(inst->srcType);
  fprintf(code, " %s\n", inst->src.name);
}

void printLDArray(LoadArrayInst *inst)
{ fprintf(code, "%s = load ", inst->dst.name);
  printArrayTypePtr(inst->tabType, inst->dimen);
  fprintf(code, "* %s\n", inst->src.name);
}

void printCondBr(CondBrInst *inst)
{ fprintf(code, "br i1 %s, label %%%s, label %%%s\n", inst->src.name, inst->dstTrue.name, inst->dstFalse.name);
}

void printBinOp(BinOpInst *inst)
{ fprintf(code, "%s = ", inst->dst.name);

  switch(inst->opc) {
  case PLUS:
    fprintf(code, "add ");
    break;
  case MINUS:
    fprintf(code, "sub ");
    break;
  case TIMES:
    fprintf(code, "mul ");
    break;
  case OVER:
    fprintf(code, "fdiv ");
    break;
  case MOD:
    fprintf(code, "frem ");
    break;
  default:
    Error = TRUE;
    break;      
  }
  
  printLLVMType(inst->type);
  fprintf(code, " %s, %s\n", inst->src1.name, inst->src2.name);
}

void printCMP(CMPInst *inst)
{
  if(inst->type == double_float)
  { fprintf(code, "%s = fcmp ", inst->dst.name);
    
    switch(inst->cond) {
    case EQ:
      fprintf(code, "ueq ");
      break;
    case NEQ:
      fprintf(code, "une ");
      break;
    case LE:
      fprintf(code, "ule ");
      break;
    case GE:
      fprintf(code, "uge ");
      break;
    case LT:
      fprintf(code, "ult ");
      break;
    case GT:
      fprintf(code, "ugt ");
      break;
    default:
      Error = TRUE;
      break;      
    }  
  }
  else if(inst->type == i1)
  { fprintf(code, "%s = icmp ", inst->dst.name);
    switch(inst->cond) {
    case EQ:
      fprintf(code, "eq ");
      break;
    case NEQ:
      fprintf(code, "ne ");
      break;
    case LE:
      fprintf(code, "ule ");
      break;
    case GE:
      fprintf(code, "uge ");
      break;
    case LT:
      fprintf(code, "ult ");
      break;
    case GT:
      fprintf(code, "ugt ");
      break;
    default:
      Error = TRUE;
      break;      
    }    
  }  
  printLLVMType(inst->type);
  fprintf(code, " %s, %s\n", inst->src1.name, inst->src2.name);
}

void printAlloc(AllocInst *inst)
{ fprintf(code, "%s = alloca ", inst->dst.name);
  printLLVMType(inst->type);
  fprintf(code , "\n");
}

void printAllocArrayStack(AllocArrayStackInst *inst)
{ fprintf(code, "%s = alloca ", inst->dst.name);
  printArrayTypePtr(inst->type, inst->dimen);
  fprintf(code , "\n");
}

void printBit(BitInst *inst)
{ fprintf(code, "%s = ", inst->dst.name);

  switch(inst->opc) {
  case AND:
    fprintf(code, "and ");
    break;
  case OR:
    fprintf(code, "or ");
    break;
  default:
    Error = TRUE;
    break;      
  }
  
  printLLVMType(inst->type);
  fprintf(code, " %s, %s\n", inst->src1.name, inst->src2.name);
}

void printInitString(InitStringInst* inst)
{ fprintf(code, "%s = constant [%d x i8] c\"%s\"\n", inst->dst.name, inst->len, inst->string);
}

void printLDString(LDStringInst * inst)
{ fprintf(code, "%s = bitcast [%d x i8]* %s to i8*\n", inst->dst.name, inst->len, inst->src.name );
}

void printRet(RetInst *inst)
{ fprintf(code, "ret ");
    
  printRetType(inst->typeList);
  
  if (inst->typeList != NULL)
    fprintf(code, " %s\n", inst->src.name);
  else
    fprintf(code, "\n");
}

void printLDStruct(LoadStructInst *inst)
{ fprintf(code, "%s = load ", inst->dst.name);
    
  printRetType(inst->typeList);
  
  fprintf(code, "* %s\n", inst->src.name);
}

void printAllocStruct(AllocStructInst *inst)
{ fprintf(code, "%s = common global ", inst->dst.name);
  printRetType(inst->typeList);
  fprintf(code, " zeroinitializer\n");
}

void printAllocArray(AllocArrayInst *inst)
{ int i;
  fprintf(code, "%s = common global ", inst->dst.name);
  
  for (i = 0; i < inst->dimen; i++)
    fprintf(code, "[256 x ");

  printLLVMType(inst->eleType);
  
  fprintf(code, "]");
  
  for (i = 0; i < inst->dimen - 1; i++)
    fprintf(code, "* ]");
    
  fprintf(code, " zeroinitializer\n");
}

void printCall(CallInst *inst)
{ if(inst->dst.name != NULL)
    fprintf(code, "%s = call ", inst->dst.name);
  else
    fprintf(code, "call ");
    
  if(inst->isStruct || inst->retList == NULL)
    printRetType(inst->retList);
  else
    printLLVMType(inst->retList->type);
    
  fprintf(code, "@%s(", inst->src.name);
  printCallList(inst->argList);
  fprintf(code, ")\n");
}

void printGetPtr(GetPtrInst * inst)
{ fprintf(code, "%s = getelementptr ", inst->dst.name);
  printRetType(inst->typeList);
  fprintf(code, "* %s, i32 0, i32 %d\n", inst->src.name, inst->index);
}

void printGetPtrArray(GetPtrArrayInst * inst)
{ int i;
  fprintf(code, "%s = getelementptr ", inst->dst.name);
  for (i = 0; i < inst->dimen; i++)
    fprintf(code, "[ 256 x ");

  printLLVMType(inst->type);
  
  for (i = 0; i < inst->dimen; i++)
    fprintf(code, "]* ");
  fprintf(code, "%s, i32 0, i32 %s\n", inst->src.name, inst->index);
}

void printExtract(ExtractInst * inst)
{ fprintf(code, "%s = extractvalue ", inst->dst.name);
  printRetType(inst->typeList);
  fprintf(code, " %s, %d\n", inst->src.name, inst->index);
}

void printPrint(PrintInst * inst)
{ fprintf(code, "call i32 (i8*, ...)* @printf(");
  printCallList(inst->argList);
  fprintf(code, ")\n");
}

void printToFloat(ToFloatInst *inst)
{ fprintf(code, "%s = sitofp i32 %s to double\n", inst->dst.name, inst->src.name);
}

void printToInt(ToIntInst *inst)
{ fprintf(code, "%s = fptosi double %s to i32\n", inst->dst.name, inst->src.name);
}

void printInst(Inst *inst)
{ switch(inst->instType) {
  case AssignI:
    printAssign((AssignInst *)inst->inst);
    break;
  case UncondBrI:
    printUncondBr((UncondBrInst *)inst->inst);
    break;
  case STI:
    printST((StoreInst *)inst->inst);
    break;
  case STArrayI:
    printSTArray((StoreArrayInst *)inst->inst);
    break;
  case LDI:
    printLD((LoadInst *)inst->inst);
    break;
  case LDArrayI:
    printLDArray((LoadArrayInst *)inst->inst);
    break;
  case CondBrI:
    printCondBr((CondBrInst *)inst->inst);
    break;
  case BinOpI:
    printBinOp((BinOpInst *)inst->inst);
    break;
  case CMPI:
    printCMP((CMPInst *)inst->inst);
    break;
  case AllocI:
    printAlloc((AllocInst *)inst->inst);
    break;
  case AllocArrayStackI:
    printAllocArrayStack((AllocArrayStackInst *)inst->inst);
    break;
  case BitI:
    printBit((BitInst *)inst->inst);
    break;
  case InitSI:
    printInitString((InitStringInst*)inst->inst);
    break;
  case LDStringI:
    printLDString((LDStringInst *)inst->inst);
    break;
  case RetI:
    printRet((RetInst *)inst->inst);
    break;
  case AllocStructI:
    printAllocStruct((AllocStructInst *)inst->inst);
    break;
  case AllocArrayI:
    printAllocArray((AllocArrayInst *)inst->inst);
    break;
  case CallI:
    printCall((CallInst *)inst->inst);
    break;
  case GetPtrI:
    printGetPtr((GetPtrInst *) inst->inst);
    break;
  case GetPtrArrayI:
    printGetPtrArray((GetPtrArrayInst *) inst->inst);
    break;
  case ExtractI:
    printExtract((ExtractInst *) inst->inst);
    break;
  case PrintI:
    printPrint((PrintInst *) inst->inst);
    break;
  case LDStructI:
    printLDStruct((LoadStructInst *)inst->inst);
    break;
  case ToFloatI:
    printToFloat((ToFloatInst *)inst->inst);
    break;
  case ToIntI:
    printToInt((ToIntInst *)inst->inst);
    break;
  default:
    Error = TRUE;
    break;
  }
}

void printBlk(BLOCK *blk)
{ Inst * inst = blk->inst;

  // if (blk->ignore) return;

  fprintf(code, "%s:\n", blk->name);
  
  while(inst != NULL) {
    printInst(inst);
    inst = inst->next;
  }
}

void printFunc(FUNC *f)
{ BLOCK * blk = f->block;
  
  if(f->retType != NULL && f->retType->type == i32)
    fprintf(code, "define i32 @%s(", f->name);
  else
    fprintf(code, "define void @%s(", f->name);
  
  printArgType(f->parType);
  fprintf(code, ") alwaysinline {\n");
  
  while(blk != NULL)
  { printBlk(blk);
    blk = blk->next;
  }
  
  fprintf(code, "}\n");
}

void printGlobal(GLOBAL *g)
{ Inst * inst = g->inst;

  while(inst != NULL)
  { printInst(inst);
    inst = inst->next;
  }
}

void printModule(MODULE *m)
{ FUNC * f = m->function;
  fprintf(code, "declare i32 @printf(i8* , ...)\n");
  fprintf(code, "declare i8* @strcat(i8* , i8* )\n");
  fprintf(code, "declare i32 @strlen(i8*)\n");
  fprintf(code, "declare double @llvm.pow.f64(double, double)\n");
  fprintf(code, "declare double @atof(i8*)\n");
  fprintf(code, "declare i32 @sprintf(i8*, i8*, ...)\n");
  fprintf(code, "declare i8* @malloc(i32)\n");
  fprintf(code, "declare void @llvm.memset.i32(i8* , i8, i32, i32)\n");
  fprintf(code, "declare i8* @strcpy(i8* , i8*)\n");
  fprintf(code, "declare i32 @strcmp(i8*, i8*)\n");
  fprintf(code, "@ftoa.str = internal constant [3 x i8] c\"%%f\\00\"\n");
  fprintf(code, "@false.str = internal constant [6 x i8] c\"false\\00\"\n");
  fprintf(code, "@true.str = internal constant [5 x i8] c\"true\\00\"\n");

  printGlobal(m->global);
  
  while(f != NULL)
  { printFunc(f);
    f = f->next;
  }

  if (f2a)
  { fprintf(code, "define i8* @ftoa(double %%num) alwaysinline {\n");
    fprintf(code, "entry:\n");
    fprintf(code, "%%0 = tail call i8* @malloc(i32 256)\n");
    fprintf(code, "tail call void @llvm.memset.i32(i8* %%0, i8 0, i32 256, i32 1)\n");
    fprintf(code, "%%1 = tail call i32 (i8*, i8*, ...)* @sprintf(i8* %%0, i8* getelementptr ([3 x i8]* @ftoa.str, i32 0, i32 0), double %%num)\n");
    fprintf(code, "ret i8* %%0\n");
    fprintf(code, "}\n");
  }

  if(scat)
  { fprintf(code, "define i8* @stringcat(i8* %%s1, i8* %%s2) alwaysinline {\n");
    fprintf(code, "entry:\n");
    fprintf(code, "%%0 = tail call i8* @malloc(i32 256)\n");
    fprintf(code, "tail call void @llvm.memset.i32(i8* %%0, i8 0, i32 256, i32 1)\n");
    fprintf(code, "%%1 = tail call i8* @strcpy(i8* %%0, i8* %%s1)\n");
    fprintf(code, "%%2 = tail call i8* @strcat(i8* %%0, i8* %%s2)\n");
    fprintf(code, "ret i8* %%0\n");
    fprintf(code, "}\n");
  }

  if(scmp)
  { fprintf(code, "define i1 @stringcmp(i8* %%s1, i8* %%s2, i32 %%op) alwaysinline {\n");
    fprintf(code, "entry:\n");
    fprintf(code, "%%0 = tail call i32 @strcmp(i8* %%s1, i8* %%s2)\n");
    fprintf(code, "	switch i32 %%op, label %%return [\n");
    fprintf(code, "i32 0, label %%bb\n");
    fprintf(code, "i32 1, label %%bb1\n");
    fprintf(code, "i32 2, label %%bb2\n");
    fprintf(code, "i32 3, label %%bb3\n");
    fprintf(code, "i32 4, label %%bb4\n");
    fprintf(code, "i32 5, label %%bb5\n");
    fprintf(code, "]\n");
    fprintf(code, "bb:\n");
    fprintf(code, "%%1 = icmp slt i32 %%0, 0\n");
    fprintf(code, "ret i1 %%1\n");
    fprintf(code, "bb1:\n");
    fprintf(code, "%%2 = icmp sgt i32 %%0, 0\n");
    fprintf(code, "ret i1 %%2\n");
    fprintf(code, "bb2:\n");
    fprintf(code, "%%3 = icmp slt i32 %%0, 1\n");
    fprintf(code, "ret i1 %%3\n");
    fprintf(code, "bb3:\n");
    fprintf(code, "%%4 = icmp sgt i32 %%0, -1\n");
    fprintf(code, "ret i1 %%4\n");
    fprintf(code, "bb4:\n");
    fprintf(code, "%%5 = icmp ne i32 %%0, 0	\n");
    fprintf(code, "ret i1 %%5\n");
    fprintf(code, "bb5:\n");
    fprintf(code, "%%6 = icmp eq i32 %%0, 0	\n");
    fprintf(code, "ret i1 %%6\n");
    fprintf(code, "return:\n");
    fprintf(code, "ret i1 undef\n");
    fprintf(code, "}\n");
  }

  if (b2a)
  { fprintf(code, "define i8* @btoa(i1 %%i) alwaysinline {\n");
    fprintf(code, "entry:\n");
    fprintf(code, "        %%.0 = select i1 %%i, i8* getelementptr ([5 x i8]* @true.str, i32 0, i32 0), i8* getelementptr ([6 x i8]* @false.str, i32 0, i32 0)\n");
    fprintf(code, "ret i8* %%.0\n");
    fprintf(code, "}\n");
  }
}


Inst * newAlloc( char *name, LLVMType type )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  AllocInst *i = (AllocInst *)malloc(sizeof(AllocInst));
  
  i->dst.name = name;
  i->type = type;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * insertAlloc(char *name, LLVMType type, Inst *inst)
{ Inst * tmpInst = inst->prev;
  
  if (tmpInst != NULL)
  { tmpInst->next = newAlloc(name, type); 
    tmpInst->next->instType = AllocI;
    tmpInst->next->parent = tmpInst->parent;
    tmpInst->next->next = inst;
    inst->prev = tmpInst->next;
    tmpInst->next->prev = tmpInst;
        
    return tmpInst->next;
  }
  else
  { BLOCK *blk = (BLOCK *)(inst->parent);
    blk->inst = newAlloc(name, type); 
    blk->inst->instType = AllocI;
    blk->inst->prev = NULL;
    blk->inst->next = inst;
    blk->inst->parent = inst->parent;
    inst->prev = blk->inst;
    
    return blk->inst;
  }
}

Inst * newAllocArrayStack( char *name, LLVMType type, int dimen)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  AllocArrayStackInst *i = (AllocArrayStackInst *)malloc(sizeof(AllocArrayStackInst));
  
  i->dst.name = name;
  i->type = type;
  i->dimen = dimen;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * insertAllocArray(char *name, LLVMType type, int dimen, Inst *inst)
{ Inst * tmpInst = inst->prev;
  
  if (tmpInst != NULL)
  { tmpInst->next = newAllocArrayStack(name, type, dimen); 
    tmpInst->next->instType = AllocArrayStackI;
    tmpInst->next->parent = tmpInst->parent;
    tmpInst->next->next = inst;
    inst->prev = tmpInst->next;
    tmpInst->next->prev = tmpInst;
        
    return tmpInst->next;
  }
  else
  { BLOCK *blk = (BLOCK *)(inst->parent);
    blk->inst = newAllocArrayStack(name, type, dimen); 
    blk->inst->instType = AllocArrayStackI;
    blk->inst->prev = NULL;
    blk->inst->next = inst;
    blk->inst->parent = inst->parent;
    inst->prev = blk->inst;
    
    return blk->inst;
  }
}

Inst * newCall( char * dst, char * src, LLVMCallList callList, LLVMRetTypeList retList, int isStruct)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  CallInst * i = (CallInst *)malloc(sizeof(CallInst));
  
  i->dst.name = dst;
  i->src.name = src;
  i->argList = callList;
  i->retList = retList;
  i->isStruct = isStruct;
  inst->inst = (void *)i;
  return inst;
}

Inst *appendCall(char * dst, LLVMRetTypeList retList, char * src, LLVMCallList callList, BLOCK * blk, int isStruct)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newCall(dst, src, callList, retList, isStruct); 
    lastInst->next->instType = CallI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newCall(dst, src, callList, retList, isStruct); 
    blk->inst->instType = CallI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newPrint( LLVMCallList callList)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  PrintInst * i = (PrintInst *)malloc(sizeof(PrintInst));
  
  i->argList = callList;

  inst->inst = (void *)i;
  return inst;
}

Inst *appendPrint(LLVMCallList callList, BLOCK * blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newPrint(callList); 
    lastInst->next->instType = PrintI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newPrint(callList); 
    blk->inst->instType = PrintI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newToFloat( char * to, char * from)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  ToFloatInst * i = (ToFloatInst *)malloc(sizeof(ToFloatInst));
  
  i->dst.name = to;
  i->src.name = from;
  inst->inst = (void *)i;
  return inst;
}

Inst * appendToFloat(char *to, char *from, BLOCK * blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newToFloat(to, from); 
    lastInst->next->instType = ToFloatI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newToFloat(to, from); 
    blk->inst->instType = ToFloatI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newToInt( char * to, char * from)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  ToIntInst * i = (ToIntInst *)malloc(sizeof(ToIntInst));
  
  i->dst.name = to;
  i->src.name = from;
  inst->inst = (void *)i;
  return inst;
}

Inst * appendToInt(char *to, char *from, BLOCK * blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newToInt(to, from); 
    lastInst->next->instType = ToIntI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newToInt(to, from); 
    blk->inst->instType = ToIntI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newAllocStruct( char *name, LLVMRetTypeList typeList )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  AllocStructInst *i = (AllocStructInst *)malloc(sizeof(AllocStructInst));
  
  i->dst.name = name;
  i->typeList = typeList;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendAllocStruct(char *name, LLVMRetTypeList typeList, GLOBAL *g)
{ Inst * lastInst = g->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newAllocStruct(name, typeList); 
    lastInst->next->instType = AllocStructI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = g;
    g->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { g->inst = newAllocStruct(name, typeList); 
    g->inst->instType = AllocStructI;
    g->inst->prev = NULL;
    g->inst->next = NULL;
    g->inst->parent = g;
    g->lastInst = g->inst;
    
    return g->inst;
  }
}

Inst * newAllocArray( char *tabName, LLVMType tabType, int dimen )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  AllocArrayInst *i = (AllocArrayInst *)malloc(sizeof(AllocArrayInst));
  
  i->dst.name = tabName;
  i->eleType = tabType;
  i->dimen = dimen;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendAllocArray(char *tabName, LLVMType tabType, int dimen, GLOBAL *g)
{ Inst * lastInst = g->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newAllocArray(tabName, tabType, dimen); 
    lastInst->next->instType = AllocArrayI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = g;
    g->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { g->inst = newAllocArray(tabName, tabType, dimen); 
    g->inst->instType = AllocArrayI;
    g->inst->prev = NULL;
    g->inst->next = NULL;
    g->inst->parent = g;
    g->lastInst = g->inst;
    
    return g->inst;
  }
}

Inst * newST( LLVMType dstType, char *dst, LLVMType srcType, char * src )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  StoreInst *i = (StoreInst *)malloc(sizeof(StoreInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->srcType = srcType;
  i->dstType = dstType;
  inst->inst = (void *)i;
  return inst;
}

Inst * insertST(LLVMType dstType, char *dst, LLVMType srcType, char * src, Inst *inst)
{ Inst * tmpInst = inst->prev;
  
  if (tmpInst != NULL)
  { tmpInst->next = newST(dstType, dst, srcType, src); 
    tmpInst->next->instType = STI;
    tmpInst->next->parent = tmpInst->parent;
    tmpInst->next->next = inst;
    inst->prev = tmpInst->next;
    tmpInst->next->prev = tmpInst;

    return tmpInst->next;
  }
  else
  { BLOCK *blk = (BLOCK *)(inst->parent);
    blk->inst = newST(dstType, dst, srcType, src); 
    blk->inst->instType = STI;
    blk->inst->parent = inst->parent;
    blk->inst->prev = NULL;
    blk->inst->next = inst;
    inst->prev = blk->inst;
    
    return blk->inst;
  }
}

Inst * appendST(LLVMType dstType, char *dst, LLVMType srcType, char * src, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newST(dstType, dst, srcType, src); 
    lastInst->next->instType = STI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newST(dstType, dst, srcType, src); 
    blk->inst->instType = STI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newSTArray( LLVMType tabType, int dimen, char *dst, char * src )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  StoreArrayInst *i = (StoreArrayInst *)malloc(sizeof(StoreArrayInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->tabType = tabType;
  i->dimen = dimen;
  inst->inst = (void *)i;
  return inst;
}

Inst * insertSTArray(LLVMType tabType, int dimen, char *dst, char * src, Inst *inst)
{ Inst * tmpInst = inst->prev;
  
  if (tmpInst != NULL)
  { tmpInst->next = newSTArray(tabType, dimen, dst, src); 
    tmpInst->next->instType = STArrayI;
    tmpInst->next->parent = tmpInst->parent;
    tmpInst->next->next = inst;
    inst->prev = tmpInst->next;
    tmpInst->next->prev = tmpInst;

    return tmpInst->next;
  }
  else
  { BLOCK *blk = (BLOCK *)(inst->parent);
    blk->inst = newSTArray(tabType, dimen, dst, src); 
    blk->inst->instType = STArrayI;
    blk->inst->parent = inst->parent;
    blk->inst->prev = NULL;
    blk->inst->next = inst;
    inst->prev = blk->inst;
    
    return blk->inst;
  }
}

Inst * appendSTArray(LLVMType tabType, int dimen, char *dst, char * src, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newSTArray(tabType, dimen, dst, src); 
    lastInst->next->instType = STArrayI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newSTArray(tabType, dimen, dst, src); 
    blk->inst->instType = STArrayI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newBit( TokenType opc, LLVMType type, char *dst, char * src1, char *src2)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  BitInst *i = (BitInst *)malloc(sizeof(BitInst));
  
  i->opc = opc;
  i->dst.name = dst;
  i->src1.name = src1;
  i->src2.name = src2;
  i->type = type;
  inst->inst = (void *)i;
    
  return inst;
}

Inst * appendBit(TokenType opc, LLVMType type, char *dst, char * src1, char *src2, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newBit(opc, type, dst, src1, src2); 
    lastInst->next->instType = BitI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newBit(opc, type, dst, src1, src2); 
    blk->inst->instType = BitI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newBinOp( TokenType opc, char *dst, LLVMType type, char *src1, char *src2 )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  BinOpInst *i = (BinOpInst *)malloc(sizeof(BinOpInst));
  
  i->opc = opc;
  i->src1.name = src1;
  i->src2.name = src2;  
  i->dst.name = dst;
  i->type = type;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendBinOp(TokenType opc, char *dst, LLVMType type, char *src1, char *src2, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newBinOp(opc, dst, type, src1, src2); 
    lastInst->next->instType = BinOpI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newBinOp(opc, dst, type, src1, src2); 
    blk->inst->instType = BinOpI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newLD( char *dst, LLVMType srcType, char * src )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  LoadInst * i = (LoadInst *)malloc(sizeof(LoadInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->srcType = srcType;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendLD(char *dst, LLVMType srcType, char *src, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newLD(dst, srcType, src); 
    lastInst->next->instType = LDI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newLD(dst, srcType, src); 
    blk->inst->instType = LDI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newLDArray( char *dst, LLVMType tabType, int dimen, char *src )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  LoadArrayInst * i = (LoadArrayInst *)malloc(sizeof(LoadArrayInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->tabType = tabType;
  i->dimen = dimen;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendLDArray(char *dst, LLVMType tabType, int dimen, char *src, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newLDArray(dst, tabType, dimen, src); 
    lastInst->next->instType = LDArrayI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newLDArray(dst, tabType, dimen, src); 
    blk->inst->instType = LDArrayI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newCMP( char * dst, LLVMType type, char * src1, char * src2, TokenType cond )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  CMPInst *i = (CMPInst *)malloc(sizeof(CMPInst));
  
  i->src1.name = src1;
  i->src2.name = src2;
  i->dst.name = dst;
  i->cond = cond;
  i->type = type;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendCMP(char * dst, LLVMType type, char * src1, char * src2, TokenType cond, BLOCK *blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newCMP(dst, type, src1, src2, cond); 
    lastInst->next->instType = CMPI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newCMP(dst, type, src1, src2, cond); 
    blk->inst->instType = CMPI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newUncondBr(char * targName) 
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  UncondBrInst *i = (UncondBrInst *)malloc(sizeof(UncondBrInst));
  
  i->dst.name = targName;
  inst->inst = (void *)i;
  return inst;
}

Inst *appendUncondBr(char * targetName, BLOCK * blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newUncondBr(targetName); 
    lastInst->next->instType = UncondBrI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newUncondBr(targetName); 
    blk->inst->instType = UncondBrI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}

Inst * newCondBr(char * dstTrue, char * dstFalse, char * src) 
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  CondBrInst *i = (CondBrInst *)malloc(sizeof(CondBrInst));
  
  i->dstTrue.name = dstTrue;
  i->dstFalse.name = dstFalse;
  i->src.name = src;
  inst->inst = (void *)i;
  return inst;
} 

Inst *appendCondBr(char * dstTrue, char * dstFalse, char * src, BLOCK * blk)
{ Inst * lastInst = blk->lastInst;
  
  if (lastInst != NULL)
  { lastInst->next = newCondBr(dstTrue, dstFalse, src); 
    lastInst->next->instType = CondBrI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;
    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newCondBr(dstTrue, dstFalse, src);
    blk->inst->instType = CondBrI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
    
    return blk->inst;
  }
}


BLOCK * newBlk(char * blkName, FUNC * func)
{ BLOCK * blk = (BLOCK * ) malloc(sizeof(BLOCK));

  blk->lastInst = NULL;
  blk->inst = NULL;
  blk->prev = NULL;
  blk->next = NULL; 
  blk->parent = func; 
  blk->exitInst = NULL;
  blk->name = blkName;
  
  return blk;
}

BLOCK * appendBlk(char * blkName, FUNC * func)
{ BLOCK * lastBlk = func->lastBlock;
  
  if (lastBlk != NULL)
  { lastBlk->next = newBlk(blkName, func); 
    lastBlk->next->prev = lastBlk;
    lastBlk->next->next = NULL;
    func->lastBlock = lastBlk->next;
    
    return lastBlk->next;
  }
  else
  { 
    func->block = newBlk(blkName, func); 
    func->block->prev = NULL;
    func->block->next = NULL;
    func->lastBlock = func->block;
    
    return func->block;
  }
}

FUNC * newFunc(char * funcName, LLVMRetTypeList retType, LLVMArgTypeList parType, MODULE * m)
{ FUNC * func = (FUNC * ) malloc(sizeof(FUNC));
  char *blkName = (char *)malloc(256);
  BLOCK *entryBlk;
  
  func->lastBlock = NULL;
  func->block = NULL;
  func->prev = NULL;
  func->next = NULL; 
  func->parent = m; 
  func->retType = retType;
  func->parType = parType;
  func->name = funcName;
  
  entryBlk = appendBlk("entry", func);
  sprintf(blkName, "%s.bb%d", funcName, blkID++);
  entryBlk->exitInst = appendUncondBr(blkName, entryBlk);
  func->currBlock = appendBlk(blkName, func);
  
  return func;
}

FUNC * appendFunc(char * funcName, LLVMRetTypeList retType, LLVMArgTypeList parType, MODULE * m)
{ FUNC * lastFunc = m->lastFunc;
  
  if (lastFunc != NULL)
  { lastFunc->next = newFunc(funcName, retType, parType, m); 
    lastFunc->next->prev = lastFunc;
    lastFunc->next->next = NULL;
    m->lastFunc = lastFunc->next;
    
    return lastFunc->next;
  }
  else
  { 
    m->function = newFunc(funcName, retType, parType, m); 
    m->function->prev = NULL;
    m->function->next = NULL;
    m->lastFunc = m->function;
    
    return m->function;
  }
}

FUNC * insertFunc(char * funcName, LLVMRetTypeList retType, LLVMArgTypeList parType, FUNC * f)
{ FUNC * tmpFunc = f->prev;
  
  if (tmpFunc != NULL)
  { tmpFunc->next = newFunc(funcName, retType, parType, f->parent); 
    tmpFunc->next->next = f;
    f->prev = tmpFunc->next;
    tmpFunc->next->prev = tmpFunc;
    
    return tmpFunc->next;
  }
  else
  { MODULE * m = (MODULE *)(f->parent);
    m->function = newFunc(funcName, retType, parType, f->parent); 
    m->function->prev = NULL;
    m->function->next = f;
    f->prev = m->function;
    
    return m->function;
  }
}

Inst * newAssign( char *dst, char *src, LLVMType type, char *prefix )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  AssignInst *i = (AssignInst *)malloc(sizeof(AssignInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->type = type;
  i->prefix.name = prefix;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendInit( char *dst, int val, LLVMType type, char *prefix, void *blk, int isGlobal)
{ Inst * lastInst;
  
  char *src = malloc(13);
  
  switch(type)
  {
  case i1:
    sprintf(src, "%d", 0);
    break;
  case double_float:
    sprintf(src, "%s", "0.000000e+00");
    break;
  case i8_star:
    sprintf(src, "%s", "null");
    break;
  default:
    Error = TRUE;
    break;
  }
  
  if(isGlobal)
    lastInst = ((GLOBAL *)blk)->lastInst;
  else
    lastInst = ((BLOCK *)blk)->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newAssign(dst, src, type, prefix); 
    lastInst->next->instType = AssignI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    if(isGlobal)
      ((GLOBAL *)blk)->lastInst = lastInst->next;
    else
      ((BLOCK *)blk)->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
    if(isGlobal)
    { ((GLOBAL *)blk)->inst = newAssign(dst, src, type, prefix); 
      ((GLOBAL *)blk)->inst->instType = AssignI;
      ((GLOBAL *)blk)->inst->prev = NULL;
      ((GLOBAL *)blk)->inst->next = NULL;
      ((GLOBAL *)blk)->inst->parent = ((GLOBAL *)blk);
      ((GLOBAL *)blk)->lastInst = ((GLOBAL *)blk)->inst;
    
      return ((GLOBAL *)blk)->inst;
    }
    else
    { ((BLOCK *)blk)->inst = newAssign(dst, src, type, prefix); 
      ((BLOCK *)blk)->inst->instType = AssignI;
      ((BLOCK *)blk)->inst->prev = NULL;
      ((BLOCK *)blk)->inst->next = NULL;
      ((BLOCK *)blk)->inst->parent = ((BLOCK *)blk);
      ((BLOCK *)blk)->lastInst = ((BLOCK *)blk)->inst;
    
      return ((BLOCK *)blk)->inst;
    }
}

Inst * newInitString(char *dst, char *s, int len)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  int i = 0, j = 0;
  InitStringInst * in = (InitStringInst *)malloc(sizeof(InitStringInst));
  char *format = malloc(3 * strlen(s));
  
  memset(format, 0, 3 * strlen(s));
  
  for(i = 0; i < strlen(s); i++)
  { switch(s[i]) {
    case '\n':
      format[j++] = '\\';
      format[j++] = '0';
      format[j++] = 'A';
      break;
    case '\t':
      format[j++] = '\\';
      format[j++] = '0';
      format[j++] = '9';
      break;
    default:
      format[j++] = s[i];
      break;
    }
  }

  in->dst.name = dst;
  in->string = s;
  in->len = len;
  inst->inst = (void *)in;  
  return inst;
}

Inst * appendInitString(char *dst, char *s, int len, GLOBAL*g)
{ Inst * lastInst;

  lastInst = g->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newInitString(dst, s, len); 
    lastInst->next->instType = InitSI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = g;

    g->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { g->inst = newInitString(dst, s, len); 
    g->inst->instType = InitSI;
    g->inst->prev = NULL;
    g->inst->next = NULL;
    g->inst->parent = g;
    g->lastInst = g->inst;
  
    return g->inst;
  }
}

Inst * newRet( LLVMRetTypeList retType, char * src )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  RetInst *i = (RetInst *)malloc(sizeof(RetInst));
  
  i->src.name = src;
  i->typeList = retType;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendRet(LLVMRetTypeList retType, char * src, BLOCK * blk)
{ Inst * lastInst;

  lastInst = blk->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newRet(retType, src); 
    lastInst->next->instType = RetI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newRet(retType, src);
    blk->inst->instType = RetI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
  
    return blk->inst;
  }
}

Inst * newLDStruct( char * dst, LLVMRetTypeList retType, char * src )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  LoadStructInst *i = (LoadStructInst *)malloc(sizeof(LoadStructInst));
  
  i->dst.name = dst;
  i->src.name = src;
  i->typeList = retType;
  
  inst->inst = (void *)i;
  return inst;
}

Inst * appendLDStruct(char * dst, LLVMRetTypeList retType, char * src, BLOCK * blk)
{ Inst * lastInst;

  lastInst = blk->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newLDStruct ( dst, retType, src); 
    lastInst->next->instType = LDStructI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newLDStruct ( dst, retType, src);
    blk->inst->instType = LDStructI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
  
    return blk->inst;
  }
}

Inst * newGetPtr( char * dst, char * src, LLVMRetTypeList retType, int index )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  GetPtrInst *i = (GetPtrInst *)malloc(sizeof(GetPtrInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->typeList = retType;
  i->index = index;
  inst->inst = (void *)i;
  return inst;
}

Inst * appendGetPtr(char * dst, char * src, LLVMRetTypeList retType, int index, BLOCK *blk)
{ Inst * lastInst;

  lastInst = blk->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newGetPtr(dst, src, retType, index); 
    lastInst->next->instType = GetPtrI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newGetPtr(dst, src, retType, index); 
    blk->inst->instType = GetPtrI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
  
    return blk->inst;
  }
}

Inst * newGetPtrArray( char *dst, char *src, LLVMType type, int dimen, char *id )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  GetPtrArrayInst *i = (GetPtrArrayInst *)malloc(sizeof(GetPtrArrayInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->type = type;
  i->dimen = dimen;
  i->index = id;
  inst->inst = (void *)i;
  return inst;
}

Inst * appendGetPtrArray(char *dst, char *src, LLVMType type, int dimen, char *id, BLOCK * blk)
{ Inst * lastInst;

  lastInst = blk->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newGetPtrArray(dst, src, type, dimen, id); 
    lastInst->next->instType = GetPtrArrayI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newGetPtrArray(dst, src, type, dimen, id); 
    blk->inst->instType = GetPtrArrayI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
  
    return blk->inst;
  }
}

Inst * newExtract( char * dst, char * src, LLVMRetTypeList retType, int index )
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  ExtractInst *i = (ExtractInst *)malloc(sizeof(ExtractInst));
  
  i->src.name = src;
  i->dst.name = dst;
  i->typeList = retType;
  i->index = index;
  inst->inst = (void *)i;
  return inst;
}

Inst * appendExtract(char * dst, char * src, LLVMRetTypeList retType, int index, BLOCK *blk)
{ Inst * lastInst;

  lastInst = blk->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newExtract(dst, src, retType, index); 
    lastInst->next->instType = ExtractI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newExtract(dst, src, retType, index); 
    blk->inst->instType = ExtractI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
  
    return blk->inst;
  }
}


Inst * newLDString(char *dst, char *src, int len)
{ Inst *inst = (Inst *)malloc(sizeof(Inst));
  
  LDStringInst *i = (LDStringInst *)malloc(sizeof(LDStringInst));
  i->src.name = src;
  i->dst.name = dst;
  i->len = len;
  inst->inst = (void *)i;
  return inst;
}

Inst * appendLDString(char *dst, char *src, int len, BLOCK *blk)
{ Inst * lastInst;

  lastInst = blk->lastInst;

  if (lastInst != NULL)
  { lastInst->next = newLDString(dst, src, len); 
    lastInst->next->instType = LDStringI;
    lastInst->next->prev = lastInst;
    lastInst->next->next = NULL;
    lastInst->next->parent = blk;

    blk->lastInst = lastInst->next;
        
    return lastInst->next;
  }
  else
  { blk->inst = newLDString(dst, src, len); 
    blk->inst->instType = LDStringI;
    blk->inst->prev = NULL;
    blk->inst->next = NULL;
    blk->inst->parent = blk;
    blk->lastInst = blk->inst;
  
    return blk->inst;
  }
}

MODULE * newModule()
{ MODULE * m = (MODULE * ) malloc(sizeof(MODULE));
  m->global = NULL;
  m->function = NULL;
  m->lastFunc = NULL;
  
  return m;
}

GLOBAL * newGlobal(MODULE * m)
{ GLOBAL * g = (GLOBAL *) malloc(sizeof(GLOBAL));
  g->inst = NULL;
  m->global = g;
  g->parent = (void *)m;
  g->lastInst = NULL;
  
  return g;
}

/* Delete an instruction */
Inst * deleteInst(Inst *inst)
{
 Inst *next = NULL;
 Inst *prev = NULL;
 Inst *del = inst;
 Inst *temp = NULL;

 if(inst == NULL)
 {
   Error = TRUE;
   return NULL;
 }
 
 /* first node deletion */
 if(del->prev == NULL)
 {
   temp = del->next;
   if(temp) temp->prev = NULL;
   // free(del);
   return temp;
 }
 /*Last node deletion*/
 if(del->next == NULL)
 {
   temp = del->prev;
   if(temp) temp->next = NULL;
   //free(del);
   while(temp->prev) temp = temp->prev;
   
   ((BLOCK*)(temp->parent))->lastInst = del->prev;
   return temp;
 }
 /*Any other node deletion */
 temp = inst->prev;
 prev = inst->prev;
 next = inst->next;
 prev->next = next;
 next->prev = prev;
 // free(del);
 while (temp->prev) temp = temp->prev;
 return temp;
}

BLOCK * deleteBlk(BLOCK *blk)
{
 BLOCK *next = NULL;
 BLOCK *prev = NULL;
 BLOCK *del = blk;
 BLOCK *temp = NULL;

 if(blk == NULL)
 {
   Error = TRUE;
   return NULL;
 }
 
 /* first node deletion */
 if(del->prev == NULL)
 {
   temp = del->next;
   if(temp) temp->prev = NULL;
   ((FUNC*)(del->parent))->block = del->next;
   // free(del);
   return del->next;
 }
 /*Last node deletion*/
 if(del->next == NULL)
 {
   temp = del->prev;
   if(temp) temp->next = NULL;
   //free(del);

   return NULL;
 }
 /*Any other node deletion */
 temp = blk->prev;
 prev = blk->prev;
 next = blk->next;
 prev->next = next;
 next->prev = prev;
 // free(del);

 return next;
}


/*find if the arguements are constants*/
int IsFloat(char *buf, float *num)
{ int result = 0;
  float number = 0;
  if(buf && ((*buf == '@') || (*buf == '%')))
  { *num = 0;
    return FALSE;
  }
  sscanf(buf,"%f",&number);
  if(num) *num = number;
  return TRUE;
}

/*find if the arguements are constants*/
int IsInt(char *buf, int *num)
{ int result = 0;
  int number = 0;
  if(buf && ((*buf == '@') || (*buf == '%')))
  { *num = 0;
    return FALSE;
  }
  sscanf(buf,"%d",&number);
  if(num) *num = number;
  return TRUE;
}

/*To convert a number to char form */
int FloatToChar(char *buf, float num)
{ if(buf)
  { sprintf(buf,"%f",num);
    return TRUE;
  }
  return FALSE;
}

/*To convert a number to char form */
int IntToChar(char *buf, int num)
{ if(buf)
  { sprintf(buf,"%d",num);
    return TRUE;
  }
  return FALSE;
}
