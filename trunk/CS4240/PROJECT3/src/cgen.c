/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the LUA compiler                             */
/* Haicheng                                         */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "constprop.h"
#include "cfg.h"
#include "cfgopti.h"

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree, char *label, FUNC * prevFunc);

char *strtrans(char *s)
{ char* trans = malloc(256);
  char c;
  int i = 0, j = 0;  
  
  memset(trans, 0, sizeof(s) * 3);
  
  char a[4] = {"\\07"};;
  char b[4] = {"\\08"};;
  char f[4] = {"\\0C"};;
  char n[4] = {"\\0A"};;
  char r[4] = {"\\0D"};;
  char t[4] = {"\\09"};;
  char v[4] = {"\\0B"};;
  char bs[4] = {"\\5C"};;
  char dq[4] = {"\\22"};
  char null[4] = {"\\00"};
  
  while((c = s[i]) != '\0')
  { switch(c) {
    case '\a':
      strcat(trans, a);
      j += 3;
      break;
    case '\b':
      strcat(trans, b);
      j += 3;
      break;
    case '\f':
      strcat(trans, f);
      j += 3;
      break;
    case '\n':
      strcat(trans, n);
      j += 3;
      break;
    case '\r':
      strcat(trans, r);
      j += 3;
      break;
    case '\t':
      strcat(trans, t);
      j += 3;
      break;
    case '\v':
      strcat(trans, v);
      j += 3;
      break;
    case '\\':
      strcat(trans, bs);
      j += 3;
      break;
    case '\"':
      strcat(trans, dq);
      j += 3;
      break;
    default:
      trans[j++] = s[i];
      break;
    }
    i++;
  }
  
  strcat(trans, null);
  return trans;
}
void genPrintf(TreeNode * t)
{ TreeNode * tt = t;
  char *format = (char *)malloc(256);
  char tab[4] = {"\\09"};
  char newline[4] = {"\\0A"};
  char s[3] = {"%s"};
  char f[3] = {"%f"};
  char d[3] = {"%d"};
  char null[4] = {"\\00"};
  char * formatstring = (char *)malloc(20);
  char * formatVar = (char *)malloc(256);
  LLVMCallList curr = NULL, next = NULL, root = NULL;
  
  int formatLen = 0;
  memset(format, 0, 256);
  
  while(tt!=NULL)
  {
    if (tt->sibling == NULL && tt->nodekind == ExpK && 
      tt->kind.exp == PreK && tt->child[0]->kind.stmt == FunCallK)
    { CallRetList ret = tt->child[0]->retRegs;
        
      while (ret != NULL)
      { next = (LLVMCallList)malloc(sizeof(struct CallRetRec));
        if(ret->type != Boolean)
          next->name = ret->regName;
        else
        { char *tmp = (char *)malloc(256);
          LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;

          sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
              
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i1;
          strcatArg->typePtr = i1_star;
          strcatArg->name = ret->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = i8_star;
          strcatRet->typePtr = i8_star2;
          strcatRet->next = NULL;
              
          appendCall(tmp, strcatRet, "btoa", strcatArg, currFunc->currBlock, FALSE);
          b2a=TRUE;
          next->name = tmp;
        }
        next->next = NULL;
        
        switch(ret->type) {
        case i1:
          next->type = i8_star;
          next->typePtr = i8_star2;
          strcat(format, s);
          strcat(format, tab);
          formatLen += 3;
          break;
        case double_float:
          next->type = double_float;
          next->typePtr = double_star;
          strcat(format, f);
          strcat(format, tab);
          formatLen += 3;
          break;
        case i8_star:
          next->type = i8_star;
          next->typePtr = i8_star2;
          strcat(format, s);
          strcat(format, tab);
          formatLen += 3;
          break;
        } 
      
        if(curr == NULL)
        { curr = next;
          root = next;
        }
        else
        { curr->next = next;
          curr = next;
        }      
        ret = ret->next;
      }
    }
    else 
    {
      next = (LLVMCallList)malloc(sizeof(struct CallRetRec));
      
      if(tt->type != Boolean)
        next->name = tt->regName;
      else
      { char *tmp = (char *)malloc(256);
        LLVMCallList strcatArg;
        LLVMRetTypeList strcatRet;

        sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
            
        strcatArg = malloc(sizeof(struct CallRec));
        strcatArg->type = i1;
        strcatArg->typePtr = i1_star;
        strcatArg->name = tt->regName;
        strcatArg->next = NULL;
        
        strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
        strcatRet->type = i8_star;
        strcatRet->typePtr = i8_star2;
        strcatRet->next = NULL;
            
        appendCall(tmp, strcatRet, "btoa", strcatArg, currFunc->currBlock, FALSE);
        b2a=TRUE;
        next->name = tmp;
      }
      
      next->next = NULL;
      
      switch(tt->type) {
      case Boolean:
        next->type = i8_star;
        next->typePtr = i8_star2;
        strcat(format, s);
        strcat(format, tab);
        formatLen += 3;
        break;
      case Number:
        next->type = double_float;
        next->typePtr = double_star;
        strcat(format, f);
        strcat(format, tab);
        formatLen += 3;
        break;
      case String:
        next->type = i8_star;
        next->typePtr = i8_star2;
        strcat(format, s);
        strcat(format, tab);
        formatLen += 3;
        break;
      } 
      
      if(curr == NULL)
      { curr = next;
        root = next;
      }
      else
      { curr->next = next;
        curr = next;
      }
    }

    tt = tt->sibling;
  }

  strcat(format, newline);
  strcat(format, null);
  formatLen+=2;
  
  sprintf(formatstring, "@print%d", printID++);
  appendInitString(formatstring, format, formatLen, ((MODULE *)(currFunc->parent))->global);
  sprintf(formatVar, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
  appendLDString(formatVar, formatstring, formatLen, currFunc->currBlock);

  curr = (LLVMCallList)malloc(sizeof(struct CallRetRec));
  curr->name = formatVar;
  curr->type = i8_star;
  curr->typePtr = i8_star2;
  curr->next = root;
  root = curr;
  appendPrint(root, currFunc->currBlock);
}

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * t, char *label, FUNC * prevFunc)
{ switch (t->kind.stmt) {
  case AssignK:
    /* generate code for rhs */
    cGen(t->child[1], label, prevFunc);
    /* generate code for lhs */
    cGen(t->child[0], label, prevFunc);
    
    { TreeNode * vt, * et;
      vt = t->child[0];
      et = t->child[1];
      
      while(vt != NULL)
      { 
        if (vt->childNum == 1)
        { BucketList l = st_lookup(vt->child[0]->attr.name);
          if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && 
             et->kind.exp == PreK && et->child[0]->kind.stmt == FunCallK)
          { BucketList l;
            CallRetList ret = et->child[0]->retRegs;
            
            while (ret != NULL)
            { l = st_lookup(vt->child[0]->attr.name);
            
              switch(vt->type) {
              case Number:
                appendST(double_star, l->loc, double_float, ret->regName, currFunc->currBlock);
                break;
              case String:
                appendST(i8_star2, l->loc, i8_star, ret->regName, currFunc->currBlock);
                break;
              case Boolean:
                appendST(i1_star, l->loc, i1, ret->regName, currFunc->currBlock);
                break;
              case Table:
                l->loc = ret->regName;
                l->tabType = ret->tabType;
                l->tabEleNum = ret->tabEleNum;
                l->tabDimen = ret->tabDimen;
                break;
              default:
                Error = TRUE;
                break;
              }
            
              ret = ret->next;
              vt = vt->sibling;
              if(vt == NULL) break;
            }
            break;
          }
          else if(et != NULL)
          { 
            switch(vt->type) {
            case Number:
              appendST(double_star, l->loc, double_float, et->regName, currFunc->currBlock);
              break;
            case String:
              appendST(i8_star2, l->loc, i8_star, et->regName, currFunc->currBlock);
              break;
            case Boolean:
              appendST(i1_star, l->loc, i1, et->regName, currFunc->currBlock);
              break;
            case Table:
              l->loc = et->regName;
              l->tabType = et->tabType;
              l->tabEleNum = et->tabEleNum;
              l->tabDimen = et->tabDimen;
              break;
            default:
              Error = TRUE;
              break;
            }

            et = et->sibling;
            if(et == NULL) break;
          }
        }
        else if(vt->childNum == 2)
        { 
          if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && 
             et->kind.exp == PreK && et->child[0]->kind.stmt == FunCallK)
          { CallRetList ret = et->child[0]->retRegs;
            
            while (ret != NULL)
            { switch(vt->type) {
              case Number:
                appendST(double_star, vt->ptrName, double_float, ret->regName, currFunc->currBlock);
                break;
              case String:
                appendST(i8_star2, vt->ptrName, i8_star, ret->regName, currFunc->currBlock);
                break;
              case Boolean:
                appendST(i1_star, vt->ptrName, i1, ret->regName, currFunc->currBlock);
                break;
              case Table:
                appendSTArray(ret->tabType, ret->tabDimen, vt->ptrName, ret->regName, currFunc->currBlock);
                break;
              default:
                Error = TRUE;
                break;
              }
            
              ret = ret->next;
              vt = vt->sibling;
              if(vt == NULL) break;
            }
            break;
          }
          else if(et != NULL)
          { 
            switch(vt->type) {
            case Number:
              appendST(double_star, vt->ptrName, double_float, et->regName, currFunc->currBlock);
              break;
            case String:
              appendST(i8_star2, vt->ptrName, i8_star, et->regName, currFunc->currBlock);
              break;
            case Boolean:
              appendST(i1_star, vt->ptrName, i1, et->regName, currFunc->currBlock);
              break;
            case Table:
              appendSTArray(et->tabType, et->tabDimen, vt->ptrName, et->regName, currFunc->currBlock);
              break;
            default:
              Error = TRUE;
              break;
            }

            et = et->sibling;
            if(et == NULL) break;
          }
        }
        
        if(vt !=NULL ) vt = vt->sibling;
      }
    }
    
    break;
  case LocAssignK:
    /* generate code for rhs */
    cGen(t->child[1], label, prevFunc);
    /* generate code for lhs */
    cGen(t->child[0], label, prevFunc);
    
    { TreeNode * vt, * et;
      vt = t->child[0];
      et = t->child[1];
      
      while(vt != NULL)
      { 
        { BucketList l = st_lookup(vt->attr.name);
          if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && 
              et->kind.exp == PreK && et->child[0]->kind.stmt == FunCallK)
          { BucketList l;
            CallRetList ret = et->child[0]->retRegs;;
            
            while (ret != NULL)
            { l = st_lookup(vt->attr.name);
            
              switch(vt->type) {
              case Number:
                appendST(double_star, l->loc, double_float, ret->regName, currFunc->currBlock);
                break;
              case String:
                appendST(i8_star2, l->loc, i8_star, ret->regName, currFunc->currBlock);
                break;
              case Boolean:
                appendST(i1_star, l->loc, i1, ret->regName, currFunc->currBlock);
                break;
              case Table:
                l->loc = ret->regName;
                l->tabType = ret->tabType;
                l->tabEleNum = ret->tabEleNum;
                l->tabDimen = ret->tabDimen;
                
                break;
              default:
                Error = TRUE;
                break;
              }
            
              ret = ret->next;
              vt = vt->sibling;
              if(vt == NULL) break;
            }
            break;
          }
          else if (et != NULL)
          {
            switch(vt->type)
            {
            case Number:
              appendST(double_star, l->loc, double_float, et->regName, currFunc->currBlock);
              break;
            case String:
              appendST(i8_star2, l->loc, i8_star, et->regName, currFunc->currBlock);
              break;
            case Boolean:
              appendST(i1_star, l->loc, i1, et->regName, currFunc->currBlock);
              break;
            case Table:
              l->loc = et->regName;
              l->tabType = et->tabType;
              l->tabEleNum = et->tabEleNum;
              l->tabDimen = et->tabDimen;
              break;
            default:
              Error = TRUE;
              break;
            }
            
            et = et->sibling;
            if(et == NULL) break;
          }
        }
        
        if(vt !=NULL ) vt = vt->sibling;
      }
    }

    break;
  case FunCallK:
    cGen(t->child[1], label, prevFunc);
    
    if(strcmp(t->child[0]->child[0]->child[0]->attr.name, "print") == 0)
    { genPrintf(t->child[1]);
      goto ENDOFNOTPRINT;
    }
    
    { BucketList funl = st_lookup(t->child[0]->child[0]->child[0]->attr.name);
      HashTable *funh = (HashTable *)funl->ptr;
      TreeNode *tt;
      LLVMCallList callCurr = NULL, callNext = NULL, callRoot = NULL;
      LLVMRetTypeList retCurr = NULL, retRoot = NULL;
      CallRetList callRetCurr = NULL, callRetNext = NULL, callRetRoot = NULL;
      char * callTmp = (char *)malloc(256);
      int retID = 0;
      
      tt = t->child[1];
      
      while (tt != NULL)
      { 
        if (tt->sibling == NULL && tt->nodekind == ExpK && 
            tt->kind.exp == PreK && tt->child[0]->kind.stmt == FunCallK)
        { CallRetList ret = tt->child[0]->retRegs;
            
          while (ret != NULL)
          { callNext = malloc(sizeof(struct CallRec));
          
            callNext->name = ret->regName;
            callNext->type = ret->type;
            
            if(callNext->type == tab)
            { callNext->tabType = ret->tabType;
              callNext->tabDimen = ret->tabDimen;
            }
            callNext->next = NULL;
          
            if(callCurr == NULL)
            { callCurr = callNext;
              callRoot = callNext;
            }
            else
            { callCurr->next = callNext;
              callCurr = callNext;
            }
          
          ret = ret->next;
          }
        }
        else
        { callNext = malloc(sizeof(struct CallRec));
          
          callNext->name = tt->regName;
          
          switch(tt->type) {
          case Boolean:
            callNext->type = i1;
            callNext->typePtr = i1_star;
            break;
          case Number:
            callNext->type = double_float;
            callNext->typePtr = double_star;
            break;
          case String:
            callNext->type = i8_star;
            callNext->typePtr = i8_star2;
            break;
          case Table:
            callNext->type = tab;
            callNext->tabDimen = tt->tabDimen;
            
            switch (tt->tabType) {
            case Boolean:
              callNext->tabType = i1;
              break;
            case String:
              callNext->tabType = i8_star;
              break;
            case Number:
              callNext->tabType = double_float;
              break;
            }
            break;
            
          default:
            Error = TRUE;
            break;
          }
          callNext->next = NULL;
          
          if(callCurr == NULL)
          { callCurr = callNext;
            callRoot = callNext;
          }
          else
          { callCurr->next = callNext;
            callCurr = callNext;
          }
        }
        tt = tt->sibling;
      }

      retRoot = (LLVMRetTypeList)(funh->llvmPtr);
      retCurr = retRoot;
      sprintf(callTmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      
      if(retRoot != NULL)
      { char *tmp = (char *)malloc(256);
        sprintf(tmp, "@%s.retval", t->child[0]->child[0]->child[0]->attr.name);
        appendCall(NULL, NULL, t->child[0]->child[0]->child[0]->attr.name, callRoot, currFunc->currBlock, TRUE);
        appendLDStruct(callTmp, retRoot, tmp, currFunc->currBlock);
      }
      else
        appendCall(NULL, retRoot, t->child[0]->child[0]->child[0]->attr.name, callRoot, currFunc->currBlock, TRUE);
      
      while(retCurr != NULL)
      { char * tmp1 = malloc(256);

        callRetNext = malloc(sizeof(struct CallRetRec));
        
        sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        
        callRetNext->regName = tmp1;
        callRetNext->type = retCurr->type;

        if (callRetNext->type == tab)
        { callRetNext->tabType = retCurr->tabType;
          callRetNext->tabDimen = retCurr->tabDimen;
        }
        else
          callRetNext->typePtr = retCurr->typePtr;
          
        callRetNext->next = NULL;
        
        appendExtract(tmp1, callTmp, retRoot, retID, currFunc->currBlock);

        retCurr = retCurr->next;
        retID++;
        
        if(callRetCurr == NULL)
        { callRetCurr = callRetNext;
          callRetRoot = callRetNext;
        }
        else
        { callRetCurr->next = callRetNext;
          callRetCurr = callRetNext;
        }
      }
      
      t->regName = (callRetRoot == NULL) ? NULL : callRetRoot->regName;
      t->retRegs = callRetRoot;
    }
ENDOFNOTPRINT:
    break;
  case DoK:
    entBlock();
    cGen(t->child[0], label, prevFunc);
    lvBlock();

    break;
  case WhileK:
    { char *blk1, *blk2, *blk3;
      char *tmp;
      
      blk1 = (char *) malloc(256);
      blk2 = (char *) malloc(256);
      blk3 = (char *) malloc(256);
      
      sprintf(blk1, "%s.bb%d", currFunc->name, blkID++);
      sprintf(blk2, "%s.bb%d", currFunc->name, blkID++);
      sprintf(blk3, "%s.bb%d", currFunc->name, blkID++);
      
    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(blk1, currFunc->currBlock);
        
      currFunc->currBlock = appendBlk(blk1, currFunc);
      
      cGen(t->child[0], label, prevFunc);
      if(t->child[0]->type == Boolean)
        tmp = t->child[0]->regName;
      else
      { tmp = (char *)malloc(256);
        sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        appendBinOp(PLUS, tmp, i1, "0", "1", currFunc->currBlock);
      }
      
      currFunc->currBlock->exitInst = appendCondBr(blk2, blk3, tmp, currFunc->currBlock);
      
      currFunc->currBlock = appendBlk(blk2, currFunc);
      
      entBlock();
      cGen(t->child[1], blk3, prevFunc);
      lvBlock();
      
    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(blk1, currFunc->currBlock);
      
      currFunc->currBlock = appendBlk(blk3, currFunc);
    }

    break;
  case RepeatK:
    { char *blk1, *blk2, *blk3;
      char * tmp;
      
      entBlock();
      
      blk1 = (char *) malloc(256);
      blk2 = (char *) malloc(256);
      blk3 = (char *) malloc(256);
      
      sprintf(blk1, "%s.bb%d", currFunc->name, blkID++);
      sprintf(blk2, "%s.bb%d", currFunc->name, blkID++);
      sprintf(blk3, "%s.bb%d", currFunc->name, blkID++);

    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(blk1, currFunc->currBlock);
        
      currFunc->currBlock = appendBlk(blk1, currFunc);
      
      cGen(t->child[0], blk3, prevFunc);
      
    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(blk2, currFunc->currBlock);

      currFunc->currBlock = appendBlk(blk2, currFunc);
      
      cGen(t->child[1], label, prevFunc);
      
      if(t->child[1]->type == Boolean)
        tmp = t->child[1]->regName;
      else
      { tmp = (char *)malloc(256);
        sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        appendBinOp(PLUS, tmp, i1, "0", "1", currFunc->currBlock);
      }
      
      currFunc->currBlock->exitInst = appendCondBr(blk3, blk1, tmp, currFunc->currBlock);
      
      currFunc->currBlock = appendBlk(blk3, currFunc);
      lvBlock();
    }

    break;
  case IfK:
    { char *dstTrue, *dstFalse, *dstAfter;
      char *tmp;
    
      dstAfter = (char *) malloc(256);
      sprintf(dstAfter, "%s.bb%d", currFunc->name, blkID++);
      
      while(t != NULL && (t->kind.stmt == IfK || t->kind.stmt == ElseIfK))
      { 
        cGen(t->child[0], label, prevFunc);
        
        dstTrue = (char *) malloc(256);
        dstFalse = (char *) malloc(256);
        
        sprintf(dstTrue, "%s.bb%d", currFunc->name, blkID++);
        sprintf(dstFalse, "%s.bb%d", currFunc->name, blkID++);
        
        if(t->child[0]->type == Boolean)
          tmp = t->child[0]->regName;
        else
        { tmp = (char *)malloc(256);
          sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
          appendBinOp(PLUS, tmp, i1, "0", "1", currFunc->currBlock);
        }
        currFunc->currBlock->exitInst = appendCondBr(dstTrue, dstFalse, tmp, currFunc->currBlock);

        currFunc->currBlock = appendBlk(dstTrue, currFunc);
        entBlock();
        cGen(t->child[1], label, prevFunc);
        lvBlock();
        
    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
          currFunc->currBlock->exitInst = appendUncondBr(dstAfter, currFunc->currBlock);

        currFunc->currBlock = appendBlk(dstFalse, currFunc);
        if(t->sibling != NULL && (t->sibling->kind.stmt == ElseIfK || t->sibling->kind.stmt == ElseK))
          t = t->sibling;
        else 
          break;
      }
      
      if(t != NULL && t->kind.stmt == ElseK)
      { entBlock();
        cGen(t->child[0], label, prevFunc);
        lvBlock();
      }

    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(dstAfter, currFunc->currBlock);

      currFunc->currBlock = appendBlk(dstAfter, currFunc);
    }
    break;
  case ElseK:
  case ElseIfK:
    break;
  case ForNumK:
    { BucketList l;
      char * iterVar = (char *)malloc(256);
      char * limitVar;
      char * stepVar;
      
      char *blk1, *blk2, *blk3;
      char *tmpVar1, *tmpVar2, *tmpVar3;
       
      entBlock();     
      sprintf(iterVar, "@%s.%s", currFunc->currBlock->name, t->child[0]->attr.name);
      appendInit(iterVar, 0, double_float, "common global", ((MODULE *)(currFunc->parent))->global, TRUE);
      l = st_lookup(t->child[0]->attr.name);
      l->loc = iterVar;

      cGen(t->child[1], label, prevFunc);
      appendST(double_star, iterVar, double_float, t->child[1]->regName, currFunc->currBlock);
      
      cGen(t->child[2], label, prevFunc);
      limitVar = t->child[2]->regName;
      
      if(t->childNum == 5)
      { cGen(t->child[3], label, prevFunc);
        stepVar = t->child[3]->regName;
      }
      else
      { stepVar = (char *)malloc(256);
        sprintf(stepVar, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        appendBinOp(PLUS, stepVar, double_float, "0.000000e+00", "1.000000e+00", currFunc->currBlock);
      }
      
      blk1 = (char *)malloc(256);
      blk2 = (char *)malloc(256);
      blk3 = (char *)malloc(256);
      
      sprintf(blk1, "%s.bb%d", currFunc->name, blkID++);
      sprintf(blk2, "%s.bb%d", currFunc->name, blkID++);
      sprintf(blk3, "%s.bb%d", currFunc->name, blkID++);

    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(blk1, currFunc->currBlock);

      currFunc->currBlock = appendBlk(blk1, currFunc);
      
      tmpVar1 = (char *)malloc(256);
      sprintf(tmpVar1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      appendLD(tmpVar1, double_star, iterVar, currFunc->currBlock);
      t->child[0]->regName = tmpVar1;
      
      if(t->childNum == 5)
      { char *tmp1, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6, *tmp7;
        
        tmp1 = (char *)malloc(256);
        tmp2 = (char *)malloc(256);
        tmp3 = (char *)malloc(256);   
        tmp4 = (char *)malloc(256);
        tmp5 = (char *)malloc(256);
        tmp6 = (char *)malloc(256); 
        tmp7 = (char *)malloc(256);  
        
        sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        sprintf(tmp2, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        sprintf(tmp3, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);    
        sprintf(tmp4, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        sprintf(tmp5, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        sprintf(tmp6, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);  
        sprintf(tmp7, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);  
        
        appendCMP(tmp2, double_float, stepVar, "0.000000e+00", GT, currFunc->currBlock);
        appendCMP(tmp3, double_float, tmpVar1, limitVar, LE, currFunc->currBlock);
        appendBit(AND, i1, tmp4, tmp2, tmp3, currFunc->currBlock);
        appendCMP(tmp5, double_float, stepVar, "0.000000e+00", LE, currFunc->currBlock);
        appendCMP(tmp6, double_float, tmpVar1, limitVar, GE, currFunc->currBlock);
        appendBit(AND, i1, tmp7, tmp5, tmp6, currFunc->currBlock);        
        appendBit(OR, i1, tmp1, tmp4, tmp7, currFunc->currBlock); 
        currFunc->currBlock->exitInst = appendCondBr(blk2, blk3, tmp1, currFunc->currBlock);         
      } 
      else
      { char *tmp1;
        tmp1 = (char *)malloc(256);
        sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        appendCMP(tmp1, double_float, tmpVar1, limitVar, LE, currFunc->currBlock);
        currFunc->currBlock->exitInst = appendCondBr(blk2, blk3, tmp1, currFunc->currBlock);
      } 
      
      currFunc->currBlock = appendBlk(blk2, currFunc);
      
      tmpVar2 = (char *)malloc(256);
      sprintf(tmpVar2, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);

      tmpVar3 = (char *)malloc(256);
      sprintf(tmpVar3, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);

      if(t->childNum == 5)
      { cGen(t->child[4], blk3, prevFunc);
        appendLD(tmpVar2, double_star, iterVar, currFunc->currBlock);
        appendBinOp(PLUS, tmpVar3, double_float, tmpVar2, stepVar, currFunc->currBlock);
      } 
      else
      { cGen(t->child[3], blk3, prevFunc);
        appendLD(tmpVar2, double_star, iterVar, currFunc->currBlock);      
        appendBinOp(PLUS, tmpVar3, double_float, tmpVar2, stepVar, currFunc->currBlock);
      }
      appendST(double_star, iterVar, double_float, tmpVar3, currFunc->currBlock);

    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
        currFunc->currBlock->exitInst = appendUncondBr(blk1, currFunc->currBlock);

      lvBlock();
      currFunc->currBlock = appendBlk(blk3, currFunc);
    }

    break;
  case FunK:
  case LocFunK:
    prevFunc = currFunc;
    entFunBlock();
    
    { RetTypeList funr = currFunSymTab->retType;
      ArgTypeList funa = currFunSymTab->argType;
      TreeNode * argNode = t->child[1]->child[0];
      LLVMRetTypeList retCurr = NULL, retNext = NULL, retRoot = NULL;
      LLVMArgTypeList argCurr = NULL, argNext = NULL, argRoot = NULL; 
      
      if(funr == NULL)
        retRoot = NULL;
      else
      {
        while(funr != NULL)
        { retNext = malloc(sizeof(struct RetTypeRec));
          
          switch (funr->type) {
          case Boolean:
            retNext->type = i1;
            retNext->typePtr = i1_star;
            break;
          case Number:
            retNext->type = double_float;
            retNext->typePtr = double_star;
            break;
          case String:
            retNext->type = i8_star;
            retNext->typePtr = i8_star2;
            break;
          case Table:
            retNext->type = tab;

            switch (funr->tabType) {
            case Boolean:
              retNext->tabType = i1;
              break;
            case Number:
              retNext->tabType = double_float;
              break;
            case String:
              retNext->tabType = i8_star;
              break;
            default:
              break;
            }
            
            retNext->tabDimen = funr->tabDimen;
            break;
          default:
            Error = TRUE;
            break;
          }
        
          if(retCurr == NULL)
          { retCurr = retNext;
            retRoot = retNext;
          }
          else
          { retCurr->next = retNext;
            retCurr = retNext;
          }
          
          funr = funr->next;
        }
      }
      
      currFunSymTab->llvmPtr = (void *)retRoot;
      
      if(funa == NULL)
        argRoot = NULL;
      else
      {
        while(funa != NULL)
        { char *locname = malloc(256);
          argNext = malloc(sizeof(struct ParTypeRec));
          argNext->name = argNode->attr.name;
          
          switch (funa->arg->type) {
          case Boolean:
            argNext->type = i1;
            argNext->typePtr = i1_star;
            break;
          case Number:
            argNext->type = double_float;
            argNext->typePtr = double_star;
            break;
          case String:
            argNext->type = i8_star;
            argNext->typePtr = i8_star2;
            break;
          case Table:
            argNext->type = tab;

            switch(funa->arg->tabType) {
            case Boolean:
              argNext->tabType = i1;
              break;
            case String:
              argNext->tabType = i8_star;
              break;
            case Number:
              argNext->tabType = double_float;
              break;
            }

            argNext->tabDimen = funa->arg->tabDimen;
            break;
          default:
            Error = TRUE;
            break;
          }
        
          if(argCurr == NULL)
          { argCurr = argNext;
            argRoot = argNext;
          }
          else
          { argCurr->next = argNext;
            argCurr = argNext;
          }
          
          if(funa->arg->type != Table)
          { sprintf(locname, "%%%s.%s", t->child[0]->attr.name, funa->arg->name);
            funa->arg->loc = locname;
          }
          else
          { sprintf(locname, "%%%s", funa->arg->name);
            funa->arg->loc = locname;
          }

          funa = funa->next;
          argNode = argNode->sibling;
        }
      }
      currFunc = insertFunc(t->child[0]->attr.name, retRoot, argRoot, mainFunc);

      cGen(t->child[1], label, currFunc);
      
      if (currFunc->currBlock->inst == NULL 
      || (currFunc->currBlock->lastInst->instType != UncondBrI
      && currFunc->currBlock->lastInst->instType != CondBrI
      && currFunc->currBlock->lastInst->instType != RetI))
        currFunc->currBlock->exitInst = appendUncondBr("return", currFunc->currBlock);
        
      currFunc->currBlock = appendBlk("return", currFunc);
      
      retCurr = retRoot;
      
      if(retRoot != NULL)
      {
        int retID = 0;
        char *ret = (char *)malloc(256);
        sprintf(ret, "@%s.retval", currFunc->name);
        
        while(retCurr != NULL)
        { char * retName = malloc(256);
          char * tmp1 = malloc(256);
          char * tmp2 = malloc(256);
          char * tmp3 = malloc(256);
          
          sprintf(retName, "%%retval%d", retID);
          sprintf(tmp1, "%%%s.%s.tmp%d", currFunc->name, currFunc->currBlock->name, tmpID++);
          sprintf(tmp2, "%%%s.%s.tmp%d", currFunc->name, currFunc->currBlock->name, tmpID++);
          
          if(retCurr->type != tab)
          { appendLD(tmp1, retCurr->typePtr, retName, currFunc->currBlock);
            appendGetPtr(tmp2, ret, retRoot, retID, currFunc->currBlock);
            appendST(retCurr->typePtr, tmp2, retCurr->type, tmp1, currFunc->currBlock);
          }
          else
          { appendLDArray(tmp1, retCurr->tabType, retCurr->tabDimen, retName, currFunc->currBlock);
            appendGetPtr(tmp2, ret, retRoot, retID, currFunc->currBlock);
            appendSTArray(retCurr->tabType, retCurr->tabDimen, tmp2, tmp1, currFunc->currBlock);
          }

          retCurr = retCurr->next;
          retID++;
        }
      }
      currFunc->currBlock->exitInst = appendRet(NULL, "void", currFunc->currBlock);
    }

    lvFunBlock();
    currFunc = prevFunc;
    break;
  case ReturnK:
    if (t->childNum == 1)
    {
      int retID = 0;
      cGen(t->child[0], label, prevFunc);
      
      { TreeNode *retExp = t->child[0];

        while(retExp != NULL)
         { 
          if (retExp->sibling == NULL && retExp->nodekind == ExpK && 
             retExp->kind.exp == PreK && retExp->child[0]->kind.stmt == FunCallK)
          { CallRetList ret = retExp->child[0]->retRegs;
            
            while (ret != NULL)
            { char * retName = (char *)malloc(256);
              sprintf(retName, "%%retval%d", retID++);
              
              if(ret->type != tab)
                appendST(ret->typePtr, retName, ret->type, ret->regName, currFunc->currBlock);
              else
                appendSTArray(ret->tabType, ret->tabDimen, retName, ret->regName, currFunc->currBlock);

              ret = ret->next;
            }
          }
          else
          { char * retName = (char *)malloc(256);
            sprintf(retName, "%%retval%d", retID++);
            
            switch(retExp->type) {
            case Number:
              appendST(double_star, retName, double_float, retExp->regName, currFunc->currBlock);
              break;
            case String:
              appendST(i8_star2, retName, i8_star, retExp->regName, currFunc->currBlock);
              break;
            case Boolean:
              appendST(i1_star, retName, i1, retExp->regName, currFunc->currBlock);
              break;
            case Table:
              switch (retExp->tabType) {
              case Number:
                appendSTArray(double_float, retExp->tabDimen, retName, retExp->regName, currFunc->currBlock);
                break;
              case String:
                appendSTArray(i8_star, retExp->tabDimen, retName, retExp->regName, currFunc->currBlock);
                break;
              case Boolean:
                appendSTArray(i1, retExp->tabDimen, retName, retExp->regName, currFunc->currBlock);
                break;
              default:
                break;
              }
              
              break;
            default:
              Error = TRUE;
              break;
            }
          }
          retExp = retExp->sibling;
        }
      }
    } 
    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
      currFunc->currBlock->exitInst = appendUncondBr("return", currFunc->currBlock);

//    currFunc->currBlock->exitInst->next = NULL;

    break;
  case BreakK:
    if(currFunc->currBlock->lastInst == NULL
   || (currFunc->currBlock->lastInst->instType != UncondBrI 
    && currFunc->currBlock->lastInst->instType != CondBrI))
      currFunc->currBlock->exitInst = appendUncondBr(label, currFunc->currBlock);
      
    break;
  default:
    fprintf(listing,"Unknown StmtNode kind\n");
    Error = TRUE;
    break;
  }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * t, char * label, FUNC * prevFunc)
{ switch (t->kind.exp) {
  case BinOpK:
    { char * dst = (char *)malloc(256);
      char * tmp1 , * tmp2;
      
      sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);

      if (t->attr.op == PLUS  || t->attr.op == MINUS
       || t->attr.op == TIMES || t->attr.op == OVER
       || t->attr.op == MOD)
      { cGen(t->child[0], label, prevFunc);
        cGen(t->child[1], label, prevFunc);
        
        if(t->child[0]->type == String)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          tmp1 = (char *)malloc(256);
          sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i8_star;
          strcatArg->typePtr = i8_star2;
          strcatArg->name = t->child[0]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = double_float;
          strcatRet->typePtr = double_star;
          strcatRet->next = NULL;

          appendCall(tmp1, strcatRet, "atof", strcatArg, currFunc->currBlock, FALSE);
        }
        else
          tmp1 = t->child[0]->regName;
          
        if(t->child[1]->type == String)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          tmp2 = (char *)malloc(256);
          sprintf(tmp2, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i8_star;
          strcatArg->typePtr = i8_star2;
          strcatArg->name = t->child[1]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = double_float;
          strcatRet->typePtr = double_star;
          strcatRet->next = NULL;

          appendCall(tmp2, strcatRet, "atof", strcatArg, currFunc->currBlock, FALSE);
        }
        else
          tmp2 = t->child[1]->regName;
          
        appendBinOp(t->attr.op, dst, double_float, tmp1, tmp2, currFunc->currBlock);
        t->regName = dst;
      } 
      else if (t->attr.op == EQ  || t->attr.op == NEQ
        || t->attr.op == LE || t->attr.op == GE
        || t->attr.op == LT   || t->attr.op == GT)
      { cGen(t->child[0], label, prevFunc);
        cGen(t->child[1], label, prevFunc);
        
        if (t->child[0]->type == Number && t->child[1]->type == Number)
          appendCMP(dst, double_float, t->child[0]->regName, t->child[1]->regName, t->attr.op, currFunc->currBlock);
        else if (t->child[0]->type == Boolean && t->child[1]->type == Boolean)
          appendCMP(dst, i1, t->child[0]->regName, t->child[1]->regName, t->attr.op, currFunc->currBlock);
        else if (t->child[0]->type == String && t->child[1]->type == String)
        { LLVMCallList strcatArg1, strcatArg2, strcatArg3;
          LLVMRetTypeList strcatRet;
        
          strcatArg1 = malloc(sizeof(struct CallRec));
          strcatArg1->type = i8_star;
          strcatArg1->typePtr = i8_star2;
          strcatArg1->name = t->child[0]->regName;
          strcatArg1->next = malloc(sizeof(struct CallRec));

          strcatArg2 = strcatArg1->next;
          strcatArg2->type = i8_star;
          strcatArg2->typePtr = i8_star2;
          strcatArg2->name = t->child[1]->regName;
          strcatArg2->next = malloc(sizeof(struct CallRec));

          strcatArg3 = strcatArg2->next;
          strcatArg3->type = i32;
          strcatArg3->typePtr = i32_star;
          switch(t->attr.op) {
          case EQ:
            strcatArg3->name = "5";
            break;
          case NEQ:
            strcatArg3->name = "4";
            break;
          case LE:
            strcatArg3->name = "2";
            break;
          case GE:
            strcatArg3->name = "3";
            break;
          case LT:
            strcatArg3->name = "0";
            break;
          case GT:
            strcatArg3->name = "1";
            break;
          }
          
          strcatArg3->next = NULL;

          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = i1;
          strcatRet->typePtr = i1_star;
          strcatRet->next = NULL;

          appendCall(dst, strcatRet, "stringcmp", strcatArg1, currFunc->currBlock, FALSE);
          scmp = TRUE;
        }
        else if(t->child[0]->type != t->child[1]->type && t->attr.op == EQ)
          appendBinOp(PLUS, dst, i1, "0", "0", currFunc->currBlock);
        else if (t->child[0]->type != t->child[1]->type && t->attr.op == NEQ)
          appendBinOp(PLUS, dst, i1, "0", "1", currFunc->currBlock);
          
        t->regName = dst;
      } 
      else if (t->attr.op == AND )
      { cGen(t->child[0], label, prevFunc);
        cGen(t->child[1], label, prevFunc);
        
        if(t->type == Boolean)
        { appendBit(AND, i1, dst, t->child[0]->regName, t->child[1]->regName, currFunc->currBlock);
          t->regName = dst;
        }
        else
        {
          t->regName = t->child[1]->regName;
        }
      } 
      else if (t->attr.op == OR )
      { cGen(t->child[0], label, prevFunc);
        cGen(t->child[1], label, prevFunc);
        
        if(t->type == Boolean)
        { appendBit(OR, i1, dst, t->child[0]->regName, t->child[1]->regName, currFunc->currBlock);
          t->regName = dst;
        }
        else
        {
          t->regName = t->child[0]->regName;
        }
      } 
      else if (t->attr.op == DDOT )
      { LLVMCallList strcatArg1, strcatArg2;
        LLVMRetTypeList strcatRet;
        char *callTmp = (char *)malloc(256);
        char *tmp1, *tmp2;
        
        cGen(t->child[0], label, prevFunc);
        cGen(t->child[1], label, prevFunc);
        
        if(t->child[0]->type == Number)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          char *alloc = (char *)malloc(256);
          
          tmp1 = (char *)malloc(256);
          sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);

          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = double_float;
          strcatArg->typePtr = double_star;
          strcatArg->name = t->child[0]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = i8_star;
          strcatRet->typePtr = i8_star2;
          strcatRet->next = NULL;
          
          appendCall(tmp1, strcatRet, "ftoa", strcatArg, currFunc->currBlock, FALSE);
          f2a = TRUE;
        }
        else
          tmp1 = t->child[0]->regName;
          
        if(t->child[1]->type == Number)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          char *alloc = (char *)malloc(256);
          
          tmp2 = (char *)malloc(256);
          sprintf(tmp2, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);

          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = double_float;
          strcatArg->typePtr = double_star;
          strcatArg->name = t->child[1]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = i8_star;
          strcatRet->typePtr = i8_star2;
          strcatRet->next = NULL;
          
          appendCall(tmp2, strcatRet, "ftoa", strcatArg, currFunc->currBlock, FALSE);
          f2a=TRUE;
        }
        else
          tmp2 = t->child[1]->regName;
        
        strcatArg1 = malloc(sizeof(struct CallRec));
        strcatArg1->type = i8_star;
        strcatArg1->typePtr = i8_star2;
        strcatArg1->name = tmp1;

        strcatArg1->next = malloc(sizeof(struct CallRec));
        strcatArg2 = strcatArg1->next;
        strcatArg2->type = i8_star;
        strcatArg2->typePtr = i8_star2;
        strcatArg2->name = tmp2;
        strcatArg2->next = NULL;
        
        strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
        strcatRet->type = i8_star;
        strcatRet->typePtr = i8_star2;
        strcatRet->next = NULL;
        
        sprintf(callTmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        appendCall(callTmp, strcatRet, "stringcat", strcatArg1, currFunc->currBlock, FALSE);
        scat = TRUE;
        
        t->regName = callTmp;
      }
      else if(t->attr.op == POW)
      { LLVMCallList strcatArg1, strcatArg2;
        LLVMRetTypeList strcatRet;
        
        char *callTmp = (char *)malloc(256);
        
        cGen(t->child[0], label, prevFunc);
        cGen(t->child[1], label, prevFunc);
        if(t->child[0]->type == String)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          tmp1 = (char *)malloc(256);
          sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i8_star;
          strcatArg->typePtr = i8_star2;
          strcatArg->name = t->child[0]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = double_float;
          strcatRet->typePtr = double_star;
          strcatRet->next = NULL;

          appendCall(tmp1, strcatRet, "atof", strcatArg, currFunc->currBlock, FALSE);
        }
        else
          tmp1 = t->child[0]->regName;
          
        if(t->child[1]->type == String)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          tmp2 = (char *)malloc(256);
          sprintf(tmp2, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i8_star;
          strcatArg->typePtr = i8_star2;
          strcatArg->name = t->child[1]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = double_float;
          strcatRet->typePtr = double_star;
          strcatRet->next = NULL;

          appendCall(tmp2, strcatRet, "atof", strcatArg, currFunc->currBlock, FALSE);
        }
        else
          tmp2 = t->child[1]->regName;
          
        strcatArg1 = malloc(sizeof(struct CallRec));
        strcatArg1->type = double_float;
        strcatArg1->typePtr = double_star;
        strcatArg1->name = t->child[0]->regName;

        strcatArg1->next = malloc(sizeof(struct CallRec));
        strcatArg2 = strcatArg1->next;
        strcatArg2->type = double_float;
        strcatArg2->typePtr = double_star;
        strcatArg2->name = t->child[1]->regName;
        strcatArg2->next = NULL;
        
        strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
        strcatRet->type = double_float;
        strcatRet->typePtr = double_star;
        strcatRet->next = NULL;
        
        sprintf(callTmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        appendCall(callTmp, strcatRet, "llvm.pow.f64", strcatArg1, currFunc->currBlock, FALSE);
        
        t->regName = callTmp;
      }
    }

    break;
  case UnOpK:
    { char * dst = (char *)malloc(256);
      char *tmp;
      sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      
      if (t->attr.op == MINUS)
      { cGen(t->child[0], label, prevFunc);
        if(t->child[0]->type == String)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          tmp = (char *)malloc(256);
          sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
        
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i8_star;
          strcatArg->typePtr = i8_star2;
          strcatArg->name = t->child[0]->regName;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = double_float;
          strcatRet->typePtr = double_star;
          strcatRet->next = NULL;

          appendCall(tmp, strcatRet, "atof", strcatArg, currFunc->currBlock, FALSE);
        }
        else
          tmp = t->child[0]->regName;

        appendBinOp(MINUS, dst, double_float, "0.000000e+00", tmp, currFunc->currBlock);
        t->regName = dst;
      } 
      else if (t->attr.op == NOT )
      { cGen(t->child[0], label, prevFunc);
        if(t->child[0]->type == Boolean)
          appendBinOp(MINUS, dst, i1, "1", t->child[0]->regName, currFunc->currBlock);
        else
          appendBinOp(PLUS, dst, i1, "0", "0", currFunc->currBlock);
          
        t->regName = dst;
      } 
      else if (t->attr.op == POUND )
      {
        cGen(t->child[0], label, prevFunc);
        
        if (t->child[0]->type == Number || t->child[0]->type == String)
        { LLVMCallList strcatArg;
          LLVMRetTypeList strcatRet;
          
          char *callTmp = (char *)malloc(256);
          char *toTmp = (char *)malloc(256);
          char *tmp;
          
          if(t->child[0]->type == Number)
          { LLVMCallList strcatArg;
            LLVMRetTypeList strcatRet;
            char *alloc = (char *)malloc(256);
            
            tmp = (char *)malloc(256);
            sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);

            strcatArg = malloc(sizeof(struct CallRec));
            strcatArg->type = double_float;
            strcatArg->typePtr = double_star;
            strcatArg->name = t->child[0]->regName;
            strcatArg->next = NULL;
            
            strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
            strcatRet->type = i8_star;
            strcatRet->typePtr = i8_star2;
            strcatRet->next = NULL;
            
            appendCall(tmp, strcatRet, "ftoa", strcatArg, currFunc->currBlock, FALSE);
            f2a=TRUE;
          }
          else
            tmp = t->child[0]->regName;
          
          strcatArg = malloc(sizeof(struct CallRec));
          strcatArg->type = i8_star;
          strcatArg->typePtr = i8_star2;
          strcatArg->name = tmp;
          strcatArg->next = NULL;
          
          strcatRet = malloc(sizeof(struct LLVMRetTypeRec));
          strcatRet->type = i32;
          strcatRet->typePtr = i32_star;
          strcatRet->next = NULL;
          
          sprintf(callTmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
          appendCall(callTmp, strcatRet, "strlen", strcatArg, currFunc->currBlock, FALSE);
          
          sprintf(toTmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
          appendToFloat(toTmp, callTmp, currFunc->currBlock);
          
          t->regName = toTmp;
        }
        else if (t->child[0]->type == Table)
        { char * dst = (char *)malloc(256);
          char * val = (char *)malloc(20);
          
          sprintf(val, "%f", (float)t->tabEleNum);
          sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
          appendBinOp(PLUS, dst, double_float, "0.000000e+00", val, currFunc->currBlock);
          t->regName = dst;
        }
      }
    }
      
    break;
  case BoolConstK:
    { char * dst = (char *)malloc(256);
      char * val = (char *)malloc(2);
      
      sprintf(val, "%d", t->attr.boolVal);
      sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      appendBinOp(PLUS, dst, i1, "0", val, currFunc->currBlock);
      t->regName = dst;
    }

    break;
  case RealConstK:
    { char * dst = (char *)malloc(256);
      char * val = (char *)malloc(20);
      
      sprintf(val, "%f", t->attr.realVal);
      sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      appendBinOp(PLUS, dst, double_float, "0.000000e+00", val, currFunc->currBlock);
      t->regName = dst;
    }

    break;
  case StringConstK:
    { char * dst = (char *)malloc(256);
      char * constant = (char *)malloc(20);
      
      sprintf(constant, "@string%d", stringID++);
      appendInitString(constant, strtrans(t->attr.name),
                       strlen(t->attr.name) + 1, ((MODULE *)(currFunc->parent))->global);
      sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      appendLDString(dst, constant, strlen(t->attr.name) + 1, currFunc->currBlock);
      t->regName = dst;
    }

    break;

  case PreK:
    cGen(t->child[0], label, prevFunc);
    t->regName = t->child[0]->regName;

    break;
  case IdK:
    { BucketList l = st_lookup(t->attr.name);
      char *tmp = malloc(256);
      sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      
     if (l->type != FunK )
     { if(l->loc == NULL)
       { char * newLoc = (char *)malloc(256);
         sprintf(newLoc, "@%s.%s", currFunc->currBlock->name, t->attr.name);
         
         switch(t->type)
         { case Boolean:
             appendInit(newLoc, 0, i1, "common global", ((MODULE *)(currFunc->parent))->global, TRUE);
             appendLD(tmp, i1_star, newLoc, currFunc->currBlock);
             break;
           case Number:
             appendInit(newLoc, 0, double_float, "common global", ((MODULE *)(currFunc->parent))->global, TRUE);
             appendLD(tmp, double_star, newLoc, currFunc->currBlock);
             break;
           case String:
             appendInit(newLoc, 0, i8_star, "common global", ((MODULE *)(currFunc->parent))->global, TRUE);
             appendLD(tmp, i8_star2, newLoc, currFunc->currBlock);
             break;
         }

         l->loc = newLoc;
       }
       else 
       { switch(t->type)
         { case Boolean:
             appendLD(tmp, i1_star, l->loc, currFunc->currBlock);
             break;
           case Number:
             appendLD(tmp, double_star, l->loc, currFunc->currBlock);
             break;
           case String:
             appendLD(tmp, i8_star2, l->loc, currFunc->currBlock);
             break;
           case Table:
/*             switch (l->tabType) {*/
/*             case Boolean:*/
/*               appendLDArray(tmp, i1, l->tabEleNum, l->loc, currFunc->currBlock);*/
/*               break;*/
/*             case Number:*/
/*               appendLDArray(tmp, double_float, l->tabEleNum, l->loc, currFunc->currBlock);*/
/*               break;*/
/*             case String:*/
/*               appendLDArray(tmp, i8_star, l->tabEleNum, l->loc, currFunc->currBlock);*/
/*               break;*/
/*             }*/
             tmp = l->loc;
             break;
           default:
             Error = TRUE;
             break;
         }
       }
       t->regName = tmp;
     }
    }
        
    break;
  case VarK:
    if(t->childNum == 1)
    { cGen(t->child[0], label, prevFunc);
      t->regName = t->child[0]->regName;
    }
    else if(t->childNum == 2)
    { char *tmp = (char *)malloc(256);
      char *val = (char *)malloc(256);
      char *dst = (char *)malloc(256);
      char *toTmp = (char *)malloc(256);
      
      sprintf(tmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      sprintf(val, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      sprintf(dst, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      
      cGen(t->child[0], label, prevFunc);
      cGen(t->child[1], label, prevFunc);
      
      sprintf(toTmp, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
      appendBinOp(MINUS, dst, double_float, t->child[1]->regName, "1.000000e+00", currFunc->currBlock);
      appendToInt(toTmp, dst, currFunc->currBlock);
 
      switch(t->child[0]->tabType) {
      case Boolean:
        appendGetPtrArray(tmp, t->child[0]->regName, i1, t->child[0]->tabDimen, toTmp, currFunc->currBlock);
        if (t->child[0]->tabDimen == 1)
          appendLD(val, i1_star, tmp, currFunc->currBlock);
        else
          appendLDArray(val, i1, t->child[0]->tabDimen - 1, tmp, currFunc->currBlock);
        break;
      case Number:
        appendGetPtrArray(tmp, t->child[0]->regName, double_float, t->child[0]->tabDimen, toTmp,currFunc->currBlock);
        if (t->child[0]->tabDimen == 1)
          appendLD(val, double_star, tmp, currFunc->currBlock);
        else
          appendLDArray(val, double_float, t->child[0]->tabDimen - 1, tmp, currFunc->currBlock);
          
        break;
      case String:
        appendGetPtrArray(tmp, t->child[0]->regName, i8_star, t->child[0]->tabDimen, toTmp, currFunc->currBlock); 
        if (t->child[0]->tabDimen == 1)
          appendLD(val, i8_star2, tmp, currFunc->currBlock);
        else
          appendLDArray(val, i8_star, t->child[0]->tabDimen - 1, tmp, currFunc->currBlock);
          
        break;
      }
                        
      t->regName = val;
      t->ptrName = tmp;
    }

    break;
  case FunBodyK:
    { LLVMRetTypeList retType = currFunc->retType;
    
      if (t->childNum == 2)
      { LLVMArgTypeList argType = currFunc->parType;
      
        while(argType != NULL)
        { char *dst = malloc(256);
          char *src = malloc(256);
          
          sprintf(src, "%%%s", argType->name);
          sprintf(dst, "%%%s.%s", currFunc->name, argType->name);
          
          if(argType->type != tab)
          { insertAlloc(dst, argType->type, currFunc->block->exitInst);
            insertST(argType->typePtr, dst, argType->type, src, currFunc->block->exitInst);
          }
/*          else*/
/*          { insertAllocArray(dst, argType->tabType, argType->tabEleNum, currFunc->block->exitInst);*/
/*            insertSTArray(argType->tabType, argType->tabEleNum, dst, src, currFunc->block->exitInst);*/
/*          }*/

          argType = argType->next;
        }
      } 

      if (retType != NULL)
      { int retID = 0;
        char *ret = (char *)malloc(256);
        
        while(retType != NULL)
        { char *dst = malloc(256);
          
          sprintf(dst, "%%retval%d", retID++);
          
          if(retType->type != tab)
            insertAlloc(dst, retType->type, currFunc->block->exitInst);
          else
            insertAllocArray(dst, retType->tabType, retType->tabDimen, currFunc->block->exitInst);
          
          retType = retType->next;
        }
        sprintf(ret, "@%s.retval", currFunc->name);
        appendAllocStruct(ret, currFunc->retType, ((MODULE *)(currFunc->parent))->global);
      } 
      
      if (t->childNum == 2)
        cGen(t->child[1], label, prevFunc);
      else
        cGen(t->child[0], label, prevFunc);
    }  
    break;
  case TabK:
    { char *tabName = (char *)malloc(256);
      int fieldNum = 0, fieldID = 0;
      TreeNode *tt = t->child[0];
      LLVMType eleType, elePtrType;
      
      cGen(tt, label, prevFunc);
      sprintf(tabName, "@tab%d", tabID++);

      switch (t->tabType) {
      case Boolean:
        eleType = i1;
        elePtrType = i1_star;
        break;
      case Number:
        eleType = double_float;
        elePtrType = double_star;
        break;
      case String:
        eleType = i8_star;
        elePtrType = i8_star2;
        break;
      }

      while(tt != NULL)
      { 
        if (tt != NULL && tt->sibling == NULL && tt->nodekind == ExpK && 
            tt->child[0]->kind.exp == PreK && tt->child[0]->child[0]->kind.stmt == FunCallK)
        { CallRetList ret = tt->child[0]->child[0]->retRegs;
          
          while (ret != NULL)
          {       
            ret = ret->next;
            fieldNum++;
          }
        }
        else
          fieldNum++;
          
        tt = tt->sibling;
      }

      appendAllocArray(tabName, eleType, t->tabDimen, ((MODULE *)(currFunc->parent))->global);
      t->regName = tabName;

      tt = t->child[0];
      while(tt != NULL)
      {
        if (tt != NULL && tt->sibling == NULL && tt->nodekind == ExpK && 
            tt->child[0]->kind.exp == PreK && tt->child[0]->child[0]->kind.stmt == FunCallK)
        { CallRetList ret = tt->child[0]->child[0]->retRegs;
          
          while (ret != NULL)
          { char *tmp1 = (char *)malloc(256);
            char *tmp2 = (char *)malloc(256);
            
            sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
            sprintf(tmp2, "%d", fieldID);
            appendGetPtrArray(tmp1, tabName, eleType, t->tabDimen, tmp2, currFunc->currBlock);
            if (t->tabDimen == 1)
              appendST(elePtrType, tmp1, eleType, ret->regName, currFunc->currBlock);
            else
              appendSTArray(eleType, t->tabDimen - 1, tmp1, ret->regName, currFunc->currBlock);
              
            fieldID++;
          
            ret = ret->next;
          }
        }
        else
        { char *tmp1 = (char *)malloc(256);
          char *tmp2 = (char *)malloc(256);
          
          sprintf(tmp1, "%%%s.tmp%d", currFunc->currBlock->name, tmpID++);
          sprintf(tmp2, "%d", fieldID);
          appendGetPtrArray(tmp1, tabName, eleType, t->tabDimen, tmp2, currFunc->currBlock);
          if (t->tabDimen == 1)
            appendST(elePtrType, tmp1, eleType, tt->regName, currFunc->currBlock);
          else
            appendSTArray(eleType, t->tabDimen - 1, tmp1, tt->regName, currFunc->currBlock);
          fieldID++;
        }
        tt = tt->sibling;
      }
    }
    break;
  case FieldK:
    cGen(t->child[0], label, prevFunc);
    t->regName = t->child[0]->regName;
    break;
  default:
    Error = TRUE;
    fprintf(listing,"Unknown ExpNode kind\n");
    break;
  }
} /* genExp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree, char * label, FUNC * prevFunc)
{ if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree, label, prevFunc);
        break;
      case ExpK:
        genExp(tree, label, prevFunc);
        break;
      default:
        Error = TRUE;
        break;
    }
    cGen(tree->sibling, label, prevFunc);
  }
}

void declareGlobals(GLOBAL * g)
{ int i;

  BucketList *table = rootSymTable->table;

  for (i=0;i<SIZE;++i)
  { if (table[i] != NULL)
    { BucketList l = table[i];
      while (l != NULL)
      { 
        char *s; 
        
        switch (l->type)
        {
        case Boolean:
          s = malloc(strlen(l->name) + 9);
          strcpy(s, "@global.");
          strcat(s, l->name);
          l->loc = s;
          appendInit(s, 0, i1, "common global", g, TRUE);
          break;
        case Number:
          s = malloc(strlen(l->name) + 9);
          strcpy(s, "@global.");
          strcat(s, l->name);
          l->loc = s;
          appendInit(s, 0, double_float, "common global", g, TRUE);
          break;
        case String:
          s = malloc(strlen(l->name) + 9);
          strcpy(s, "@global.");
          strcat(s, l->name);
          l->loc = s;
          appendInit(s, 0, i8_star, "common global", g, TRUE);
          break;
        case Function:
          break;
        case Table:
        default:
          break;
        }

        l = l->next;
      }
    }
  }
} /* declareGlobals */

void Optimize(MODULE * m)
{ FUNC * f = m->function;
  int change = FALSE;
  
  while(f)
  {
      do
      {
          change = FALSE;
          createFuncDFG(f);
          change |= constProp(f);
          rmUnreachable(f);
          createFuncDFG(f);
          change |= deadCodeElimination(f);
      }while(change);
      
      do
      {
          change = FALSE;
          GetCFGForFUNC(f);
          change |= MergeSingleEdgeBrToBlock(f);
/*          rmUnreachable(f);*/
          change |= RemoveBrToUncondBr(f);
/*          rmUnreachable(f);*/
          change |= MergeIdenticalBrsToBlock(f);
/*          rmUnreachable(f);*/
       }while(change);
      rmUnreachable(f);
      cse(f);

      f = f->next;
  }
}


/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  MODULE * m;
   GLOBAL * g;
   
   m = newModule();
   g = newGlobal(m);

   declareGlobals(g);
   
   LLVMRetTypeList retMain = malloc(sizeof(struct RetTypeRec));
   retMain->type = i32;
   retMain->next = NULL;
   
   mainFunc = appendFunc("main", retMain, NULL, m);
   currFunc = mainFunc;
   
   currSymTable = rootSymTable;
   nextChildSym = rootSymTable->child;
   
   /* generate code for LUA program */
   cGen(syntaxTree, NULL, mainFunc);
   mainFunc->currBlock->exitInst = appendRet(retMain, "0", mainFunc->currBlock);
   
   Optimize(m);

   printModule(m);
}


