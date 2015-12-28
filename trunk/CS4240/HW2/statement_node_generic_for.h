#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "UNIT"
#endif

#ifndef STATEMENT_NODE_GENERIC_FOR_H
#define STATEMENT_NODE_GENERIC_FOR_H


#include "base_node.h"
#include "statement_node.h"
#include "name_node.h"
#include "expression_node.h"
#include "chunk_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeGenericFor : public CStatementNode

{

    public:

        CStatementNodeGenericFor(NameNodeList names, ExpressionNodeList expressions, ChunkNode chunk);
        virtual ~CStatementNodeGenericFor();

		NameNodeList GetNames();
		ExpressionNodeList GetExpressions();
		ChunkNode GetChunk();
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
		NameNodeList m_names;
		ExpressionNodeList m_expressions;
		ChunkNode m_chunk;

};

typedef CStatementNodeGenericFor* StatementNodeGenericFor;
typedef list<StatementNodeGenericFor> CStatementNodeGenericForList;
typedef CStatementNodeGenericForList* StatementNodeGenericForList;
typedef CStatementNodeGenericForList::iterator StatementNodeGenericForIter;



#endif // STATEMENT_NODE_GENERIC_FOR_H

