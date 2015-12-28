#ifndef NODE_TYPE
#define NODE_TYPE "functioncall"
#endif

#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H


#include "base_node.h"
#include "expression_node.h"
#include "prefix_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

#include "llvm_generator.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CFunctionCallNode : public CBaseNode 
{
    public:

        CFunctionCallNode(PrefixNode prefix, ExpressionNodeList args);
        virtual ~CFunctionCallNode();


		PrefixNode GetPrefix();
		ExpressionNodeList GetArguments();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		Value* Codegen(IRBuilder<>* builder);


    protected:

    private:
		PrefixNode m_prefix;
		ExpressionNodeList m_args;


};

typedef CFunctionCallNode* FunctionCallNode;
typedef list<FunctionCallNode> CFunctionCallNodeList;
typedef CFunctionCallNodeList* FunctionCallNodeList;
typedef CFunctionCallNodeList::iterator FunctionCallNodeIter;



#endif // FUNCTION_CALL_NODE_H

