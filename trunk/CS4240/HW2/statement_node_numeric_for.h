#ifndef NODE_TYPE
#define NODE_TYPE "stat"
#endif

#ifndef STAT_TYPE
#define STAT_TYPE "UNIT"
#endif

#ifndef STATEMENT_NODE_NUMERIC_FOR_H
#define STATEMENT_NODE_NUMERIC_FOR_H


#include "base_node.h"
#include "statement_node.h"
#include "expression_node.h"
#include "chunk_node.h"
#include "name_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CStatementNodeNumericFor : public CStatementNode

{

    public:

        CStatementNodeNumericFor(NameNode name, ExpressionNode exp1, ExpressionNode exp2, ExpressionNode exp3, ChunkNode chunk);
        virtual ~CStatementNodeNumericFor();

		NameNode GetName();
		ExpressionNode GetExp1();
		ExpressionNode GetExp2();
		ExpressionNode GetExp3();
		ChunkNode GetChunk();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);
        virtual string GetStatementType() { return STAT_TYPE; }

    protected:

    private:
		NameNode m_name;
		ExpressionNode m_exp1;
		ExpressionNode m_exp2;
		ExpressionNode m_exp3;
		ChunkNode m_chunk;

};

typedef CStatementNodeNumericFor* StatementNodeNumericFor;
typedef list<StatementNodeNumericFor> CStatementNodeNumericForList;
typedef CStatementNodeNumericForList* StatementNodeNumericForList;
typedef CStatementNodeNumericForList::iterator StatementNodeNumericForIter;



#endif // STATEMENT_NODE_NUMERIC_FOR_H

