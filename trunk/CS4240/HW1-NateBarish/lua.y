%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parsetree.h"
#include "yyvaltype.h"

#define YYSTYPE char *


extern treenode* topNode;

void yyerror(const char *str)
{	
	extern int linenum;
	fprintf(stderr,"Error: parse error at line %d\n", linenum);
}


%}

%token NAME NUMBER STRING AND BREAK DO ELSE ELSEIF END FALSE FOR FUNCTION IF IN LOCAL NIL NOT OR REPEAT RETURN THEN TRUE UNTIL WHILE SEMI EQUALS COMMA DOT OPEN_BRACK CLOSE_BRACK DOTDOT DOTDOTDOT OPEN_PAR CLOSE_PAR OPEN_SQUIG CLOSE_SQUIG COLON PLUS MINUS STAR FSLASH CARET PERCENT LESS LESS_EQUAL MORE MORE_EQUAL EQUAL_EQUAL SQUIG_EQUAL SHARP

%% 

top:
	chunk
	{
		topNode = (treenode*)$$;
	};

chunk:
	chunk_rep_stat chunk_opt_laststat
	{
		treenode* chunk = makeTreeNodeNonTerm("chunk");

		treenode* statementsNode = (treenode*)$1;	
		treenode* lastStatementNode = (treenode*)$2;	

		if (statementsNode != NULL)
		{
			addChildren(chunk, statementsNode);	
			deleteTreeNode(statementsNode);
		}

		if (lastStatementNode != NULL)
		{
			addChild(chunk, lastStatementNode);	
		}
		
		$$ = (void*)chunk;

		//printf("chunk -> chunk_rep_stat chunk_opt_laststat\n");
	};

chunk_rep_stat:
	stat chunk_opt_semi chunk_rep_stat
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* statementNode = (treenode*)$1;	
		treenode* restStatementsNode = (treenode*)$3;	

		addChild(retNode, statementNode);
		
		if (restStatementsNode != NULL)
		{
			addChildren(retNode, restStatementsNode);	
			deleteTreeNode(restStatementsNode);
		}

		$$ = (void*)retNode;
	
		//printf("chunk_rep_stat -> stat chunk_opt_semi chunk_rep_stat\n");
	};

chunk_rep_stat:
	/* empty */
	{
		$$ = (void*)NULL;
		//printf("chunk_rep_stat -> /* empty */\n");
	};

chunk_opt_laststat:
	laststat chunk_opt_semi
	{
		$$ = (void*)(treenode*)$1;
		//printf("chunk_opt_laststat -> laststat chunk_opt_semi\n");
	};

chunk_opt_laststat:
	/* empty */
	{
		$$ = (void*)NULL;	
		//printf("chunk_opt_laststat -> /* empty */\n");
	};

chunk_opt_semi:
	SEMI
	{
		$$ = (void*)NULL; //dont care about semi in ABS
		//printf("chunk_opt_semi -> SEMI\n");
	};

chunk_opt_semi:
	/* empty */
	{
		$$ = (void*)NULL;
		//printf("chunk_opt_semi -> /* empty */\n");
	};

block:
	chunk
	{
		treenode* block = makeTreeNodeNonTerm("block");
		treenode* chunkNode = (treenode*)$1;	
		addChild(block, chunkNode);
		$$ = (void*)block;
		//printf("block -> chunk\n");
	};

stat:
	varlist EQUALS explist
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* varListNode = (treenode*)$1;	
		treenode* equalsNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* expListNode = (treenode*)$3;	
		addChild(stat, varListNode);
		addChild(stat, equalsNode);
		addChild(stat, expListNode);
		$$ = (void*)stat;
		//printf("stat -> varlist EQUALS explist\n");
	};

stat:
	functioncall
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* functioncallNode = (treenode*)$1;	
		addChild(stat, functioncallNode);
		$$ = (void*)stat;
		//printf("stat -> functioncall\n");
	};

stat:
	DO block END
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* doNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* blockNode = (treenode*)$2;
		treenode* endNode = makeTreeNodeTerm((yyvalType*)$3);
		addChild(stat, doNode);
		addChild(stat, blockNode);
		addChild(stat, endNode);
		$$ = (void*)stat;
		//printf("stat -> DO block END\n");
	};

stat:
	WHILE exp DO block END
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* whileNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expNode = (treenode*)$2;
		treenode* doNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* blockNode = (treenode*)$4;
		treenode* endNode = makeTreeNodeTerm((yyvalType*)$5);
	
		addChild(stat, whileNode);
		addChild(stat, expNode);
		addChild(stat, doNode);
		addChild(stat, blockNode);
		addChild(stat, endNode);
		$$ = (void*)stat;
		//printf("stat -> WHILE exp DO block END\n");
	};

stat:
	REPEAT block UNTIL exp
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* repeatNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* blockNode = (treenode*)$2;
		treenode* untilNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* expNode = (treenode*)$4;
	
		addChild(stat, repeatNode);
		addChild(stat, blockNode);
		addChild(stat, untilNode);
		addChild(stat, expNode);
		$$ = (void*)stat;
		//printf("stat -> REPEAT block UNTIL exp\n");
	};

stat:
	IF exp THEN block stat_rep_elseif stat_opt_else END
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* ifNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expNode = (treenode*)$2;
		treenode* thenNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* blockNode = (treenode*)$4;
		treenode* elseifsNode = (treenode*)$5;
		treenode* elseNode = (treenode*)$6;
		treenode* endNode = makeTreeNodeTerm((yyvalType*)$7);
	
		addChild(stat, ifNode);
		addChild(stat, expNode);
		addChild(stat, thenNode);
		addChild(stat, blockNode);		
		if (elseifsNode != NULL)
		{
			addChildren(stat, elseifsNode);	
			deleteTreeNode(elseifsNode);
		}
		if (elseNode != NULL)
		{
			addChildren(stat, elseNode);	
			deleteTreeNode(elseNode);
		}
		addChild(stat, endNode);

		$$ = (void*)stat;
		//printf("stat -> IF exp THEN block stat_rep_elseif stat_opt_else END\n");
	};

stat_rep_elseif:
	ELSEIF exp THEN block stat_rep_elseif
	{

		treenode* retNode = makeTreeNodeNonTerm("TEMP");

		treenode* elseifNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expNode = (treenode*)$2;	
		treenode* thenNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* blockNode = (treenode*)$4;

		treenode* restElseifsNode = (treenode*)$5;	

		addChild(retNode, elseifNode);
		addChild(retNode, expNode);
		addChild(retNode, thenNode);
		addChild(retNode, blockNode);
		
		if (restElseifsNode != NULL)
		{
			addChildren(retNode, restElseifsNode);	
			deleteTreeNode(restElseifsNode);
		}

		$$ = (void*)retNode;
		
		//printf("stat_rep_elseif -> ELSEIF exp THEN block stat_rep_elseif\n");
	};

stat_rep_elseif:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("stat_rep_elseif -> /*empty*/\n");
	};

stat_opt_else:
	ELSE block
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* elseNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* blockNode = (treenode*)$2;

		addChild(retNode, elseNode);
		addChild(retNode, blockNode);	

		$$ = (void*)retNode;
		//printf("stat_opt_else -> ELSE block\n");
	};

stat_opt_else:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("stat_opt_else -> /*empty*/\n");
	};

stat:
	FOR NAME EQUALS exp COMMA exp stat_opt_exp DO block END
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* ifNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* equalsNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* expNode1 = (treenode*)$4;
		treenode* commaNode = makeTreeNodeTerm((yyvalType*)$5);
		treenode* expNode2 = (treenode*)$6;
		treenode* expNode3 = (treenode*)$7;
		treenode* doNode = makeTreeNodeTerm((yyvalType*)$8);
		treenode* blockNode = (treenode*)$9;
		treenode* endNode = makeTreeNodeTerm((yyvalType*)$10);

	
		addChild(stat, ifNode);
		addChild(stat, nameNode);
		addChild(stat, equalsNode);
		addChild(stat, expNode1);		
		addChild(stat, commaNode);		
		addChild(stat, expNode2);		
		if (expNode3 != NULL)
		{
			addChildren(stat, expNode3);	
			deleteTreeNode(expNode3);
		}
		addChild(stat, doNode);
		addChild(stat, blockNode);
		addChild(stat, endNode);

		$$ = (void*)stat;

		//printf("stat -> FOR NAME EQUALS exp COMMA exp stat_opt_exp DO block END\n");
	};

stat_opt_exp:
	COMMA exp
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* commaNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expNode = (treenode*)$2;

		addChild(retNode, commaNode);
		addChild(retNode, expNode);	

		$$ = (void*)retNode;
		//printf("stat_opt_exp -> COMMA exp\n");
	};

stat_opt_exp:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("stat_opt_exp -> /*empty*/\n");
	};

stat:
	FOR namelist IN explist DO block END
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* forNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* namelistNode = (treenode*)$2;
		treenode* inNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* explistNode = (treenode*)$4;
		treenode* doNode = makeTreeNodeTerm((yyvalType*)$5);
		treenode* blockNode = (treenode*)$6;
		treenode* endNode = makeTreeNodeTerm((yyvalType*)$7);

	
		addChild(stat, forNode);
		addChild(stat, namelistNode);
		addChild(stat, inNode);
		addChild(stat, explistNode);		
		addChild(stat, doNode);		
		addChild(stat, blockNode);
		addChild(stat, endNode);

		$$ = (void*)stat;
		//printf("stat -> FOR namelist IN explist DO block END\n");
	};

stat:
	FUNCTION funcname funcbody
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* functionNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* funcnameNode = (treenode*)$2;
		treenode* funcbodyNode = (treenode*)$3;

	
		addChild(stat, functionNode);
		addChild(stat, funcnameNode);
		addChild(stat, funcbodyNode);

		$$ = (void*)stat;
		//printf("stat -> FUNCTION funcname funcbody\n");
	};

stat:
	LOCAL FUNCTION NAME funcbody
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* localNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* functionNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* funcbodyNode = (treenode*)$4;


		addChild(stat, localNode);	
		addChild(stat, functionNode);
		addChild(stat, nameNode);
		addChild(stat, funcbodyNode);

		$$ = (void*)stat;
		//printf("stat -> LOCAL FUNCTION NAME funcbody\n");
	};

stat:
	LOCAL namelist stat_opt_explist
	{
		treenode* stat = makeTreeNodeNonTerm("stat");
		treenode* localNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* namelistNode = (treenode*)$2;
		treenode* explistNode = (treenode*)$3;

		addChild(stat, localNode);	
		addChild(stat, namelistNode);
		if (explistNode != NULL)
		{
			addChildren(stat, explistNode);	
			deleteTreeNode(explistNode);
		}
		$$ = (void*)stat;
		//printf("stat -> LOCAL namelist stat_opt_explist\n");
	};

stat_opt_explist:
	EQUALS explist 
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* equalsNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* explistNode = (treenode*)$2;

		addChild(retNode, equalsNode);
		addChild(retNode, explistNode);	

		$$ = (void*)retNode;
		//printf("stat_opt_explist -> EQUALS explist \n");
	};

stat_opt_explist:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("stat_opt_explist -> /*empty*/\n");
	};

laststat:
	RETURN laststat_opt_explist
	{
		treenode* laststat = makeTreeNodeNonTerm("laststat");
		treenode* returnNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* laststatExplistNode = (treenode*)$2;


		addChild(laststat, returnNode);	
		if (laststatExplistNode != NULL)
		{
			addChild(laststat, laststatExplistNode);	
		}
		$$ = (void*)laststat;
		//printf("laststat -> RETURN laststat_opt_explist\n");
	};

laststat_opt_explist:
	explist
	{
		$$ = (void*)(treenode*)$1;
		//printf("laststat_opt_explist -> explist\n");
	};

laststat_opt_explist:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("laststat_opt_explist -> /*empty*/\n");
	};

laststat:
	BREAK
	{
		treenode* laststat = makeTreeNodeNonTerm("laststat");
		treenode* breakNode = makeTreeNodeTerm((yyvalType*)$1);
		addChild(laststat, breakNode);			
		$$ = (void*)laststat;
		//printf("laststat -> BREAK\n");
	};

funcname:
	NAME funcname_rep_name funcname_opt_name
	{
		treenode* funcname = makeTreeNodeNonTerm("funcname");

		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* funcnamerepnameNode = (treenode*)$2;
		treenode* funcnameoptnameNode = (treenode*)$3;

		addChild(funcname, nameNode);			
		if (funcnamerepnameNode != NULL)
		{
			addChildren(funcname, funcnamerepnameNode);	
			deleteTreeNode(funcnamerepnameNode);			
		}
		if (funcnameoptnameNode != NULL)
		{
			addChildren(funcname, funcnameoptnameNode);	
			deleteTreeNode(funcnameoptnameNode);			
		}

		$$ = (void*)funcname;
		//printf("funcname -> NAME funcname_rep_name funcname_opt_name\n");
	};

funcname_rep_name:
	DOT NAME funcname_rep_name
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* dotNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* moreNode = (treenode*)$3;


		addChild(retNode, dotNode);
		addChild(retNode, nameNode);
		if (moreNode != NULL)
		{
			addChildren(retNode, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)retNode;
		//printf("funcname_rep_name -> DOT NAME funcname_rep_name\n");
	};

funcname_rep_name:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("funcname_rep_name -> /*empty*/\n");
	};

funcname_opt_name:
	COLON NAME
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* colonNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$2);

		addChild(retNode, colonNode);
		addChild(retNode, nameNode);	

		$$ = (void*)retNode;
		//printf("funcname_opt_name -> COLON NAME\n");
	};

funcname_opt_name:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("funcname_opt_name -> /*empty*/\n");
	};

varlist:
	var varlist_rep_var
	{
		treenode* varlist = makeTreeNodeNonTerm("varlist");
		treenode* varNode = (treenode*)$1;
		treenode* moreNode = (treenode*)$2;
		
		addChild(varlist, varNode);
		if (moreNode != NULL)
		{
			addChildren(varlist, moreNode);	
			deleteTreeNode(moreNode);			
		}

		$$ = (void*)varlist;

		//printf("varlist -> var varlist_rep_var\n");
	};

varlist_rep_var:
	COMMA var varlist_rep_var
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* commaNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* varNode = (treenode*)$2;
		treenode* moreNode = (treenode*)$3;


		addChild(retNode, commaNode);
		addChild(retNode, varNode);
		if (moreNode != NULL)
		{
			addChildren(retNode, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)retNode;
		//printf("varlist_rep_var -> COMMA var varlist_rep_var\n");
	};

varlist_rep_var:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("varlist_rep_var -> /*empty*/\n");
	};

var:
	 NAME 
	{
		treenode* var = makeTreeNodeNonTerm("var");
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$1);
		addChild(var, nameNode);
		$$ = (void*)var;
		//printf("var -> NAME \n");
	};

var:
	prefixexp OPEN_BRACK exp CLOSE_BRACK 
	{
		treenode* var = makeTreeNodeNonTerm("var");
		treenode* prefixexpNode = (treenode*)$1;
		treenode* openNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* expNode = (treenode*)$3;
		treenode* closeNode = makeTreeNodeTerm((yyvalType*)$4);
		addChild(var, prefixexpNode);
		addChild(var, openNode);
		addChild(var, expNode);
		addChild(var, closeNode);
		$$ = (void*)var;
		//printf("var -> prefixexp OPEN_BRACK exp CLOSE_BRACK \n");
	};

var:
	prefixexp DOT NAME
	{
		treenode* var = makeTreeNodeNonTerm("var");
		treenode* prefixexpNode = (treenode*)$1;
		treenode* dotNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$3);
		addChild(var, prefixexpNode);
		addChild(var, dotNode);
		addChild(var, nameNode);
		$$ = (void*)var;
		//printf("var -> prefixexp DOT NAME\n");
	};

namelist:
	NAME namelist_rep_name
	{
		treenode* namelist = makeTreeNodeNonTerm("namelist");
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* moreNode = (treenode*)$2;

		addChild(namelist, nameNode);
		if (moreNode != NULL)
		{
			addChildren(namelist, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)namelist;
		//printf("namelist -> NAME namelist_rep_name\n");
	};

namelist_rep_name:
	COMMA NAME namelist_rep_name
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* commaNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* moreNode = (treenode*)$3;


		addChild(retNode, commaNode);
		addChild(retNode, nameNode);
		if (moreNode != NULL)
		{
			addChildren(retNode, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)retNode;

		//printf("namelist_rep_name -> COMMA NAME namelist_rep_name\n");
	};

namelist_rep_name:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("namelist_rep_name -> /*empty*/\n");
	};

explist:
	exp explist_rep_exp 
	{
		treenode* explist = makeTreeNodeNonTerm("explist");
		treenode* expNode = (treenode*)$1;
		treenode* moreNode = (treenode*)$2;

		addChild(explist, expNode);
		if (moreNode != NULL)
		{
			addChildren(explist, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)explist;
		//printf("explist -> exp explist_rep_exp \n");
	};

explist_rep_exp:
	COMMA exp explist_rep_exp
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* commaNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expNode = (treenode*)$2;
		treenode* moreNode = (treenode*)$3;


		addChild(retNode, commaNode);
		addChild(retNode, expNode);
		if (moreNode != NULL)
		{
			addChildren(retNode, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)retNode;

		//printf("explist_rep_exp -> COMMA exp explist_rep_exp\n");
	};

explist_rep_exp:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("explist_rep_exp -> /*empty*/\n");
	};

exp:
	NIL 
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = makeTreeNodeTerm((yyvalType*)$1);
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> NIL \n");
	};

exp:
	FALSE
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = makeTreeNodeTerm((yyvalType*)$1);
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> FALSE\n");
	};

exp:
	TRUE
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = makeTreeNodeTerm((yyvalType*)$1);
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> TRUE\n");
	};

exp:
	NUMBER 
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = makeTreeNodeTerm((yyvalType*)$1);
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> NUMBER \n");
	};

exp:
	STRING 
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = makeTreeNodeTerm((yyvalType*)$1);
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> STRING \n");
	};

exp:
	DOTDOTDOT 
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = makeTreeNodeTerm((yyvalType*)$1);
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> DOTDOTDOT \n");
	};

exp:
	function
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = (treenode*)$1;
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> function\n");
	};

exp:
	prefixexp 
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = (treenode*)$1;
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> prefixexp \n");
	};

exp:
	tableconstructor 
	{
		treenode* exp = makeTreeNodeNonTerm("exp");
		treenode* node = (treenode*)$1;
		addChild(exp, node);
		$$ = (void*)exp;
		//printf("exp -> tableconstructor \n");
	};

exp:
	exp binop exp 
	{
		treenode* exp = makeTreeNodeNonTerm("binop");
		treenode* exp1Node = (treenode*)$1;
		treenode* binopNode = (treenode*)$2;
		treenode* exp2Node = (treenode*)$3;
		addChild(exp, exp1Node);
		addChild(exp, binopNode);
		addChild(exp, exp2Node);
		$$ = (void*)exp;
		//printf("exp -> exp binop exp \n");
	};

exp:
	unop exp 
	{
		treenode* exp = makeTreeNodeNonTerm("unop");
		treenode* unopNode = (treenode*)$1;
		treenode* exp1Node = (treenode*)$2;
		addChild(exp, unopNode);
		addChild(exp, exp1Node);
		$$ = (void*)exp;
		//printf("exp -> unop exp \n");
	};

prefixexp:
	var 
	{
		treenode* prefixexp = makeTreeNodeNonTerm("prefixexp");
		treenode* node = (treenode*)$1;
		addChild(prefixexp, node);
		$$ = (void*)prefixexp;
		//printf("prefixexp -> var \n");
	};

prefixexp:
	functioncall 
	{
		treenode* prefixexp = makeTreeNodeNonTerm("prefixexp");
		treenode* node = (treenode*)$1;
		addChild(prefixexp, node);
		$$ = (void*)prefixexp;
		//printf("prefixexp -> functioncall \n");
	};

prefixexp:
	OPEN_PAR exp CLOSE_PAR
	{
		treenode* prefixexp = makeTreeNodeNonTerm("prefixexp");
		treenode* opNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expNode = (treenode*)$2;
		treenode* cpNode = makeTreeNodeTerm((yyvalType*)$3);
		addChild(prefixexp, opNode);
		addChild(prefixexp, expNode);
		addChild(prefixexp, cpNode);
		$$ = (void*)prefixexp;
		//printf("prefixexp -> OPEN_PAR exp CLOSE_PAR\n");
	};

functioncall:
	prefixexp args 
	{
		treenode* functioncall = makeTreeNodeNonTerm("functioncall");
		treenode* prefixexpNode = (treenode*)$1;
		treenode* argsNode = (treenode*)$2;
		addChild(functioncall, prefixexpNode);
		addChild(functioncall, argsNode);
		$$ = (void*)functioncall;
		//printf("functioncall -> prefixexp args \n");
	};

functioncall:
	prefixexp COLON NAME args 
	{
		treenode* functioncall = makeTreeNodeNonTerm("functioncall");
		treenode* prefixexpNode = (treenode*)$1;
		treenode* colonNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* argsNode = (treenode*)$4;

		addChild(functioncall, prefixexpNode);
		addChild(functioncall, colonNode);
		addChild(functioncall, nameNode);
		addChild(functioncall, argsNode);
		$$ = (void*)functioncall;
		//printf("functioncall -> prefixexp COLON NAME args \n");
	};

args:
	OPEN_PAR args_opt_explist CLOSE_PAR 
	{
		treenode* args = makeTreeNodeNonTerm("args");
		treenode* opNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* expListNode = (treenode*)$2;
		treenode* cpNode = makeTreeNodeTerm((yyvalType*)$3);

		addChild(args, opNode);
		if (expListNode != NULL)
		{
			addChild(args, expListNode);
		}
		addChild(args, cpNode);
		$$ = (void*)args;
		//printf("args -> OPEN_PAR args_opt_explist CLOSE_PAR \n");
	};

args_opt_explist:
	explist 
	{
		$$ = (void*)(treenode*)$1;
		//printf("args_opt_explist -> explist \n");
	};

args_opt_explist:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("args_opt_explist -> /*empty*/\n");
	};

args:
	tableconstructor 
	{
		treenode* args = makeTreeNodeNonTerm("args");
		treenode* tableconstructorNode = (treenode*)$1;
		addChild(args, tableconstructorNode);
		$$ = (void*)args;
		//printf("args -> tableconstructor \n");
	};

args:
	STRING 
	{
		treenode* args = makeTreeNodeNonTerm("args");
		treenode* stringNode = makeTreeNodeTerm((yyvalType*)$1);
		addChild(args, stringNode);
		$$ = (void*)args;
		//printf("args -> STRING \n");
	};

function:
	FUNCTION funcbody
	{
		treenode* function = makeTreeNodeNonTerm("function");
		treenode* functionNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* funcbodyNode = (treenode*)$2;
		addChild(function, functionNode);
		addChild(function, funcbodyNode);
		$$ = (void*)function;
		//printf("function -> FUNCTION funcbody\n");
	};

funcbody:
	OPEN_PAR funcbody_opt_parlist CLOSE_PAR block END
	{
		treenode* funcbody = makeTreeNodeNonTerm("funcbody");
		treenode* opNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* parlistNode = (treenode*)$2;
		treenode* cpNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* blockNode = (treenode*)$4;
		treenode* endNode = makeTreeNodeTerm((yyvalType*)$5);

		addChild(funcbody, opNode);
		if (parlistNode != NULL)
		{
			addChild(funcbody, parlistNode);
		}
		addChild(funcbody, cpNode);
		addChild(funcbody, blockNode);
		addChild(funcbody, endNode);
		$$ = (void*)funcbody;
		//printf("funcbody -> OPEN_PAR funcbody_opt_parlist CLOSE_PAR block END\n");
	};

funcbody_opt_parlist:
	parlist
	{
		$$ = (void*)(treenode*)$1;
		//printf("funcbody_opt_parlist -> parlist\n");
	};

funcbody_opt_parlist:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("funcbody_opt_parlist -> /*empty*/\n");
	};

parlist:
	namelist parlist_opt_dots
	{
		treenode* parlist = makeTreeNodeNonTerm("parlist");
		treenode* namelistNode = (treenode*)$1;
		treenode* dotsNode = (treenode*)$2;

		addChild(parlist, namelistNode);
		if (dotsNode != NULL)
		{
			addChildren(parlist, dotsNode);
			deleteTreeNode(dotsNode);
		}
		$$ = (void*)parlist;
		//printf("parlist -> namelist parlist_opt_dots\n");
	};

parlist_opt_dots:
	COMMA DOTDOTDOT
	{
		treenode* temp = makeTreeNodeNonTerm("TEMP");
		treenode* commaNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* dotsNode = makeTreeNodeTerm((yyvalType*)$2);
		addChild(temp, commaNode);
		addChild(temp, dotsNode);
		$$ = (void*)temp;
		//printf("parlist_opt_dots -> COMMA DOTDOTDOT\n");
	};

parlist_opt_dots:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("parlist_opt_dots -> /*empty*/\n");
	};

parlist:
	DOTDOTDOT
	{
		treenode* parlist = makeTreeNodeNonTerm("parlist");
		treenode* dotsNode = makeTreeNodeTerm((yyvalType*)$1);
		addChild(parlist, dotsNode);		
		$$ = (void*)parlist;
		//printf("parlist -> DOTDOTDOT\n");
	};

tableconstructor:
	OPEN_SQUIG tableconstructor_opt_fieldlist CLOSE_SQUIG
	{
		treenode* tableconstructor = makeTreeNodeNonTerm("tableconstructor");
		treenode* osquigNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* optNode = (treenode*)$2;
		treenode* csquigNode = makeTreeNodeTerm((yyvalType*)$3);
		addChild(tableconstructor, osquigNode);		
		if (optNode != NULL)
		{
			addChild(tableconstructor, optNode);	
		}
		addChild(tableconstructor, csquigNode);		
		$$ = (void*)tableconstructor;
		//printf("tableconstructor -> OPEN_SQUIG tableconstructor_opt_fieldlist CLOSE_SQUIG\n");
	};

tableconstructor_opt_fieldlist :
	fieldlist
	{
		$$ = (void*)(treenode*)$1;
		//printf("tableconstructor_opt_fieldlist  -> fieldlist\n");
	};

tableconstructor_opt_fieldlist :
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("tableconstructor_opt_fieldlist  -> /*empty*/\n");
	};

fieldlist:
	field fieldlist_rep_field
	{
		treenode* fieldlist = makeTreeNodeNonTerm("fieldlist");
		treenode* fieldNode = (treenode*)$1;
		treenode* repNode = (treenode*)$2;

		addChild(fieldlist, fieldNode);		
		if (repNode != NULL)
		{
			addChildren(fieldlist, repNode);	
			deleteTreeNode(repNode);
		}

		$$ = (void*)fieldlist;
		//printf("fieldlist -> field fieldlist_rep_field fieldlist_opt_fieldsep\n");
	};

fieldlist:
	field fieldsep fieldlist_rep_field2
	{
		treenode* fieldlist = makeTreeNodeNonTerm("fieldlist");
		treenode* fieldNode = (treenode*)$1;		
		treenode* optNode = (treenode*)$2;
		treenode* repNode = (treenode*)$3;

		addChild(fieldlist, fieldNode);						
		addChild(fieldlist, optNode);	
		if (repNode != NULL)
		{
			addChildren(fieldlist, repNode);	
			deleteTreeNode(repNode);
		}
		

		$$ = (void*)fieldlist;
		//printf("fieldlist -> field fieldlist_rep_field fieldlist_opt_fieldsep\n");
	};

fieldlist_rep_field:
	fieldsep field fieldlist_rep_field
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* fieldsepNode = (treenode*)$1;
		treenode* fieldNode = (treenode*)$2;
		treenode* moreNode = (treenode*)$3;


		addChild(retNode, fieldsepNode);
		addChild(retNode, fieldNode);
		if (moreNode != NULL)
		{
			addChildren(retNode, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)retNode;
		//printf("fieldlist_rep_field -> fieldsep field fieldlist_rep_field\n");
	};

fieldlist_rep_field:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("fieldlist_rep_field -> /*empty*/\n");
	};

fieldlist_rep_field2:
	field fieldsep fieldlist_rep_field2
	{
		treenode* retNode = makeTreeNodeNonTerm("TEMP");
		treenode* fieldNode = (treenode*)$1;
		treenode* fieldsepNode = (treenode*)$2;
		treenode* moreNode = (treenode*)$3;


		addChild(retNode, fieldNode);
		addChild(retNode, fieldsepNode);
		if (moreNode != NULL)
		{
			addChildren(retNode, moreNode);	
			deleteTreeNode(moreNode);			
		}	

		$$ = (void*)retNode;
		//printf("fieldlist_rep_field -> fieldsep field fieldlist_rep_field\n");
	};

fieldlist_rep_field2:
	/*empty*/
	{
		$$ = (void*)NULL;
		//printf("fieldlist_rep_field -> /*empty*/\n");
	};


field:
	OPEN_BRACK exp CLOSE_BRACK EQUALS exp 
	{
		treenode* field = makeTreeNodeNonTerm("field");
		treenode* obNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* exp1Node = (treenode*)$2;
		treenode* cbNode = makeTreeNodeTerm((yyvalType*)$3);
		treenode* eqNode = makeTreeNodeTerm((yyvalType*)$4);
		treenode* exp2Node = (treenode*)$5;

		addChild(field, obNode);
		addChild(field, exp1Node);		
		addChild(field, cbNode);		
		addChild(field, eqNode);		
		addChild(field, exp2Node);				
				
		$$ = (void*)field;
		//printf("field -> OPEN_BRACK exp CLOSE_BRACK EQUALS exp \n");
	};

field:
	NAME EQUALS exp 
	{
		treenode* field = makeTreeNodeNonTerm("field");
		treenode* nameNode = makeTreeNodeTerm((yyvalType*)$1);
		treenode* eqNode = makeTreeNodeTerm((yyvalType*)$2);
		treenode* expNode = (treenode*)$3;

		addChild(field, nameNode);
		addChild(field, eqNode);		
		addChild(field, expNode);				
				
		$$ = (void*)field;
		//printf("field -> NAME EQUALS exp \n");
	};

field:
	exp
	{
		treenode* field = makeTreeNodeNonTerm("field");
		treenode* expNode = (treenode*)$1;		
		addChild(field, expNode);								
		$$ = (void*)field;
		//printf("field -> exp\n");
	};

fieldsep:
	COMMA 
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("fieldsep -> COMMA \n");
	};

fieldsep:
	SEMI
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("fieldsep -> SEMI\n");
	};

binop:
	PLUS 
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> PLUS \n");
	};

binop:
	MINUS
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> MINUS\n");
	};

binop:
	STAR 
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> STAR \n");
	};

binop:
	FSLASH
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> FSLASH\n");
	};

binop:
	CARET
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> CARET\n");
	};

binop:
	PERCENT 
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> PERCENT \n");
	};

binop:
	DOTDOT
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> DOTDOT\n");
	};

binop:
	LESS
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> LESS\n");
	};

binop:
	LESS_EQUAL		
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> LESS_EQUAL\n");
	};

binop:
	MORE
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> MORE\n");
	};

binop:
	MORE_EQUAL
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> MORE_EQUAL\n");
	};

binop:
	EQUAL_EQUAL
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> EQUAL_EQUAL\n");
	};

binop:
	SQUIG_EQUAL
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> SQUIG_EQUAL\n");
	};

binop:
	AND
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> AND\n");
	};

binop:
	OR
	{
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("binop -> OR\n");
	};

unop:
	MINUS
	{	
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("unop -> MINUS\n");
	};

unop:
	NOT
	{	
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("unop -> NOT\n");
	};

unop:
	SHARP
	{	
		$$ = (void*)makeTreeNodeTerm((yyvalType*)$1);
		//printf("unop -> SHARP\n");
	};


