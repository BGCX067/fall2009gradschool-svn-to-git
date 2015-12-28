/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the LUA compiler                             */
/* Haicheng                                         */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"
#include "util.h"

/* counter for variable memory locations */
static int location = 0;
int isFuncName = FALSE;
int isPar = FALSE;
int isLocal = FALSE;

void newBlock()
{ HashTable * tmpSymTable, *t;
  tmpSymTable = st_create();
  t = currSymTable->child;
  tmpSymTable->parent = currSymTable;
  if (t != NULL)
  { while (t->sibling != NULL)
      t = t->sibling;
    t->sibling = tmpSymTable;
    currSymTable = tmpSymTable; 
  } else {
    currSymTable->child = tmpSymTable;
    currSymTable = tmpSymTable;
  }
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
void insertNode( TreeNode * t)
{ BucketList l = st_lookup(t->attr.name);
  if (l == NULL || isLocal == TRUE || isPar == TRUE)
  /* not yet in table, so treat as new definition */
    st_insert(t->attr.name,t->lineno,location++);
  else
  /* already in table, so ignore location, 
  add line number of use only  */
    st_update(t->lineno,l);
}

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverseSym( TreeNode * t)
{ if (t != NULL)
    if (t->nodekind==StmtK)
    { switch (t->kind.stmt) {
        case AssignK:
          traverseSym(t->child[0]);
          traverseSym(t->child[1]);
          traverseSym(t->sibling);
          break;
        case FunCallK:
          traverseSym(t->child[0]);
          traverseSym(t->child[1]);
          traverseSym(t->sibling);
          break;
        case DoK:
          newBlock();
          traverseSym(t->child[0]);
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case WhileK:
          traverseSym(t->child[0]);
          newBlock();
          traverseSym(t->child[1]);
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case RepeatK:
          newBlock();
          traverseSym(t->child[0]);
          traverseSym(t->child[1]);
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case IfK:
        case ElseIfK:
          traverseSym(t->child[0]);
          newBlock();
          traverseSym(t->child[1]);
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case ElseK:
          newBlock();
          traverseSym(t->child[0]);
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case ForNumK:
          newBlock();
          isRootSymTab = FALSE;
          traverseSym(t->child[0]);
          traverseSym(t->child[1]);
          traverseSym(t->child[2]);
          if (t->childNum == 5)
          {
            traverseSym(t->child[3]);
            isRootSymTab = TRUE;
            traverseSym(t->child[4]);
          } else {
            isRootSymTab = TRUE;
            traverseSym(t->child[3]);          
          }
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case FunK:
          newBlock();
          isFuncName = TRUE;
          traverseSym(t->child[0]);
          isFuncName = FALSE;
          t->funSymTab = currSymTable;
          traverseSym(t->child[1]);
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case LocFunK:
          isRootSymTab = FALSE;
          newBlock();
          isFuncName = TRUE;
          isLocal = TRUE;
          traverseSym(t->child[0]);
          isLocal = FALSE;
          isFuncName = FALSE;
          t->funSymTab = currSymTable;
          traverseSym(t->child[1]);
          isRootSymTab = TRUE;
          currSymTable = currSymTable->parent;
          traverseSym(t->sibling);
          break;
        case LocAssignK:
          isRootSymTab = FALSE;
          isLocal = TRUE;
          traverseSym(t->child[0]);
          isLocal = FALSE;
          isRootSymTab = TRUE;
          traverseSym(t->child[1]);
          traverseSym(t->sibling);
          break;
        case ReturnK:
          if (t->childNum == 1)
          {
            traverseSym(t->child[0]);
          } 
          traverseSym(t->sibling);
          break;
        case BreakK:
          traverseSym(t->sibling);
          break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (t->nodekind==ExpK)
    { switch (t->kind.exp) {
        case BinOpK:
          traverseSym(t->child[0]);
          traverseSym(t->child[1]);
          traverseSym(t->sibling);
          break;
        case UnOpK:
          traverseSym(t->child[0]);
          traverseSym(t->sibling);
          break;
        case BoolConstK:
          traverseSym(t->sibling);
          break;
        case RealConstK:
          traverseSym(t->sibling);
          break;
        case StringConstK:
          traverseSym(t->sibling);
          break;
        case VarLenK:
          traverseSym(t->sibling);
          break;
        case PreK:
          traverseSym(t->child[0]);
          traverseSym(t->sibling);
          break;
        case TabK:
          traverseSym(t->child[0]);
          traverseSym(t->sibling);
          break;
        case IdK:
          insertNode(t);
          traverseSym(t->sibling);
          break;
        case VarK:
          traverseSym(t->child[0]);
          if (t->childNum == 2)
          {
            traverseSym(t->child[1]);
          } 
          traverseSym(t->sibling);
          break;
        case FunBodyK:
          if (t->childNum == 2)
          { isRootSymTab = FALSE;
            isPar = TRUE;
            traverseSym(t->child[0]);
            isRootSymTab = TRUE;
            isPar = FALSE;
            traverseSym(t->child[1]);
          } else
          {
            traverseSym(t->child[0]);
          }

          traverseSym(t->sibling);
          break;
        case FieldK:
          traverseSym(t->child[0]);
          if (t->childNum == 2)
          {
            traverseSym(t->child[1]);
          } 
          traverseSym(t->sibling);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
}

void traversePrintSym (FILE * listing, HashTable * t)
{ if (t != NULL)
  { printSymTab (listing, t);
    traversePrintSym(listing, t->child);
    traversePrintSym(listing, t->sibling);
  }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ rootSymTable = st_create ();
  currSymTable = rootSymTable;
  isRootSymTab = TRUE;
  traverseSym(syntaxTree);
  if (TraceAnalyze)
  { traversePrintSym (listing, rootSymTable);}
}

void entBlock()
{ currSymTable = nextChildSym;
  nextChildSym = nextChildSym->child;
}

void entFunBlock()
{ entBlock();
  currFunSymTab = currSymTable;
}

void lvBlock()
{ nextChildSym = currSymTable->sibling;
  currSymTable = currSymTable->parent;
}

void lvFunBlock()
{ lvBlock();
  currFunSymTab = currSymTable;
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

static void traverseType( TreeNode * t)
{ if (t != NULL)
    if (t->nodekind==StmtK)
    { switch (t->kind.stmt) {
        case AssignK:
          traverseType(t->child[1]);
          traverseType(t->child[0]);
          { TreeNode * vt, * et;
            vt = t->child[0];
            et = t->child[1];
            
            while(vt != NULL)
            { 
              if (vt->childNum == 1)
              { BucketList l = st_lookup(vt->child[0]->attr.name);
                if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && 
                   et->kind.exp == PreK && et->child[0]->kind.stmt == FunCallK)
                { BucketList funl = st_lookup(et->child[0]->child[0]->child[0]->child[0]->attr.name);
                  HashTable *funh = (HashTable *)funl->ptr;
                  RetTypeList funr = funh->retType;
                  
                  while (funr != NULL)
                  { vt->type = funr->type;
                    l->type = funr->type;
                    vt->child[0]->type = vt->type;
                    
                    if(funr->type == Table)
                    { vt->tabType = funr->tabType;
                      vt->tabEleNum = funr->tabEleNum;
                      vt->tabDimen = funr->tabDimen;
                      l->tabType = funr->tabType;
                      l->tabEleNum = funr->tabEleNum;
                      l->tabDimen = funr->tabDimen;
                      vt->child[0]->tabType = funr->tabType;
                      vt->child[0]->tabDimen = funr->tabDimen;
                      vt->child[0]->tabEleNum = funr->tabEleNum;
                    }
                    funr = funr->next;
                    vt = vt->sibling;
                    if(vt == NULL) break;
                    l = st_lookup(vt->child[0]->attr.name);
                  }
                  break;
                }
                else if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && et->kind.exp == VarLenK)
                { VarArgTypeList funva = currFunSymTab->varArgType;
                  
                  while (funva != NULL)
                  { vt->type = funva->type;
                    l->type = funva->type;
                    vt->child[0]->type = vt->type;
                    
                    if(funva->type == Table)
                    { vt->tabType = funva->tabType;
                      l->tabType = funva->tabType;
                      vt->child[0]->tabType = vt->tabType;
                    }
                    funva = funva->next;
                    vt = vt->sibling;
                    if(vt == NULL) break;
                  }
                  break;
                }
                else if (et != NULL)
                { vt->type = et->type;
                  l->type = et->type;
                  vt->child[0]->type = vt->type;
                  
                  if(et->type == Table)
                  { vt->tabType = et->tabType;
                    vt->tabEleNum = et->tabEleNum;
                    vt->tabDimen = et->tabDimen;
                    l->tabType = et->tabType;
                    l->tabEleNum = et->tabEleNum;
                    l->tabDimen = et->tabDimen;
                    vt->child[0]->tabType = vt->tabType;
                    vt->child[0]->tabEleNum = vt->tabEleNum;
                    vt->child[0]->tabDimen = vt->tabDimen;
                  }

                  et = et->sibling;
                  if(et == NULL) break;
                }
              }
              
              if(vt !=NULL ) vt = vt->sibling;
            }
          }

          traverseType(t->sibling);
          break;
        case LocAssignK:
          traverseType(t->child[1]);
          traverseType(t->child[0]);
          { TreeNode * vt, * et;
            vt = t->child[0];
            et = t->child[1];
            
            while(vt != NULL)
            { 
              { BucketList l = st_lookup(vt->attr.name);
                if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && 
                   et->kind.exp == PreK && et->child[0]->kind.stmt == FunCallK)
                { BucketList funl = st_lookup(et->child[0]->child[0]->child[0]->child[0]->attr.name);
                  HashTable *funh = (HashTable *)funl->ptr;
                  RetTypeList funr = funh->retType;
                  
                  while (funr != NULL)
                  { vt->type = funr->type;
                    l->type = funr->type;
                    
                    if(funr->type == Table)
                    { vt->tabType = funr->tabType;
                      vt->tabEleNum = funr->tabEleNum;
                      l->tabType = funr->tabType;
                      l->tabEleNum = funr->tabEleNum;
                    }
                    funr = funr->next;
                    vt = vt->sibling;
                    if(vt == NULL) break;
                    l = st_lookup(vt->attr.name);
                  }
                  break;
                }
                else if (et != NULL && et->sibling == NULL && et->nodekind == ExpK && et->kind.exp == VarLenK)
                { VarArgTypeList funva = currFunSymTab->varArgType;
                  
                  while (funva != NULL)
                  { vt->type = funva->type;
                    l->type = funva->type;
                    vt->child[0]->type = vt->type;
                    
                    if(funva->type == Table)
                    { vt->tabType = funva->tabType;
                      l->tabType = funva->tabType;
                      vt->child[0]->tabType = vt->tabType;
                    }
                    funva = funva->next;
                    vt = vt->sibling;
                    if(vt == NULL) break;
                  }
                  break;
                }
                else if (et != NULL)
                { vt->type = et->type;
                  l->type = et->type;
                  
                  if(et->type == Table)
                  { vt->tabType = et->tabType;
                    vt->tabEleNum = et->tabEleNum;
                    vt->tabDimen = et->tabDimen;
                    l->tabType = et->tabType;
                    l->tabEleNum = et->tabEleNum;
                    l->tabDimen = et->tabDimen;
                  }
                  
                  et = et->sibling;
                  if(et == NULL) break;
                }
              }
              
              if(vt !=NULL ) vt = vt->sibling;
            }
          }

          traverseType(t->sibling);
          break;
        case FunCallK:
          traverseType(t->child[0]);
          
          traverseType(t->child[1]);

          if(strcmp(t->child[0]->child[0]->child[0]->attr.name, "print") == 0) goto ENDOFNOTPRINT;
          { BucketList funl = st_lookup(t->child[0]->child[0]->child[0]->attr.name);
            HashTable *funh = (HashTable *)funl->ptr;
            ArgTypeList funa = funh->argType;
            VarArgTypeList funvaCurr = funh->varArgType;
            VarArgTypeList funvaPrev = funvaCurr;
            TreeNode *tt;
            
            tt = t->child[1];
            
            while (tt != NULL)
            { if (tt->sibling == NULL && tt->nodekind == ExpK && tt->kind.exp == VarLenK)
              { VarArgTypeList funva = currFunSymTab->varArgType;
                  
                while (funva != NULL)
                { if(funa != NULL)
                  { funa->arg->type = funva->type;
                    if(funva->type == Table)
                      funa->arg->tabType = funva->tabType;
                    funa = funa->next;
                  }
                  else
                  { if (funvaCurr != NULL)
                    { funvaCurr->type = funva->type;
                      if (funva->type == Table)
                        funvaCurr->tabType = funva->tabType;
                      funvaPrev = funvaCurr;
                      funvaCurr = funvaCurr->next;
                    }
                    else
                    { funvaCurr = malloc(sizeof(struct VarArgTypeRec));
                      funvaCurr->type = funva->type;
                      if (funva->type == Table)
                        funvaCurr->tabType = funva->tabType;
                      else
                        funvaCurr->tabType = NilTy; 
                      funvaCurr->next = NULL;
                      
                      if(funvaPrev)
                        funvaPrev->next = funvaCurr;
                        
                      funvaPrev = funvaCurr;
                      funvaCurr = funvaCurr->next;
                    }
                  }
                  funva = funva->next;
                }
              }
              else if (tt->sibling == NULL && tt->nodekind == ExpK && 
                      tt->kind.exp == PreK && tt->child[0]->kind.stmt == FunCallK)
              { BucketList funl = st_lookup(tt->child[0]->child[0]->child[0]->child[0]->attr.name);
                HashTable *funh = (HashTable *)funl->ptr;
                RetTypeList funr = funh->retType;
                  
                while (funr != NULL)
                { if(funa != NULL)
                  { funa->arg->type = funr->type;
                    if(funr->type == Table)
                    { funa->arg->tabType = funr->tabType;
                      funa->arg->tabEleNum = funr->tabEleNum;
                      funa->arg->tabDimen = funr->tabDimen;
                      }
                      
                    funa = funa->next;
                  }
                  else
                  { if (funvaCurr != NULL)
                    { funvaCurr->type = funr->type;
                      if (funr->type == Table)
                        funvaCurr->tabType = funr->tabType;
                      funvaPrev = funvaCurr;
                      funvaCurr = funvaCurr->next;
                    }
                    else
                    { funvaCurr = malloc(sizeof(struct VarArgTypeRec));
                      funvaCurr->type = funr->type;
                      if (funr->type == Table)
                        funvaCurr->tabType = funr->tabType;
                      else
                        funvaCurr->tabType = NilTy; 
                      funvaCurr->next = NULL;
                      
                      if(funvaPrev)
                        funvaPrev->next = funvaCurr;
                        
                      funvaPrev = funvaCurr;
                      funvaCurr = funvaCurr->next;
                    }
                  }
                  funr = funr->next;
                }
              }
              else
              {
              if (funa != NULL)
                {funa->arg->type = tt->type;
                if (tt->type == Table)
                { funa->arg->tabType = tt->tabType;
                  funa->arg->tabEleNum = tt->tabEleNum;
                  funa->arg->tabDimen = tt->tabDimen;
                }
                  
                funa = funa->next;
                } 
                else
                { if (funvaCurr != NULL)
                  { funvaCurr->type = tt->type;
                    if (tt->type == Table)
                      funvaCurr->tabType = tt->tabType;
                    funvaPrev = funvaCurr;
                    funvaCurr = funvaCurr->next;
                  }
                  else
                  { funvaCurr = malloc(sizeof(struct VarArgTypeRec));
                    funvaCurr->type = tt->type;
                    if (tt->type == Table)
                      funvaCurr->tabType = tt->tabType;
                    else
                      funvaCurr->tabType = NilTy; 
                    funvaCurr->next = NULL;
                    
                    if(funvaPrev)
                      funvaPrev->next = funvaCurr;
                      
                    funvaPrev = funvaCurr;
                    funvaCurr = funvaCurr -> next;
                  }
                }
              }

              tt = tt->sibling;
            }
          }
            
          { BucketList funl = st_lookup(t->child[0]->child[0]->child[0]->attr.name);
            HashTable *funh = (HashTable *)funl->ptr;
            RetTypeList funr = funh->retType;
            
            if (funr != NULL)
              t->type = funr->type;
          }
ENDOFNOTPRINT:

          traverseType(t->sibling);
          break;
        case DoK:
          entBlock();
          traverseType(t->child[0]);
          lvBlock();
          traverseType(t->sibling);
          break;
        case WhileK:
          traverseType(t->child[0]);
          entBlock();
          traverseType(t->child[1]);
          lvBlock();
          traverseType(t->sibling);
          break;
        case RepeatK:
          entBlock();
          traverseType(t->child[0]);
          traverseType(t->child[1]);
          lvBlock();
          traverseType(t->sibling);
          break;
        case IfK:
        case ElseIfK:
          traverseType(t->child[0]);
          entBlock();
          traverseType(t->child[1]);
          lvBlock();
          traverseType(t->sibling);
          break;
        case ElseK:
          entBlock();
          traverseType(t->child[0]);
          lvBlock();
          traverseType(t->sibling);
          break;
        case ForNumK:
          entBlock();
          traverseType(t->child[0]);
          
          traverseType(t->child[1]);
/*          if(t->child[1]->type != String || t->child[1]->type != Number)*/
/*            typeError(t,"iteration variable of for loop is non-number value");*/
            
          traverseType(t->child[2]);
/*          if(t->child[2]->type != String || t->child[2]->type != Number)*/
/*            typeError(t,"iteration variable of for loop is non-number value");*/
            
          if (t->childNum == 5)
          {
            traverseType(t->child[3]);
/*            if(t->child[3]->type != String || t->child[3]->type != Number)*/
/*              typeError(t,"iteration variable of for loop is non-number value");*/
              
            t->child[0]->type = Number;

            { BucketList l = st_lookup(t->child[0]->attr.name);
              l->type = Number;
            }
            
            traverseType(t->child[4]);
          } else {
            t->child[0]->type = Number;
            
            { BucketList l = st_lookup(t->child[0]->attr.name);
              l->type = Number;
            }
            
            traverseType(t->child[3]);

          }
          lvBlock();
          traverseType(t->sibling);
          break;
        case FunK:
        case LocFunK:
          traverseType(t->child[0]);
          entFunBlock();
          traverseType(t->child[1]);
          lvFunBlock();
          t->child[0]->type = Function;
          { BucketList l = st_lookup(t->child[0]->attr.name);
            l->type = Function;
          }
          traverseType(t->sibling);
          break;
        case ReturnK:
          if (t->childNum == 1)
          {
            traverseType(t->child[0]);
            { TreeNode *retExp = t->child[0];
              RetTypeList curr = currFunSymTab->retType;
              
              if (curr == NULL)
              { while(retExp != NULL)
                { 
                  if (retExp->sibling == NULL && retExp->nodekind == ExpK && retExp->kind.exp == VarLenK)
                  {
                    VarArgTypeList funva = currFunSymTab->varArgType;
                  
                    while (funva != NULL)
                    { RetTypeList next = (RetTypeList) malloc(sizeof(struct RetTypeRec));
                      next->type = funva->type;
                      
                      if(funva->type == Table)
                        next->tabType = funva->tabType;
                      else
                        next->tabType = NilTy;
                      
                      next->next = NULL;
                      
                      if(curr == NULL)
                        currFunSymTab->retType = next;
                      else
                        curr->next = next;
                        
                      curr->next = next;
                      funva = funva->next;
                    }
                  }
                  else if (retExp->sibling == NULL && retExp->nodekind == ExpK && 
                          retExp->kind.exp == PreK && retExp->child[0]->kind.stmt == FunCallK)
                  {
                    BucketList funl = st_lookup(retExp->child[0]->child[0]->child[0]->child[0]->attr.name);
                    HashTable *funh = (HashTable *)funl->ptr;
                    RetTypeList funr = funh->retType;
                  
                    while (funr != NULL)
                    { RetTypeList next = (RetTypeList) malloc(sizeof(struct RetTypeRec));
                      next->type = funr->type;
                      
                      if(funr->type == Table)
                      { next->tabType = funr->tabType;
                        next->tabEleNum = funr->tabEleNum;
                        next->tabDimen = funr->tabDimen;
                        }
                      else
                        next->tabType = NilTy;
                      
                      next->next = NULL;
                      
                      if(curr == NULL)
                        currFunSymTab->retType = next;
                      else
                        curr->next = next;
                        
                      curr->next = next;
                      funr = funr->next;
                    }
                  }
                  else
                  {
                    RetTypeList next = (RetTypeList) malloc(sizeof(struct RetTypeRec));
                    next->type = retExp->type;
                    
                    if(retExp->type == Table)
                    { next->tabType = retExp->tabType;
                      next->tabEleNum = retExp->tabEleNum;
                      next->tabDimen = retExp->tabDimen;
                    }
                    else
                      next->tabType = NilTy;
                      
                    next->next = NULL;
                    
                    if(curr == NULL)
                      currFunSymTab->retType = next;
                    else
                      curr->next = next;

                    curr = next;
                  }
                  retExp = retExp->sibling;
                }
              }
              else
              { while(retExp != NULL)
                { 
                  if (retExp->sibling == NULL && retExp->nodekind == ExpK && retExp->kind.exp == VarLenK)
                  { 
                    VarArgTypeList funva = currFunSymTab->varArgType;
                    RetTypeList next = curr;
                    
                    while (funva != NULL)
                    { 
                      if (next == NULL)
                      {
                        next = (RetTypeList) malloc(sizeof(struct RetTypeRec));
                        next->type = funva->type;
                        
                        if(funva->type == Table)
                          next->tabType = funva->tabType;
                        else
                          next->tabType = NilTy;
                        
                        next->next = NULL;
                        
                        curr->next = next;
                        curr = next;
                        next = curr->next;
                      }
                      else
                      {
                        curr->type = funva->type;
                        
                        if(funva->type == Table)
                          curr->tabType = funva->tabType;
                        else
                          curr->tabType = NilTy;
                      
                        curr = curr->next;
                        next = curr;
                      }

                      funva = funva->next;
                    }
                  }
                  else if (retExp->sibling == NULL && retExp->nodekind == ExpK && 
                          retExp->kind.exp == PreK && retExp->child[0]->kind.stmt == FunCallK)
                  { 
                    BucketList funl = st_lookup(retExp->child[0]->child[0]->child[0]->child[0]->attr.name);
                    HashTable *funh = (HashTable *)funl->ptr;
                    RetTypeList funr = funh->retType;
                    RetTypeList next = curr;
                    
                    while (funr != NULL)
                    { 
                      if (next == NULL)
                      {
                        next = (RetTypeList) malloc(sizeof(struct RetTypeRec));
                        next->type = funr->type;
                        
                        if(funr->type == Table)
                        { next->tabType = funr->tabType;
                          next->tabEleNum = funr->tabEleNum;
                          next->tabDimen = funr->tabDimen;
                        }
                        else
                          next->tabType = NilTy;
                        
                        next->next = NULL;
                        
                        curr->next = next;
                        curr = next;
                        next = curr->next;
                      }
                      else
                      {
                        curr->type = funr->type;
                        
                        if(funr->type == Table)
                        { curr->tabType = funr->tabType;
                          curr->tabEleNum = funr->tabEleNum;
                          curr->tabDimen = funr->tabDimen;
                        }
                        else
                          curr->tabType = NilTy;
                      
                        curr = curr->next;
                        next = curr;
                      }

                      funr = funr->next;
                    }
                  }
                  else
                  {
                    curr->type = retExp->type;
                    
                    if(retExp->type == Table)
                    { curr->tabType = retExp->tabType;
                      curr->tabEleNum = retExp->tabEleNum;
                      curr->tabDimen = retExp->tabDimen;
                    }
                     
                    else
                      curr->tabType = NilTy;
                      
                    curr = curr->next;
                  }
                  retExp = retExp->sibling;
                }
              }

            }
          } 
          traverseType(t->sibling);
          break;
        case BreakK:
          traverseType(t->sibling);
          break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (t->nodekind==ExpK)
    { switch (t->kind.exp) {
        case BinOpK:
          if (t->attr.op == PLUS  || t->attr.op == MINUS
           || t->attr.op == TIMES || t->attr.op == OVER
           || t->attr.op == MOD   || t->attr.op == POW)
          { traverseType(t->child[0]);
/*            if(t->child[0]->type != String || t->child[0]->type != Number)*/
/*              typeError(t,"Arithmetic Op applied to non-number");*/
            
            traverseType(t->child[1]);
/*            if(t->child[1]->type != String || t->child[1]->type != Number)*/
/*              typeError(t,"Arithmetic Op applied to non-number");*/

            t->type = Number;
          } 
          else if (t->attr.op == EQ  || t->attr.op == NEQ
           || t->attr.op == LE || t->attr.op == GE
           || t->attr.op == LT   || t->attr.op == GT)
          { traverseType(t->child[0]);
            traverseType(t->child[1]);
            t->type = Boolean;} 
          else if (t->attr.op == AND )
          { traverseType(t->child[0]);
            traverseType(t->child[1]);
            t->type = t->child[0]->type;} 
          else if (t->attr.op == OR )
          { traverseType(t->child[0]);
            traverseType(t->child[1]);
            t->type = t->child[1]->type;} 
          else if (t->attr.op == DDOT )
          { traverseType(t->child[0]);
/*            if(t->child[0]->type != String || t->child[0]->type != Number)*/
/*              typeError(t,"Concatenation Op applied to non-string");*/
            
            traverseType(t->child[1]);
/*            if(t->child[1]->type != String || t->child[1]->type != Number)*/
/*              typeError(t,"Concatenation Op applied to non-string");*/

            t->type = String;
          } 
            
          traverseType(t->sibling);
          break;
        case UnOpK:
          if (t->attr.op == MINUS)
          { traverseType(t->child[0]);
/*            if(t->child[0]->type != String || t->child[0]->type != Number)*/
/*              typeError(t,"for of non-number value");*/
              t->type = Number;
          } 
          else if (t->attr.op == NOT )
          { traverseType(t->child[0]);
            t->type = Boolean;} 
          else if (t->attr.op == POUND )
          { traverseType(t->child[0]);
/*            if(t->child[0]->type != String || t->child[0]->type != Table)*/
/*              typeError(t,"Length Op applied to non-string or non-table");*/
            
            t->type = Number;
          } 
            
          traverseType(t->sibling);
          break;
        case BoolConstK:
          t->type = Boolean;
          traverseType(t->sibling);
          break;
        case RealConstK:
          t->type = Number;
          traverseType(t->sibling);
          break;
        case StringConstK:
          t->type = String;
          traverseType(t->sibling);
          break;
        case VarLenK:
          if(!currFunSymTab->varArgType)
            t->type = currFunSymTab->varArgType->type;
          else
            t->type = NilTy;
            
          traverseType(t->sibling);
          break;
        case PreK:
          traverseType(t->child[0]);
          t->type = t->child[0]->type;
          if(t->type == Table)
          { t->tabType = t->child[0]->tabType;
            t->tabEleNum = t->child[0]->tabEleNum;
            t->tabDimen = t->child[0]->tabDimen;
          }
           
          traverseType(t->sibling);
          break;
        case TabK:
          if (t->childNum == 1) 
          { int i = 0;
            traverseType(t->child[0]);
            
            if(t->child[0]->tabDimen == 0)
              t->tabType = t->child[0]->type;
            else
              t->tabType = t->child[0]->tabType;

            t->tabDimen = t->child[0]->tabDimen + 1;
            
            { TableEleList l = (TableEleList)t->ptr;
              TreeNode *tt = t->child[0];
              TreeNode *tmp;
              
              while (tt != NULL)
              {
                if (tt->sibling == NULL && tt->nodekind == ExpK && tt->kind.exp == VarLenK)
                { VarArgTypeList funva = currFunSymTab->varArgType;
                    
                  while (funva != NULL)
                  {
                    if(l == NULL)
                    { t->ptr = malloc(sizeof(struct TableEleRec));
                      l = (TableEleList)t->ptr;
                    }
                    else
                    { l->next = malloc(sizeof(struct TableEleRec));
                      l = l->next;
                    }
                    
                    tmp = newExpNode(RealConstK);
                    tmp->attr.realVal = i++;
                    l->index = tmp;
                    l->next = NULL;
                    
                    funva = funva->next;
                  }
                }
                else if (tt->sibling == NULL && tt->nodekind == ExpK && 
                        tt->child[0]->kind.exp == PreK && tt->child[0]->child[0]->kind.stmt == FunCallK)
                { BucketList funl = st_lookup(tt->child[0]->child[0]->child[0]->child[0]->child[0]->attr.name);
                  HashTable *funh = (HashTable *)funl->ptr;
                  RetTypeList funr = funh->retType;
                    
                  while (funr != NULL)
                  {
                    if(l == NULL)
                    { t->ptr = malloc(sizeof(struct TableEleRec));
                      l = (TableEleList)t->ptr;
                    }
                    else
                    { l->next = malloc(sizeof(struct TableEleRec));
                      l = l->next;
                    }
                    
                    tmp = newExpNode(RealConstK);
                    tmp->attr.realVal = i++;
                    l->index = tmp;
                    l->next = NULL;
                    
                    funr = funr->next;
                  }
                }
                else
                {
                  if(l == NULL)
                  { t->ptr = malloc(sizeof(struct TableEleRec));
                    l = (TableEleList)t->ptr;
                  }
                  else
                  { l->next = malloc(sizeof(struct TableEleRec));
                    l = l->next;
                  }
                  if(tt->child[0]->childNum == 2)
                    l->index = tt->child[0]->child[0];
                  else
                  { tmp = newExpNode(RealConstK);
                    tmp->attr.realVal = i++;
                    l->index = tmp;
                  }
                  l->next = NULL;
                
                }
                tt = tt->sibling;
              }
            }
            t->tabEleNum = i;
          }

          t->type = Table;
          traverseType(t->sibling);
          break;
        case IdK:
          if (t->type == NilTy)
          { BucketList l = st_lookup(t->attr.name);
            t->type = l->type;
            if(t->type == Table)
            { t->tabType = l->tabType;
              t->tabEleNum = l->tabEleNum;
              t->tabDimen = l->tabDimen;
            }
             
          }
              
          traverseType(t->sibling);
          break;
        case VarK:
          if (t->childNum == 2)
          { traverseType(t->child[0]);
            traverseType(t->child[1]);

            if (t->child[0]->tabDimen == 1) 
              t->type = t->child[0]->tabType;
            else
            { t->type = t->child[0]->type;
              t->tabType = t->child[0]->tabType;
              t->tabDimen = t->child[0]->tabDimen - 1;
            }

          } 
          else if (t->childNum == 1)
          { traverseType(t->child[0]);
            t->type = t->child[0]->type;
            if (t->type == Table)
            { t->tabType = t->child[0]->tabType;
              t->tabEleNum = t->child[0]->tabEleNum;
              t->tabDimen = t->child[0]->tabDimen;
            }
          }
          traverseType(t->sibling);
          break;
        case FunBodyK:
          if (t->childNum == 2)
          { traverseType(t->child[0]);
            traverseType(t->child[1]);
          } 
          else
            traverseType(t->child[0]);
            
          traverseType(t->sibling);
          break;
        case FieldK:
          traverseType(t->child[0]);
          if (t->childNum == 2)
          {
            traverseType(t->child[1]);
          } 
          
          if (t->childNum == 2)
            t->type = t->child[1]->type;
          else
          {
            t->type = t->child[0]->type;
            t->tabType = t->child[0]->tabType;
            t->tabDimen = t->child[0]->tabDimen;
          }
            
          traverseType(t->sibling);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
}


/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ currSymTable = rootSymTable;
  nextChildSym = rootSymTable->child;
  traverseType(syntaxTree);
}
