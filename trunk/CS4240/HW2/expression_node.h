#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H


#include "base_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using namespace std;


class CExpressionNode : public CBaseNode //abstract
{
    public:

        CExpressionNode();
        virtual ~CExpressionNode();

		virtual void PrintNode(ostream& file, int tabCount)=0;
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType()=0;
		virtual Value* Codegen(IRBuilder<>* builder) = 0;

    protected:

    private:


};

typedef CExpressionNode* ExpressionNode;
typedef list<ExpressionNode> CExpressionNodeList;
typedef CExpressionNodeList* ExpressionNodeList;
typedef CExpressionNodeList::iterator ExpressionNodeIter;


#endif // EXPRESSION_NODE_H

