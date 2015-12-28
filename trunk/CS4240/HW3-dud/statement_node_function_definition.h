#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "VALUE"
#endif

#ifndef STATEMENT_NODE_FUNCTION_DEFINITION_H
#define STATEMENT_NODE_FUNCTION_DEFINITION_H


#include "base_node.h"
#include "statement_node.h"
#include "name_node.h"
#include "function_body_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeFunctionDefinition : public CStatementNode

{

    public:

        CStatementNodeFunctionDefinition(NameNodeList names, FunctionBodyNode functionBody);
        virtual ~CStatementNodeFunctionDefinition();


		NameNodeList GetNames();

		string FullName();

		FunctionBodyNode GetFunctionBody();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType();
        CSymbolTableNode* GetLocalSymbolTable() { return m_localSymbolTable; }


    protected:

    private:
		NameNodeList m_names;
		FunctionBodyNode m_functionBody;
};

typedef CStatementNodeFunctionDefinition* StatementNodeFunctionDefinition;
typedef list<StatementNodeFunctionDefinition> CStatementNodeFunctionDefinitionList;
typedef CStatementNodeFunctionDefinitionList* StatementNodeFunctionDefinitionList;
typedef CStatementNodeFunctionDefinitionList::iterator StatementNodeFunctionDefinitionIter;



#endif // STATEMENT_NODE_FUNCTION_DEFINITION_H

