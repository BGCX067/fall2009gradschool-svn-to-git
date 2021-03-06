#ifndef NODE_TYPE
#define NODE_TYPE "laststat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "UNIT"
#endif

#ifndef STATEMENT_NODE_BREAK_H
#define STATEMENT_NODE_BREAK_H


#include "base_node.h"
#include "statement_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeBreak : public CStatementNode

{

    public:

        CStatementNodeBreak();
        virtual ~CStatementNodeBreak();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }

		//each statement gets: (this is the same as a block node)
		//block - functionality of the statement should start in this block (more block can be made but this must be the first)
		//function - if more block need be made this is the function they should be made with this function
		//breakBlock - if a break happens in this statement or somewhere down the line this is the block that gets breaked to
		//return - the last block of this statement
		virtual	BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType() { return STAT_TYPE; }


    protected:

    private:

};


typedef CStatementNodeBreak* StatementNodeBreak;
typedef list<StatementNodeBreak> CStatementNodeBreakList;
typedef CStatementNodeBreakList* StatementNodeBreakList;
typedef CStatementNodeBreakList::iterator StatementNodeBreakIter;



#endif // STATEMENT_NODE_BREAK_H

