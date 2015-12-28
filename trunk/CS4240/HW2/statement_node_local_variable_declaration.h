#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "VALUE"
#endif

#ifndef STATEMENT_NODE_LOCAL_VARIABLE_DECLARATION_H
#define STATEMENT_NODE_LOCAL_VARIABLE_DECLARATION_H


#include "base_node.h"
#include "statement_node.h"
#include "statement_node_assign.h"
#include "name_node.h"
#include "expression_node.h"
#include "symbol_table.h"
#include "variable_node.h"
#include "variable_node_name.h"

#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeLocalVariableDeclaration : public CStatementNode

{

    public:

        CStatementNodeLocalVariableDeclaration(NameNodeList names, ExpressionNodeList expressions);
        virtual ~CStatementNodeLocalVariableDeclaration();

		NameNodeList GetNames();
		ExpressionNodeList GetExpressions();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType() { return STAT_TYPE; }


    protected:

    private:
		NameNodeList m_names;
		ExpressionNodeList m_expressions;

};

typedef CStatementNodeLocalVariableDeclaration* StatementNodeLocalVariableDeclaration;
typedef list<StatementNodeLocalVariableDeclaration> CStatementNodeLocalVariableDeclarationList;
typedef CStatementNodeLocalVariableDeclarationList* StatementNodeLocalVariableDeclarationList;
typedef CStatementNodeLocalVariableDeclarationList::iterator StatementNodeLocalVariableDeclarationIter;



#endif // STATEMENT_NODE_LOCAL_VARIABLE_DECLARATION_H

