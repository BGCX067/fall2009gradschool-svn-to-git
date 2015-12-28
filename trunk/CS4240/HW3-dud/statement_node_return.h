#ifndef NODE_TYPE
#define NODE_TYPE "laststat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "VALUE"
#endif

#ifndef STATEMENT_NODE_RETURN_H
#define STATEMENT_NODE_RETURN_H


#include "base_node.h"
#include "statement_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeReturn : public CStatementNode

{

    public:

        CStatementNodeReturn(ExpressionNodeList expressions);
        virtual ~CStatementNodeReturn();

		ExpressionNodeList GetExpressions();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType() { return STAT_TYPE; }

    protected:

    private:
		ExpressionNodeList m_expressions;

};

typedef CStatementNodeReturn* StatementNodeReturn;
typedef list<StatementNodeReturn> CStatementNodeReturnList;
typedef CStatementNodeReturnList* StatementNodeReturnList;
typedef CStatementNodeReturnList::iterator StatementNodeReturnIter;



#endif // STATEMENT_NODE_RETURN_H

