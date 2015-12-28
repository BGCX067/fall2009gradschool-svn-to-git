#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "VALUE"
#endif

#ifndef STATEMENT_NODE_FUNTION_CALL_H
#define STATEMENT_NODE_FUNTION_CALL_H


#include "base_node.h"
#include "statement_node.h"
#include "function_call_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeFuntionCall : public CStatementNode

{

    public:

        CStatementNodeFuntionCall(FunctionCallNode functionCall);
        virtual ~CStatementNodeFuntionCall();

		FunctionCallNode GetFunctionCall();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType() { return STAT_TYPE; }
        string GetFunctionCallType(string functionName);


    protected:

    private:
		FunctionCallNode m_functionCall;

};

typedef CStatementNodeFuntionCall* StatementNodeFuntionCall;
typedef list<StatementNodeFuntionCall> CStatementNodeFuntionCallList;
typedef CStatementNodeFuntionCallList* StatementNodeFuntionCallList;
typedef CStatementNodeFuntionCallList::iterator StatementNodeFuntionCallIter;



#endif // STATEMENT_NODE_FUNTION_CALL_H

