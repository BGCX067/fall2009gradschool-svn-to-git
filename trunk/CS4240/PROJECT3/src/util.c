/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the LUA compiler                            */
/* Haicheng                                         */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case BREAK:
    case DO:
    case ELSE:
    case ELSEIF:
    case END:
    case FOR:
    case FUNCTION:
    case IF:
    case IN:
    case LOCAL:
    case REPEAT:
    case RETURN:
    case THEN:
    case UNTIL:
    case WHILE:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case AND: fprintf(listing,"and\n"); break;
    case False: fprintf(listing,"false\n"); break;
    case NIL: fprintf(listing,"nil\n"); break;
    case NOT: fprintf(listing,"not\n"); break;
    case OR: fprintf(listing,"or\n"); break;
    case True: fprintf(listing,"true\n"); break;
    case PLUS: fprintf(listing,"+\n"); break;
    case MINUS: fprintf(listing,"-\n"); break;
    case TIMES: fprintf(listing,"*\n"); break;
    case OVER: fprintf(listing,"/\n"); break;
    case MOD: fprintf(listing,"%%\n"); break;
    case POW: fprintf(listing,"^\n"); break;
    case POUND: fprintf(listing,"#\n"); break;
    case EQ: fprintf(listing,"==\n"); break;
    case NEQ: fprintf(listing,"~=\n"); break;
    case LE: fprintf(listing,"<=\n"); break;
    case GE: fprintf(listing,">=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case GT: fprintf(listing,">\n"); break;
    case ASSIGN: fprintf(listing,"=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case LCBRACK: fprintf(listing,"{\n"); break;
    case RCBRACK: fprintf(listing,"}\n"); break;
    case LSBRACK: fprintf(listing,"[\n"); break;
    case RSBRACK: fprintf(listing,"]\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case COLON: fprintf(listing,":\n"); break;
    case COMMA: fprintf(listing,",\n"); break;
    case DOT: fprintf(listing,".\n"); break;
    case DDOT: fprintf(listing,"..\n"); break;
    case TDOT: fprintf(listing,"...\n"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUMBER:
      fprintf(listing,
          "NUM, val= %s\n",tokenString);
      break;
    case NAME:
      fprintf(listing,
          "NAME, name= %s\n",tokenString);
      break;
    case STRING:
      fprintf(listing,
          "STRING, string= %s\n", tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newTermNode creates a new terminal
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
    t->childNum = 0;
    t->siblingNum = 0;
    t->type = NilTy;
    t->tabType = NilTy;
    t->funSymTab = NULL;
    t->ptr = NULL;
    t->regName = NULL;
    t->ptrName = NULL;
    t->retRegs = NULL;
    t->tabEleNum = 0;
    t->tabDimen = 0;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = NilTy;
    t->tabType = NilTy;
    t->childNum = 0;
    t->siblingNum = 0;
    t->funSymTab = NULL;
    t->ptr = NULL;
    t->regName = NULL;
    t->ptrName = NULL;
    t->retRegs = NULL;
    t->tabEleNum = 0;
    t->tabDimen = 0;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = (char *)malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  fprintf(listing,"\n");
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case AssignK:
          fprintf(listing,"Assign\n");
          break;
        case FunCallK:
          fprintf(listing,"Function Call\n");
          break;
        case DoK:
          fprintf(listing,"Do\n");
          break;
        case WhileK:
          fprintf(listing,"While\n");
          break;
        case RepeatK:
          fprintf(listing,"Repeat\n");
          break;
        case IfK:
          fprintf(listing,"If\n");
          break;
        case ElseIfK:
          fprintf(listing,"ElseIf\n");
          break;
        case ElseK:
          fprintf(listing,"Else\n");
          break;
        case ForNumK:
          fprintf(listing,"For Number\n");
          break;
        case FunK:
          fprintf(listing,"Function\n");
          break;
        case LocFunK:
          fprintf(listing,"Local Function\n");
          break;
        case LocAssignK:
          fprintf(listing,"Local Assign\n");
          break;
        case ReturnK:
          fprintf(listing,"Return\n");
          break;
        case BreakK:
          fprintf(listing,"Break\n");
          break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case BinOpK:
        case UnOpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case BoolConstK:
          fprintf(listing,"Const: %d\n",tree->attr.boolVal);
          break;
        case RealConstK:
          fprintf(listing,"Const: %f\n",tree->attr.realVal);
          break;
        case StringConstK:
          fprintf(listing,"Const: %s\n",tree->attr.name);
          break;
        case VarLenK:
          fprintf(listing,"...\n");
          break;
        case PreK:
          fprintf(listing,"Prefixexp\n");
          break;
        case TabK:
          fprintf(listing,"Tableconstructor\n");
          break;
        case IdK:
          fprintf(listing,"Name: %s\n",tree->attr.name);
          break;
        case VarK:
          fprintf(listing,"Var\n");
          break;
        case FunBodyK:
          fprintf(listing,"Funcbody\n");
          break;
        case FieldK:
          fprintf(listing,"Field\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

void printType( TreeNode * tree )
{
  switch (tree->type) {
    case NilTy:
      fprintf(listing," Nil\n");
      break; 
    case Boolean:
      fprintf(listing," Boolean\n");
      break; 
    case Number:
      fprintf(listing," Number\n");
      break; 
    case String:
      fprintf(listing," String\n");
      break; 
    case Function:
      fprintf(listing," Function\n");
      break; 
    case Table:
      fprintf(listing," Table\n");
      break; 
    default:
      fprintf(listing," Unknown Type\n");
      break;     
  }
}

void printTypeTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case AssignK:
          fprintf(listing,"Assign\n");
          break;
        case FunCallK:
          fprintf(listing,"Function Call");
          printType(tree);
          break;
        case DoK:
          fprintf(listing,"Do\n");
          break;
        case WhileK:
          fprintf(listing,"While\n");
          break;
        case RepeatK:
          fprintf(listing,"Repeat\n");
          break;
        case IfK:
          fprintf(listing,"If\n");
          break;
        case ElseIfK:
          fprintf(listing,"ElseIf\n");
          break;
        case ElseK:
          fprintf(listing,"Else\n");
          break;
        case ForNumK:
          fprintf(listing,"For Number\n");
          break;
        case FunK:
          fprintf(listing,"Function\n");
          break;
        case LocFunK:
          fprintf(listing,"Local Function\n");
          break;
        case LocAssignK:
          fprintf(listing,"Local Assign\n");
          break;
        case ReturnK:
          fprintf(listing,"Return\n");
          break;
        case BreakK:
          fprintf(listing,"Break\n");
          break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case BinOpK:
        case UnOpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          printType(tree);
          break;
        case BoolConstK:
          fprintf(listing,"Const: %d",tree->attr.boolVal);
          printType(tree);
          break;
        case RealConstK:
          fprintf(listing,"Const: %f",tree->attr.realVal);
          printType(tree);
          break;
        case StringConstK:
          fprintf(listing,"Const: %s",tree->attr.name);
          printType(tree);
          break;
        case VarLenK:
          fprintf(listing,"...\n");
          break;
        case PreK:
          fprintf(listing,"Prefixexp");
          printType(tree);
          break;
        case TabK:
          fprintf(listing,"Tableconstructor");
          printType(tree);
          break;
        case IdK:
          fprintf(listing,"Name: %s",tree->attr.name);
          printType(tree);
          break;
        case VarK:
          fprintf(listing,"Var");
          printType(tree);
          break;
        case FunBodyK:
          fprintf(listing,"Funcbody\n");
          break;
        case FieldK:
          fprintf(listing,"Field");
          printType(tree);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTypeTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

void printCFGList(CFGList* list)
{
    CFGList* currList = NULL;

    if (!list)
    {
        printf("\n");
        return; // Error
    }

    currList = list;

    fflush(stdout);

    fprintf(listing, "{");

    while (currList)
    {

        if (currList->value && currList->value->basicBlock)
        {
            fprintf(listing, "%s", currList->value->basicBlock->name);
            if (currList->next) fprintf(listing, ", ");
        }

        currList = currList->next;
    }

    fprintf(listing, "}\n");
}

void printCFGNode(CFGNode* node)
{
    CFGList* currPred = NULL;
    if (!node) return;

    fprintf(listing, "\tBasic Block: \n");
    
    fprintf(listing, "\t\t - Name: ");
    if (node->basicBlock) fprintf(listing, "%s", node->basicBlock->name);
    fprintf(listing, "\n");

    fprintf(listing, "\t\t - Successor%s", node->sndSuccNode ? "(true): " : ": ");
    if (node->fstSuccNode && node->fstSuccNode->basicBlock) fprintf(listing, "%s", node->fstSuccNode->basicBlock->name);
    fprintf(listing, "\n");

    if (node->sndSuccNode)
    {
        fprintf(listing, "\t\t - Successor(false): ");
        if (node->sndSuccNode->basicBlock) fprintf(listing, "%s", node->sndSuccNode->basicBlock->name);
        fprintf(listing, "\n");
    }

    fprintf(listing, "\t\t - Predecessors: ");

    printCFGList(node->preds);


    fprintf(listing, "\t\t - Dom Set: ");

    printCFGList(node->DOMSet);

    fprintf(listing, "\t\t - Post Dom Set: ");

    printCFGList(node->PostDOMSet);


}


void printCFGEdgeList(CFGEdgeList* list)
{
    CFGEdgeList* currList = NULL;

    if (!list)
    {
        printf("{}\n");
        return; // Error
    }

    currList = list;

    fflush(stdout);

    fprintf(listing, "{");

    while (currList)
    {

        if (currList->value->source &&
            currList->value->target &&
            currList->value->source->basicBlock &&
            currList->value->target->basicBlock)
        {
            fprintf(listing, "%s->", currList->value->source->basicBlock->name);
            fprintf(listing, "%s", currList->value->target->basicBlock->name);
            if (currList->next) fprintf(listing, ", ");
        }

        currList = currList->next;
    }

    fprintf(listing, "}\n");
}



void printCFG(CFG* cfg)
{
    CFG* currCFGVertex = NULL;

    if (!cfg) return;


    reverseCFGNodeList(&cfg);

    currCFGVertex = cfg;

    if (currCFGVertex->func) fprintf(listing, "CFG For Function: %s\n", currCFGVertex->func->name);

    while (currCFGVertex)
    {
        printCFGNode(currCFGVertex->node);
        currCFGVertex = currCFGVertex->next;
    }
    fprintf(listing, "\n");

    fprintf(listing, "Backedges: ");

    printCFGEdgeList(cfg->backedges);

    fprintf(listing, "\n");

    reverseCFGNodeList(&cfg);
}

void printDFG(BLOCK *blk)
{ DFGNode *dfgNode = blk->dfg;
  InstructionPointer *used;
  int flag = FALSE;
  while(dfgNode)
  { printf("\t\tRegister: %s\n",dfgNode->regName);
    printf("\t\t\tDefined: %p\n",dfgNode->def->inst);
	flag = FALSE;
	used = dfgNode->use;
	printf("\t\t\tUsed:");
	while(used)
	{ printf("  %p",used->inst);
	  flag = TRUE;
	  used = used->next;
	}
	if(flag == FALSE)
	  printf(" None\n");
	printf("\n");
	dfgNode = dfgNode->next;
	flag = FALSE;
  }
}
