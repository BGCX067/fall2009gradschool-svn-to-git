%{



#define YYSTYPE void*

#include <stdlib.h>
#include <stdio.h>
#include "yyvaltype.h"

#include "name_node.h"
#include "number_node.h"
#include "string_node.h"

#include "base_node.h"
#include "chunk_node.h"
#include "expression_node.h"
#include "expression_node_binary_operation.h"
#include "expression_node_bool.h"
#include "expression_node_dots.h"
#include "expression_node_nil.h"
#include "expression_node_number.h"
#include "expression_node_prefix.h"
#include "expression_node_string.h"
#include "expression_node_table_constructor.h"
#include "expression_node_unary_operation.h"
#include "field_node.h"
#include "field_node_bracket.h"
#include "field_node_expression.h"
#include "field_node_name.h"
#include "function_body_node.h"
#include "function_call_node.h"
#include "prefix_node.h"
#include "prefix_node_function_call.h"
#include "prefix_node_parenthesis.h"
#include "prefix_node_variable.h"
#include "statement_node.h"
#include "statement_node_assign.h"
#include "statement_node_break.h"
#include "statement_node_do.h"
#include "statement_node_function_definition.h"
#include "statement_node_funtion_call.h"
#include "statement_node_generic_for.h"
#include "statement_node_if.h"
#include "statement_node_local_function_definition.h"
#include "statement_node_local_variable_declaration.h"
#include "statement_node_numeric_for.h"
#include "statement_node_repeate.h"
#include "statement_node_return.h"
#include "statement_node_while.h"
#include "variable_node.h"
#include "variable_node_name.h"
#include "variable_node_prefix_bracket.h"
#include "variable_node_prefix_dot.h"

extern "C"
{
	int yyparse(void);
	int yylex(void);	
	void yyerror(const char *str)
	{
		extern int linenum;
		fprintf(stderr, "Error: parse error at line %d\n", linenum);
		exit(1);
	}
	int yywrap()
	{
		return 1;
	}

	void* topnode;
}

class COptElseIfs
{
	public:
		ExpressionNodeList Expressions;
		ChunkNodeList Chunks;
};
typedef COptElseIfs* OptElseIfs;


class CParamsList
{
	public:
		NameNodeList Names;
		bool Dots;
};
typedef CParamsList* ParamsList;




%}

%token NAME NUMBER STRING CLASS EXTENDS VIRTUAL PUBLIC PROTECTED PRIVATE STATIC THIS AND BREAK DO ELSE ELSEIF END FALSE FOR FUNCTION IF IN LOCAL NIL NOT OR REPEAT RETURN THEN TRUE UNTIL WHILE SEMI EQUALS COMMA DOT OPEN_BRACK CLOSE_BRACK DOTDOT DOTDOTDOT OPEN_PAR CLOSE_PAR OPEN_SQUIG CLOSE_SQUIG COLON PLUS MINUS STAR FSLASH CARET PERCENT LESS LESS_EQUAL MORE MORE_EQUAL EQUAL_EQUAL SQUIG_EQUAL SHARP

/*
or
and
<     >     <=    >=    ~=    ==
..
+     -
*     /     %
not   #     - (unary)
^  

The concatenation ('..') and exponentiation ('^') operators are right associative. All other binary operators are left associative.
*/

%left OR
%left AND
%left LESS MORE LESS_EQUAL MORE_EQUAL SQUIG_EQUAL EQUAL_EQUAL
%right DOTDOT
%left PLUS MINUS
%left STAR FSLASH PERCENT
%left NOT SHARP 
%right CARET


%% 

top:
	chunk
	{
		topnode = $1;
	};

chunk:
	chunk_rep_stat chunk_opt_laststat
	{
		StatementNodeList statementNodes = (StatementNodeList)$1;			
		StatementNode lastStatementNode = (StatementNode)$2;
		if (lastStatementNode != NULL)
		{
			statementNodes->push_back(lastStatementNode);
		}
		
		$$ = (void*)new CChunkNode(statementNodes);
	};

chunk_rep_stat:
	stat chunk_opt_semi chunk_rep_stat
	{
		StatementNode statementNode = (StatementNode)$1;			
		StatementNodeList statementNodes = (StatementNodeList)$3;	
		statementNodes->push_front(statementNode);	
		$$ = (void*)statementNodes;
	};

chunk_rep_stat:
	/* empty */
	{
		$$ = (void*)new CStatementNodeList();
	};

chunk_opt_laststat:
	laststat chunk_opt_semi
	{
		$$ = (void*)$1;
	};

chunk_opt_laststat:
	/* empty */
	{
		$$ = (void*)NULL;	
	};

chunk_opt_semi:
	SEMI
	{
		$$ = (void*)NULL; //dont care about semi in ABS
	};

chunk_opt_semi:
	/* empty */
	{
		$$ = (void*)NULL;
	};

block:
	chunk
	{
		$$ = (void*)$1;	
	};

stat:
	varlist EQUALS explist
	{
		VariableNodeList vars = (VariableNodeList)$1;
		ExpressionNodeList exps = (ExpressionNodeList)$3;	
		$$ = (void*)new CStatementNodeAssign(vars, exps);
	};

stat:
	functioncall
	{
		FunctionCallNode functioncall = (FunctionCallNode)$1;	
		$$ = (void*)new CStatementNodeFuntionCall(functioncall);
	};

stat:
	DO block END
	{
		ChunkNode chunk = (ChunkNode)$2;	
		$$ = (void*)new CStatementNodeDo(chunk);
	};

stat:
	WHILE exp DO block END
	{
		ExpressionNode expression = (ExpressionNode)$2;
		ChunkNode chunk = (ChunkNode)$4;
		$$ = (void*)new CStatementNodeWhile(expression, chunk);
	};

stat:
	REPEAT block UNTIL exp
	{
		ChunkNode chunk = (ChunkNode)$2;
		ExpressionNode expression = (ExpressionNode)$4;
		$$ = (void*)new CStatementNodeRepeate(chunk, expression);
	};

stat:
	IF exp THEN block stat_rep_elseif stat_opt_else END
	{
		ExpressionNode ifExpression = (ExpressionNode)$2;
		ChunkNode ifChunk = (ChunkNode)$4;

		OptElseIfs optElseIfs = (OptElseIfs)$5;
		optElseIfs->Expressions->push_front(ifExpression);
		optElseIfs->Chunks->push_front(ifChunk);

		ChunkNode elseChunk = (ChunkNode)$6;		
		if (elseChunk != NULL)
		{
			optElseIfs->Chunks->push_back(elseChunk);
		}

		$$ = (void*)new CStatementNodeIf(optElseIfs->Expressions, optElseIfs->Chunks);
	};

stat_rep_elseif:
	ELSEIF exp THEN block stat_rep_elseif
	{
		ExpressionNode expression = (ExpressionNode)$2;
		ChunkNode chunk = (ChunkNode)$4;

		OptElseIfs optElseIfs = (OptElseIfs)$5;
		optElseIfs->Expressions->push_front(expression);
		optElseIfs->Chunks->push_front(chunk);
		$$ = (void*)optElseIfs;		
	};

stat_rep_elseif:
	/*empty*/
	{
		OptElseIfs optElseIfs = new COptElseIfs();
		optElseIfs->Expressions = new CExpressionNodeList();
		optElseIfs->Chunks = new CChunkNodeList();
		$$ = (void*)optElseIfs;
	};

stat_opt_else:
	ELSE block
	{
		$$ = (void*)$2;
	};

stat_opt_else:
	/*empty*/
	{
		$$ = (void*)NULL;
	};

stat:
	FOR NAME EQUALS exp COMMA exp stat_opt_exp DO block END
	{
		 NameNode name = new CNameNode((yyvalType*)$2);
		 ExpressionNode exp1 = (ExpressionNode)$4;
		 ExpressionNode exp2 = (ExpressionNode)$6;
		 ExpressionNode exp3 = (ExpressionNode)$7;
		 ChunkNode chunk = (ChunkNode)$9;

		$$ = (void*)new CStatementNodeNumericFor(name, exp1, exp2, exp3, chunk);
	};

stat_opt_exp:
	COMMA exp
	{
		$$ = (void*)$2;
	};

stat_opt_exp:
	/*empty*/
	{
		$$ = (void*)NULL;
	};

stat:
	FOR namelist IN explist DO block END
	{
		NameNodeList names = (NameNodeList)$2;
		ExpressionNodeList expressions = (ExpressionNodeList)$4;
		ChunkNode chunk = (ChunkNode)$6;

		$$ = (void*)new CStatementNodeGenericFor(names, expressions, chunk);
	};

stat:
	FUNCTION funcname funcbody
	{
		NameNodeList names = (NameNodeList)$2;
		FunctionBodyNode bodyNode = (FunctionBodyNode)$3;

		$$ = (void*)new CStatementNodeFunctionDefinition(names, bodyNode);
	};

stat:
	LOCAL FUNCTION NAME funcbody
	{
		NameNode name = new CNameNode((yyvalType*)$3);
		FunctionBodyNode bodyNode = (FunctionBodyNode)$4;

		$$ = (void*)new CStatementNodeLocalFunctionDefinition(name, bodyNode);
	};

stat:
	LOCAL namelist stat_opt_explist
	{
		NameNodeList names = (NameNodeList)$2;
		ExpressionNodeList expressions = (ExpressionNodeList)$3;

		$$ = (void*)new CStatementNodeLocalVariableDeclaration(names, expressions);
	};

stat_opt_explist:
	EQUALS explist 
	{
		$$ = (void*)$2;
	};

stat_opt_explist:
	/*empty*/
	{
		$$ = (void*)new CExpressionNodeList();
	};

laststat:
	RETURN laststat_opt_explist
	{		
		ExpressionNodeList expressions = (ExpressionNodeList)$2;

		$$ = (void*)new CStatementNodeReturn(expressions);
	};

laststat_opt_explist:
	explist
	{
		$$ = (void*)$1;
	};

laststat_opt_explist:
	/*empty*/
	{
		$$ = (void*)new CExpressionNodeList();;
	};

laststat:
	BREAK
	{
		$$ = (void*)new CStatementNodeBreak();
	};

funcname:
	NAME funcname_rep_name
	{
		NameNode name = new CNameNode((yyvalType*)$1);
		NameNodeList names = (NameNodeList)$2;
		names->push_front(name);
		$$ = names;
	};

funcname_rep_name:
	DOT NAME funcname_rep_name
	{
		NameNode name = new CNameNode((yyvalType*)$2);
		NameNodeList names = (NameNodeList)$3;
		names->push_front(name);
		$$ = names;
	};

funcname_rep_name:
	/*empty*/
	{
		$$ = (void*)new CNameNodeList();
	};

varlist:
	var varlist_rep_var
	{
		VariableNode var = (VariableNode)$1;
		VariableNodeList vars = (VariableNodeList)$2;
		vars->push_front(var);
		$$ = vars;
	};

varlist_rep_var:
	COMMA var varlist_rep_var
	{
		VariableNode var = (VariableNode)$2;
		VariableNodeList vars = (VariableNodeList)$3;
		vars->push_front(var);
		$$ = vars;
	};

varlist_rep_var:
	/*empty*/
	{
		$$ = (void*)new CVariableNodeList();
	};

var:
	 NAME 
	{
		NameNode name = new CNameNode((yyvalType*)$1);
		$$ = (void*)new CVariableNodeName(name);
	};

var:
	prefixexp OPEN_BRACK exp CLOSE_BRACK 
	{
		PrefixNode prefix = (PrefixNode)$1;
		ExpressionNode expression = (ExpressionNode)$3;
		$$ = (void*)new CVariableNodePrefixBracket(prefix, expression);
	};

var:
	prefixexp DOT NAME
	{
		PrefixNode prefix = (PrefixNode)$1;
		NameNode name = new CNameNode((yyvalType*)$3);
		$$ = (void*)new CVariableNodePrefixDot(prefix, name);
	};

namelist:
	NAME namelist_rep_name
	{
		NameNode name = new CNameNode((yyvalType*)$1);
		NameNodeList names = (NameNodeList)$2;
		names->push_front(name);
		$$ = (void*)names;
	};

namelist_rep_name:
	COMMA NAME namelist_rep_name
	{
		NameNode name = new CNameNode((yyvalType*)$2);
		NameNodeList names = (NameNodeList)$3;
		names->push_front(name);
		$$ = (void*)names;
	};

namelist_rep_name:
	/*empty*/
	{
		$$ = (void*)new CNameNodeList();
	};

explist:
	exp explist_rep_exp 
	{
		ExpressionNode expression = (ExpressionNode)$1;
		ExpressionNodeList expressions = (ExpressionNodeList)$2;
		expressions->push_front(expression);
		$$ = (void*)expressions;
	};

explist_rep_exp:
	COMMA exp explist_rep_exp
	{
		ExpressionNode expression = (ExpressionNode)$2;
		ExpressionNodeList expressions = (ExpressionNodeList)$3;
		expressions->push_front(expression);
		$$ = (void*)expressions;
	};

explist_rep_exp:
	/*empty*/
	{
		$$ = (void*)new CExpressionNodeList();
	};

exp:
	NIL 
	{
		$$ = (void*)new CExpressionNodeNil();
	};

exp:
	FALSE
	{
		$$ = (void*)new CExpressionNodeBool(false);
	};

exp:
	TRUE
	{
		$$ = (void*)new CExpressionNodeBool(true);
	};

exp:
	NUMBER 
	{
		NumberNode number = new CNumberNode((yyvalType*)$1);
		$$ = (void*)new CExpressionNodeNumber(number);
	};

exp:
	STRING 
	{
		StringNode stringNode = new CStringNode((yyvalType*)$1);
		$$ = (void*)new CExpressionNodeString(stringNode);
	};

exp:
	DOTDOTDOT 
	{
		$$ = (void*)new CExpressionNodeDots();
	};

exp:
	prefixexp 
	{
		PrefixNode prefix = (PrefixNode)$1;
		$$ = (void*)new CExpressionNodePrefix(prefix);
	};

exp:
	tableconstructor 
	{
		FieldNodeList fields = (FieldNodeList)$1;
		$$ = (void*)new CExpressionNodeTableConstructor(fields);
	};

exp:
	exp binop exp 
	{
		ExpressionNode exp1 = (ExpressionNode)$1;
		BinaryOperationType biop = (BinaryOperationType)(long)$2;
		ExpressionNode exp2 = (ExpressionNode)$3;
		$$ = (void*)new CExpressionNodeBinaryOperation(biop, exp1, exp2);
	};

exp:
	unop exp 
	{
		UnaryOperationType uop = (UnaryOperationType)(long)$1;
		ExpressionNode exp = (ExpressionNode)$2;
		$$ = (void*)new CExpressionNodeUnaryOperation(uop, exp);
	};

prefixexp:
	var 
	{
		VariableNode var = (VariableNode)$1;
		$$ = (void*)new CPrefixNodeVariable(var);
	};

prefixexp:
	functioncall 
	{
		FunctionCallNode functionCallNode = (FunctionCallNode)$1;
		$$ = (void*)new CPrefixNodeFunctionCall(functionCallNode);
	};

prefixexp:
	OPEN_PAR exp CLOSE_PAR
	{
		ExpressionNode expressionNode = (ExpressionNode)$2;
		$$ = (void*)new CPrefixNodeParenthesis(expressionNode);
	};

functioncall:
	prefixexp args 
	{
		PrefixNode prefix = (PrefixNode)$1;
		ExpressionNodeList args = (ExpressionNodeList)$2;
		$$ = (void*)new CFunctionCallNode(prefix, args);
	};

args:
	OPEN_PAR args_opt_explist CLOSE_PAR 
	{
		$$ = (void*)$2;
	};

args_opt_explist:
	explist 
	{
		$$ = (void*)$1;
	};

args_opt_explist:
	/*empty*/
	{
		$$ = (void*)new CExpressionNodeList();
	};

args:
	tableconstructor 
	{
		FieldNodeList fields = (FieldNodeList)$1;
 		ExpressionNodeTableConstructor tblNode = new CExpressionNodeTableConstructor(fields);
		ExpressionNodeList expNodes = new CExpressionNodeList();
		expNodes->push_front(tblNode);
		$$ = expNodes;
	};

args:
	STRING 
	{
		StringNode str = new CStringNode((yyvalType*)$1);
 		ExpressionNodeString strNode = new CExpressionNodeString(str);
		ExpressionNodeList expNodes = new CExpressionNodeList();
		expNodes->push_front(strNode);
		$$ = expNodes;
	};

funcbody:
	OPEN_PAR funcbody_opt_parlist CLOSE_PAR block END
	{
		ParamsList parms = (ParamsList)$2;
		ChunkNode chunk = (ChunkNode)$4;
		$$ = (void*)new CFunctionBodyNode(parms->Names, parms->Dots, chunk);		
	};

funcbody_opt_parlist:
	parlist
	{
		$$ = (void*)$1;
	};

funcbody_opt_parlist:
	/*empty*/
	{
		ParamsList parms = new CParamsList();
		parms->Names = new CNameNodeList();
		parms->Dots = false;
		$$ = (void*)parms;
	};

parlist:
	namelist parlist_opt_dots
	{
		ParamsList parms = new CParamsList();
		parms->Names = (NameNodeList)$1;
		parms->Dots = (bool)$2;
		$$ = (void*)parms;
	};

parlist_opt_dots:
	COMMA DOTDOTDOT
	{
		$$ = (void*)true;
	};

parlist_opt_dots:
	/*empty*/
	{
		$$ = (void*)false;
	};

parlist:
	DOTDOTDOT
	{
		ParamsList parms = new CParamsList();
		parms->Names = new CNameNodeList();
		parms->Dots = true;
		$$ = (void*)parms;
	};

tableconstructor:
	OPEN_SQUIG tableconstructor_opt_fieldlist CLOSE_SQUIG
	{
		$$ = (void*)$2;
	};

tableconstructor_opt_fieldlist :
	fieldlist
	{
		$$ = (void*)$1;
	};

tableconstructor_opt_fieldlist :
	/*empty*/
	{
		$$ = (void*)new CFieldNodeList();
	};

fieldlist:
	field fieldlist_rep_field
	{
		FieldNode field = (FieldNode)$1;
		FieldNodeList fieldList = (FieldNodeList)$2;
		fieldList->push_front(field);
		$$ = (void*)fieldList;
	};

fieldlist:
	field fieldsep fieldlist_rep_field2
	{
		FieldNode field = (FieldNode)$1;
		FieldNodeList fieldList = (FieldNodeList)$3;
		fieldList->push_front(field);
		$$ = (void*)fieldList;
	};

fieldlist_rep_field:
	fieldsep field fieldlist_rep_field
	{
		FieldNode field = (FieldNode)$2;
		FieldNodeList fieldList = (FieldNodeList)$3;
		fieldList->push_front(field);
		$$ = (void*)fieldList;
	};

fieldlist_rep_field:
	/*empty*/
	{
		$$ = (void*)new CFieldNodeList();
	};

fieldlist_rep_field2:
	field fieldsep fieldlist_rep_field2
	{
		FieldNode field = (FieldNode)$1;
		FieldNodeList fieldList = (FieldNodeList)$3;
		fieldList->push_front(field);
		$$ = (void*)fieldList;
	};

fieldlist_rep_field2:
	/*empty*/
	{
		$$ = (void*)new CFieldNodeList();
	};


field:
	OPEN_BRACK exp CLOSE_BRACK EQUALS exp 
	{
		ExpressionNode exp1 = (ExpressionNode)$2;
		ExpressionNode exp2 = (ExpressionNode)$4;
		$$ = (void*)new CFieldNodeBracket(exp1, exp2);
	};

field:
	NAME EQUALS exp 
	{
		NameNode name = new CNameNode((yyvalType*)$1);
		ExpressionNode exp = (ExpressionNode)$3;
		$$ = (void*)new CFieldNodeName(name, exp);
	};

field:
	exp
	{
		ExpressionNode exp = (ExpressionNode)$1;
		$$ = (void*)new CFieldNodeExpression(exp);
	};

fieldsep:
	COMMA 
	{
		$$ = (void*)NULL;
	};

fieldsep:
	SEMI
	{
		$$ = (void*)NULL;
	};

binop:
	PLUS 
	{
		BinaryOperationType ret = Plus;
		$$ = (void*)ret;
	};

binop:
	MINUS
	{
		BinaryOperationType ret = Minus;
		$$ = (void*)ret;
	};

binop:
	STAR 
	{
		BinaryOperationType ret = Times;
		$$ = (void*)ret;
	};

binop:
	FSLASH
	{
		BinaryOperationType ret = Divide;
		$$ = (void*)ret;
	};

binop:
	CARET
	{
		BinaryOperationType ret = Raise;
		$$ = (void*)ret;
	};

binop:
	PERCENT 
	{
		BinaryOperationType ret = Modulus;
		$$ = (void*)ret;
	};

binop:
	DOTDOT
	{
		BinaryOperationType ret = Concat;
		$$ = (void*)ret;
	};

binop:
	LESS
	{
		BinaryOperationType ret = Less;
		$$ = (void*)ret;
	};

binop:
	LESS_EQUAL		
	{
		BinaryOperationType ret = LessEqual;
		$$ = (void*)ret;
	};

binop:
	MORE
	{
		BinaryOperationType ret = More;
		$$ = (void*)ret;
	};

binop:
	MORE_EQUAL
	{
		BinaryOperationType ret = MoreEqual;
		$$ = (void*)ret;
	};

binop:
	EQUAL_EQUAL
	{
		BinaryOperationType ret = Equal;
		$$ = (void*)ret;
	};

binop:
	SQUIG_EQUAL
	{
		BinaryOperationType ret = NotEqual;
		$$ = (void*)ret;
	};

binop:
	AND
	{
		BinaryOperationType ret = And;
		$$ = (void*)ret;
	};

binop:
	OR
	{
		BinaryOperationType ret = Or;
		$$ = (void*)ret;
	};

unop:
	MINUS
	{	
		UnaryOperationType ret = Negate;
		$$ = (void*)ret;
	};

unop:
	NOT
	{	
		UnaryOperationType ret = Not;
		$$ = (void*)ret;
	};

unop:
	SHARP
	{	
		UnaryOperationType ret = Lenght;
		$$ = (void*)ret;
	};


