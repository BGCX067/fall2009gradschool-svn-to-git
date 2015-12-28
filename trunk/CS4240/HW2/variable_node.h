#ifndef NODE_TYPE
#define NODE_TYPE "var"
#endif

#ifndef VARIABLE_NODE_H
#define VARIABLE_NODE_H


#include "base_node.h"
#include "name_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

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


class CVariableNode : public CBaseNode //abstract
{
    public:

        CVariableNode();
        virtual ~CVariableNode();

		virtual void PrintNode(ostream& file, int tabCount)=0;
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual list<BaseNode> GetChildren()=0;
		//rets vars loc in mem
		virtual Value* Codegen(IRBuilder<>* builder, bool locationOnly) = 0;

		virtual NameNode GetNameNode(){ return NULL; }

    protected:

    private:
		

};

typedef CVariableNode* VariableNode;
typedef list<VariableNode> CVariableNodeList;
typedef CVariableNodeList* VariableNodeList;
typedef CVariableNodeList::iterator VariableNodeIter;


#endif // VARIABLE_NODE_H

