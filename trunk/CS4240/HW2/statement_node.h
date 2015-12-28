#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "UNIT"
#endif


#ifndef STATEMENT_NODE_H
#define STATEMENT_NODE_H

#include "base_node.h"
#include <list>
#include <iostream>
#include <fstream>

#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"


#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace llvm;
using namespace std;

class CStatementNode : public CBaseNode //abstract
{
    public:
        CStatementNode();
        virtual ~CStatementNode();

		virtual void PrintNode(ostream& file, int tabCount)=0;

		//each statement gets: (this is the same as a block node)
		//block - functionality of the statement should start in this block (more block can be made but this must be the first)
		//function - if more block need be made this is the function they should be made with this function
		//breakBlock - if a break happens in this statement or somewhere down the line this is the block that gets breaked to
		//return - the last block of this statement 
		virtual	BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock) = 0;

        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetStatementType()=0;

    protected:
    private:
};

typedef CStatementNode* StatementNode;
typedef list<StatementNode> CStatementNodeList;
typedef CStatementNodeList* StatementNodeList;
typedef CStatementNodeList::iterator StatementNodeIter;

#endif // STATEMENT_NODE_H
