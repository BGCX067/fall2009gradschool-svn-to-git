#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "VALUE"
#endif

#ifndef STATEMENT_NODE_LOCAL_FUNCTION_DEFINITION_H
#define STATEMENT_NODE_LOCAL_FUNCTION_DEFINITION_H


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


class CStatementNodeLocalFunctionDefinition : public CStatementNode

{

    public:

        CStatementNodeLocalFunctionDefinition(NameNode name, FunctionBodyNode functionBody);
        virtual ~CStatementNodeLocalFunctionDefinition();

		NameNode GetName();
		FunctionBodyNode GetFunctionBody();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType();


    protected:

    private:

		NameNode m_name;
		FunctionBodyNode m_functionBody;
};

typedef CStatementNodeLocalFunctionDefinition* StatementNodeLocalFunctionDefinition;
typedef list<StatementNodeLocalFunctionDefinition> CStatementNodeLocalFunctionDefinitionList;
typedef CStatementNodeLocalFunctionDefinitionList* StatementNodeLocalFunctionDefinitionList;
typedef CStatementNodeLocalFunctionDefinitionList::iterator StatementNodeLocalFunctionDefinitionIter;



#endif // STATEMENT_NODE_LOCAL_FUNCTION_DEFINITION_H

