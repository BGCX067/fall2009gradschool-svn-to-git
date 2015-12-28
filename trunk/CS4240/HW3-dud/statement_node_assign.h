#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "VALUE"
#endif

#ifndef STATEMENT_NODE_ASSIGN_H
#define STATEMENT_NODE_ASSIGN_H


#include "base_node.h"
#include "statement_node.h"
#include "variable_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

#include <llvm/Module.h>
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"


#include "llvm_generator.h"


using namespace llvm;
using namespace std;

class CStatementNodeAssign : public CStatementNode

{

    public:

        CStatementNodeAssign(VariableNodeList variables, ExpressionNodeList expressions);
        virtual ~CStatementNodeAssign();
		VariableNodeList GetVariables();
		ExpressionNodeList GetExpressions();
		void PrintNode(ostream& file, int tabCount);

		//each statement gets: (this is the same as a block node)
		//block - functionality of the statement should start in this block (more block can be made but this must be the first)
		//function - if more block need be made this is the function they should be made with this function
		//breakBlock - if a break happens in this statement or somewhere down the line this is the block that gets breaked to
		//return - the last block of this statement
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);

        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetStatementType() { return STAT_TYPE; }

    protected:

    private:
		VariableNodeList m_variables;
		ExpressionNodeList m_expressions;
};

typedef CStatementNodeAssign* StatementNodeAssign;
typedef list<StatementNodeAssign> CStatementNodeAssignList;
typedef CStatementNodeAssignList* StatementNodeAssignList;
typedef CStatementNodeAssignList::iterator StatementNodeAssignIter;



#endif // STATEMENT_NODE_ASSIGN_H

