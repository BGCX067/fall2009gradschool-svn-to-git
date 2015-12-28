#ifndef NODE_TYPE
#define NODE_TYPE "prefixexp"
#endif

#ifndef PREFIX_NODE_FUNCTION_CALL_H
#define PREFIX_NODE_FUNCTION_CALL_H


#include "base_node.h"
#include "prefix_node.h"
#include "function_call_node.h"
#include "name_node.h"
#include "variable_node_name.h"
#include "prefix_node_variable.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CPrefixNodeFunctionCall : public CPrefixNode
{
    public:

        CPrefixNodeFunctionCall(FunctionCallNode functionCall);
        virtual ~CPrefixNodeFunctionCall();

		FunctionCallNode GetFunctionCall();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetPrefixType();
		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:
		FunctionCallNode m_functionCall;

};

typedef CPrefixNodeFunctionCall* PrefixNodeFunctionCall;
typedef list<PrefixNodeFunctionCall> CPrefixNodeFunctionCallList;
typedef CPrefixNodeFunctionCallList* PrefixNodeFunctionCallList;
typedef CPrefixNodeFunctionCallList::iterator PrefixNodeFunctionCallIter;



#endif // PREFIX_NODE_FUNCTION_CALL_H

