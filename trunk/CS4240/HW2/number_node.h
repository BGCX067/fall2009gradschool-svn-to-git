#ifndef NODE_TYPE
#define NODE_TYPE "number"
#endif

#ifndef LEXNUMBERVAL_H
#define LEXNUMBERVAL_H

#include "base_node.h"
#include "yyvaltype.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

extern CSymbolTableNode globalSymbolTable;
using namespace llvm;
using namespace std;

class CNumberNode : public CBaseNode
{
    public:
        CNumberNode(yyvalType* yyvaltype);
        virtual ~CNumberNode();

		double GetValue();
		void PrintNode(ostream& file, int tabCount);


		virtual Value* Codegen();
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }

    protected:
    private:
        double m_value;
};

typedef CNumberNode* NumberNode;
typedef list<NumberNode> CNumberNodeList;
typedef CNumberNodeList* NumberNodeList;
typedef CNumberNodeList::iterator NumberNodeIter;

#endif // LEXNUMBERVAL_H
