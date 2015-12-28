/****************************************************/
/* File: lua.yv                                     */
/* The LUA Yacc/Bison specification file            */
/* Haicheng                                         */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYDEBUG 1
#define YYSTYPE TreeNode *

static int yylex(void);
static int fornum_index;
static TreeNode * savedTree; /* stores syntax tree for later return */
static TreeNode * fornum_statTmpNode[MAXTOKENLEN / 10];
static TreeNode * namelistTmpNode;
static TreeNode * fieldTmpNode;
static TreeNode * functioncallTmpNode;
static TreeNode * locfun_statTmpNode;
int funNum = 0;
%}
%token AND BREAK DO ELSE ELSEIF
%token END False FOR FUNCTION IF
%token IN LOCAL NIL NOT OR
%token REPEAT RETURN THEN True UNTIL WHILE

%token NAME NUMBER STRING

%token PLUS MINUS TIMES OVER MOD POW POUND
%token EQ NEQ LE GE LT GT ASSIGN
%token LPAREN RPAREN LCBRACK RCBRACK LSBRACK RSBRACK
%token SEMI COLON COMMA DOT DDOT TDOT

%token ERROR 

%left OR
%left AND
%left LT GT LE GE NEQ EQ
%right DDOT
%left PLUS MINUS
%left TIMES OVER MOD
%nonassoc NOT POUND
%right POW


%% /* Grammar for LUA */

chunk       : 
                 { $$ = NULL;
                 savedTree = NULL;}
            | stat_seq laststatemnt
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $2;
                     $$ = $1; 
                     $$->siblingNum = $1->siblingNum + 1;}
                     else $$ = $2;
                   savedTree = $$;
                 }
            | stat_seq 
                 { $$ = $1;
                   savedTree= $1;
                 }
            | laststatemnt
                 { $$ = $1;
                   savedTree= $1;
                 }
              
            ;
block       : chunk
                 { $$ = $1;}
            ;
stat_seq    : stat_seq statement
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $2;
                     $$ = $1; 
                     $$->siblingNum++;}
                     else $$ = $2;
                 }
            | statement  { $$ = $1; }
            ;
statement   :stat SEMI
                 { $$ = $1;}
            |stat { $$ = $1; }
            ;
stat        : var_stat { $$ = $1; }
            | functioncall { $$ =  $1; }
            | do_stat { $$ = $1; }
            | while_stat { $$ = $1; }
            | repeat_stat { $$ = $1; }
            | if_stat { $$ = $1; }
            | fornum_stat { $$ = $1; }
            | fun_stat { $$ = $1; }
            | locfun_stat { $$ = $1; }
            | name_stat  { $$ = $1; }
            | error  { $$ = NULL; }
            ;
var_stat    : varlist ASSIGN explist
                 { $$ = newStmtNode(AssignK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                 }
            ;
do_stat     : DO block END
                 { $$ = newStmtNode(DoK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                 }
            ;
while_stat  : WHILE exp DO block END
                 { $$ = newStmtNode(WhileK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }
            ;
repeat_stat : REPEAT block UNTIL exp
                 { $$ = newStmtNode(RepeatK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }
            ;
if_stat     : IF exp THEN block END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }
            | IF exp THEN block ELSE block END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->sibling = newStmtNode(ElseK);
                   $$->childNum = 2;
                   $$->siblingNum = 1;
                   $$->sibling->child[0] = $6;
                   $$->sibling->childNum = 1;
                 }
            | IF exp THEN block elseif_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->sibling = $5;
                   $$->childNum = 2;
                   $$->siblingNum = $5->siblingNum + 1;
                 }
            | IF exp THEN block elseif_seq ELSE block END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->sibling = $5;
                   $$->childNum = 2;
                   $$->siblingNum = $5->siblingNum + 2;

                   YYSTYPE t = $5;
                   while (t->sibling != NULL)
                     t = t->sibling;
                   t->sibling = newStmtNode(ElseK);
                   t->sibling->child[0] = $7;
                   t->sibling->childNum = 1;
                 }
            ;
elseif_seq  : elseif_seq ELSEIF exp THEN block
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = newStmtNode(ElseIfK);
                     t->sibling->child[0] = $3;
                     t->sibling->child[1] = $5;
                     t->sibling->childNum = 2;
                     $$ = $1; 
                     $$->siblingNum ++;}
                   else 
                   {
                     $$ = newStmtNode(ElseIfK);
                     $$->child[0] = $3;
                     $$->child[1] = $5;
                     $$->childNum = 2;
                   }
                 }
            | ELSEIF exp THEN block
                 { $$ = newStmtNode(ElseIfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }  
            ;
fornum_head : FOR NAME ASSIGN
                 { $$ = newExpNode(IdK);
                   $$->attr.name = copyString(nameTokenString);
                 }
            ;
fornum_stat : fornum_head exp COMMA exp COMMA exp DO block END
                 { $$ = newStmtNode(ForNumK);
                   $$->child[0] = $1;
                   $$->child[1] = $2;
                   $$->child[2] = $4;
                   $$->child[3] = $6;
                   $$->child[4] = $8;
                   $$->childNum = 5;
                 }
            | fornum_head exp COMMA exp DO block END
                 { $$ = newStmtNode(ForNumK);
                   $$->child[0] = $1;
                   $$->child[1] = $2;
                   $$->child[2] = $4;
                   $$->child[3] = $6;
                   $$->childNum = 4;
                 }
            ;
fun_stat    : FUNCTION funcname funcbody
                 { $$ = newStmtNode(FunK);
                   $$->child[0] = $2;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   funNum++;
                 }
            ;
locfun_stat : LOCAL FUNCTION NAME 
                 { locfun_statTmpNode = newExpNode(IdK);
                   locfun_statTmpNode->attr.name = copyString(nameTokenString);
               }
              funcbody
                 { $$ = newStmtNode(LocFunK);
                   $$->child[0] = locfun_statTmpNode;
                   $$->child[1] = $5;
                   $$->childNum = 2;
                   funNum++;
                 }
            ;
name_stat : LOCAL namelist ASSIGN explist
                 { $$ = newStmtNode(LocAssignK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }
            | LOCAL namelist
                 { $$ = newStmtNode(LocAssignK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                 }
            ;
laststatemnt: laststat SEMI { $$ = $1;}
            | laststat { $$ = $1;}
            ;
laststat    : RETURN explist
                 { $$ = newStmtNode(ReturnK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                 }
            | RETURN
                 { $$ = newStmtNode(ReturnK);}
            | BREAK
                 { $$ = newStmtNode(BreakK);}
            ;
funcname    : NAME name_dot_seq
                 { $$ = newExpNode(IdK);
                   $$->attr.name = copyString(nameTokenString);
                   $$->sibling = $2;
                   $$->siblingNum = $2->siblingNum + 1;
                 }
            | NAME
                 { $$ = newExpNode(IdK);
                   $$->attr.name = copyString(nameTokenString);
                 }
            ;
name_dot_seq: name_dot_seq DOT NAME
                 { YYSTYPE t = $1;
                   $3 = newExpNode(IdK);
                   $3->attr.name = copyString(nameTokenString);
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; 
                     $$->sibling++;}
                   else 
                   {
                     $$ = $3;
                   }
                 }
            | DOT NAME
                 { $2 = newExpNode(IdK);
                 $2->attr.name = copyString(nameTokenString);
                   $$ = $2;
                 }  
            ;
varlist     : var var_seq
                 { $$ = $1;
                   $1->sibling = $2;
                   $$->siblingNum++;
                 }
            | var
                 { $$ = $1;}
            ;
var_seq     : var_seq COMMA var
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; 
                     $$->siblingNum++;}
                   else 
                   {
                     $$ = $3;
                   }
                 }
            | COMMA var
                 { $$ = $2;}  
            ;
var         : NAME
                 { $1 = newExpNode(IdK);
                   $1->attr.name = copyString(nameTokenString);
                   $$ = newExpNode(VarK);
                   $$->child[0] = $1;
                   $$->childNum = 1;
                 }
            | prefixexp LSBRACK exp RSBRACK
                 { $$ = newExpNode(VarK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                 }
            | prefixexp DOT NAME
                 { $3 = newExpNode(IdK);
                   $3->attr.name = copyString(nameTokenString);
                   $$ = newExpNode(VarK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                 }
            ;
namelist    : NAME 
                 { namelistTmpNode = newExpNode(IdK);
                   namelistTmpNode->attr.name = copyString(nameTokenString);}
              name_seq
                 { $$ = namelistTmpNode;
                   namelistTmpNode->sibling = $3;
                   $$->siblingNum = namelistTmpNode->siblingNum + 1;
                 }
            | NAME
                 { $$ = newExpNode(IdK);
                   $$->attr.name = copyString(nameTokenString);
                 }
            ;
name_seq    : name_seq COMMA NAME
                 { YYSTYPE t = $1;
                   $3 = newExpNode(IdK);
                   $3->attr.name = copyString(nameTokenString);
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; 
                     $$->siblingNum++;}
                   else 
                   {
                     $$ = $3;
                   }
                 }
            | COMMA NAME
                 { $2 = newExpNode(IdK);
                 $2->attr.name = copyString(nameTokenString);
                   $$ = $2;
                 }  
            ;
explist     : exp_seq exp
                 { YYSTYPE t = $1;
                   while (t->sibling != NULL)
                     t = t->sibling;
                   t->sibling = $2;
                   $$ = $1;
                   $$->siblingNum = $1->siblingNum + 1;
                 }
            | exp
                 { $$ =  $1;}
            ;
exp_seq     : exp_seq exp COMMA
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $2;
                     $$ = $1; 
                     $$->siblingNum = $1->siblingNum + 1;}
                   else 
                   {
                     $$ = $2;
                   }
                 }
            | exp COMMA
                 { $$ = $1; }            
            ; 
exp         : NIL 
                 { $$ = newExpNode(BoolConstK);
                   $$->attr.boolVal = Nil;
                 }
            | False
                 { $$ = newExpNode(BoolConstK);
                   $$->attr.boolVal = FALSE;
                 }
            | True 
                 { $$ = newExpNode(BoolConstK);
                   $$->attr.boolVal = TRUE;
                 }
            | NUMBER 
                 { $$ = newExpNode(RealConstK);
                   $$->attr.realVal = atof(tokenString);
                 }
            | STRING 
                 { $$ = newExpNode(StringConstK);
                   $$->attr.name = copyString(stringTokenString);
                 }
            | TDOT 
                 { $$ = newExpNode(VarLenK);}
            | prefixexp 
                 { $$ =  $1;}           
            | tableconstructor 
                 { $$ = $1;}           
            |  exp PLUS exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = PLUS;
                 }
            | exp MINUS exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = MINUS;
                 }
            | exp TIMES exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = TIMES;
                 }
            | exp OVER exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = OVER;
                 }
            | exp POW exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = POW;
                 }
            | exp MOD exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = MOD;
                 }
            | exp DDOT exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = DDOT;
                 }
            | exp LT exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = LT;
                 }
            | exp LE exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = LE;
                 }
            | exp GT exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = GT;
                 }
            | exp GE exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = GE;
                 }
            | exp EQ exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = EQ;
                 }
            | exp NEQ exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = NEQ;
                 }
            | exp AND exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = AND;
                 }
            | exp OR exp
                 { $$ = newExpNode(BinOpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->childNum = 2;
                   $$->attr.op = OR;
                 }
            | MINUS exp
                 { $$ = newExpNode(UnOpK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                   $$->attr.op = MINUS;
                 }
            | NOT exp
                 { $$ = newExpNode(UnOpK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                   $$->attr.op = NOT;
                 }
            | POUND exp
                 { $$ = newExpNode(UnOpK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                   $$->attr.op = POUND;
                 }
            | error { $$ = NULL; }
            ;
prefixexp   : var
                 { $$ = newExpNode(PreK);
                   $$->child[0] = $1;
                   $$->childNum = 1;
                 }
            | functioncall 
                 { $$ = newExpNode(PreK);
                   $$->child[0] = $1;
                   $$->childNum = 1;
                 }
            | LPAREN exp RPAREN
                 { $$ = newExpNode(PreK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                 }
            ;
functioncall: prefixexp args 
                 { $$ = newStmtNode(FunCallK);
                   $$->child[0] = $1;
                   $$->child[1] = $2;
                   $$->childNum = 2;
                 }
            ;
args        : LPAREN explist RPAREN 
                 { $$ = $2;}
            | LPAREN RPAREN 
                 { $$ = NULL;}
            | tableconstructor 
                 { $$ = $1;}
            | STRING
                 { $$ = newExpNode(StringConstK);
                 $$->attr.name = copyString(stringTokenString)}
            ; 
funcbody    : LPAREN parlist RPAREN block END
                 { $$ = newExpNode(FunBodyK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }
            | LPAREN RPAREN block END
                 { $$ = newExpNode(FunBodyK);
                   $$->child[0] = $3;
                   $$->childNum = 1;
                 }
            ;
parlist     : namelist COMMA TDOT 
                 { $3 = newExpNode(VarLenK);
                   YYSTYPE t = $1;
                   while (t->sibling != NULL)
                     t = t->sibling;
                   t->sibling = $3;
                   $$ = $1;
                   $$->siblingNum = $1->siblingNum + 1;
                 }
            | namelist
                 { $$ =  $1;}
            | TDOT
                 { $$ = newExpNode(VarLenK);}
            ;

tableconstructor : LCBRACK fieldlist RCBRACK
                 { $$ = newExpNode(TabK);
                   $$->child[0] = $2;
                   $$->childNum = 1;
                 }
                 | LCBRACK RCBRACK
                 { $$ = newExpNode(TabK);
                   $$->child[0] = NULL;
                 }
                 ;
fieldlist   : field field_seq fieldsep
                 { $$ = $1;
                   $1->sibling = $2;
                   $$->siblingNum = $2->siblingNum + 1;
                 }
            | field field_seq
                 { $$ = $1;
                   $1->sibling = $2;
                   $$->siblingNum = $2->siblingNum + 1;
                 }
            | field fieldsep
                 { $$ = $1;}
            | field
                 { $$ = $1;}
            ;
field_seq   : field_seq fieldsep field
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; 
                     $$->siblingNum++;}
                   else 
                   {
                     $$ = $3;
                   }
                 }
            | fieldsep field
                 { $$ = $2;}
            ;
field       : LSBRACK exp RSBRACK ASSIGN exp 
                 { $$ = newExpNode(FieldK);
                   $$->child[0] = $2;
                   $$->child[1] = $5;
                   $$->childNum = 2;
                 }
            | NAME 
                 { fieldTmpNode = newExpNode(IdK);
                   fieldTmpNode->attr.name = copyString(nameTokenString);
                 }
              ASSIGN exp 
                 { $$ = newExpNode(FieldK);
                   $$->child[0] = fieldTmpNode;
                   $$->child[1] = $4;
                   $$->childNum = 2;
                 }
            | exp
                 { $$ = newExpNode(FieldK);
                   $$->child[0] = $1;
                   $$->childNum = 1;
                 }
            ;
fieldsep    : COMMA 
            | SEMI
            ;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ /*extern int yydebug;*/
  fornum_index = 0;
  /*yydebug = 1;*/
  yyparse();
  return savedTree;
}
