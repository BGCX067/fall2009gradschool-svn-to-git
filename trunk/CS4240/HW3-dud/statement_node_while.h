#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "UNIT"
#endif

#ifndef STATEMENT_NODE_WHILE_H
#define STATEMENT_NODE_WHILE_H


#include "base_node.h"
#include "statement_node.h"
#include "expression_node.h"
#include "chunk_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeWhile : public CStatementNode

{

    public:

        CStatementNodeWhile(ExpressionNode expressionNode, ChunkNode chunkNode);
        virtual ~CStatementNodeWhile();

		ExpressionNode GetExpressionNode();
		ChunkNode GetChunkNode();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetStatementType() { return STAT_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);

    protected:

    private:
		ExpressionNode m_expressionNode;
		ChunkNode m_chunkNode;

};

typedef CStatementNodeWhile* StatementNodeWhile;
typedef list<StatementNodeWhile> CStatementNodeWhileList;
typedef CStatementNodeWhileList* StatementNodeWhileList;
typedef CStatementNodeWhileList::iterator StatementNodeWhileIter;



#endif // STATEMENT_NODE_WHILE_H

