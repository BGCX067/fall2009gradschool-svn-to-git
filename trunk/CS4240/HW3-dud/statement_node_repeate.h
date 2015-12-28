#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "UNIT"
#endif

#ifndef STATEMENT_NODE_REPEATE_H
#define STATEMENT_NODE_REPEATE_H


#include "base_node.h"
#include "chunk_node.h"
#include "expression_node.h"
#include "statement_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeRepeate : public CStatementNode

{

    public:

        CStatementNodeRepeate(ChunkNode chunkNode, ExpressionNode expressionNode);
        virtual ~CStatementNodeRepeate();

		ChunkNode GetChunkNode();
		ExpressionNode GetExpressionNode();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetStatementType() { return STAT_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);

    protected:

    private:
		ChunkNode m_chunkNode;
		ExpressionNode m_expressionNode;


};

typedef CStatementNodeRepeate* StatementNodeRepeate;
typedef list<StatementNodeRepeate> CStatementNodeRepeateList;
typedef CStatementNodeRepeateList* StatementNodeRepeateList;
typedef CStatementNodeRepeateList::iterator StatementNodeRepeateIter;



#endif // STATEMENT_NODE_REPEATE_H

