#include "statement_node_generic_for.h"

CStatementNodeGenericFor::CStatementNodeGenericFor(NameNodeList names, ExpressionNodeList expressions, ChunkNode chunk)
{
	m_names = names;
	m_expressions = expressions;
	m_chunk = chunk;
}

CStatementNodeGenericFor::~CStatementNodeGenericFor()
{
}

NameNodeList CStatementNodeGenericFor::GetNames()
{
	return m_names;
}

ExpressionNodeList CStatementNodeGenericFor::GetExpressions()
{
	return m_expressions;
}

ChunkNode CStatementNodeGenericFor::GetChunk()
{
	return m_chunk;
}


void CStatementNodeGenericFor::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( For " << endl;

	NameNodeIter it;
	for (it=m_names->begin(); it!=m_names->end(); it++)
	{
		NameNode name = *it;
		name->PrintNode(file, tabCount+1);
	}

	ExpressionNodeIter it2;
	for (it2=m_expressions->begin(); it2!=m_expressions->end(); it2++)
	{
		ExpressionNode expression = *it2;
		expression->PrintNode(file, tabCount+1);
	}

	m_chunk->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeGenericFor::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        m_chunk->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }

    for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }

    m_chunk->GenerateSymbolTables(m_localSymbolTable);
}



BasicBlock* CStatementNodeGenericFor::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	//not sure how to support these or if we even need to they use some special iterator function
	return block;
}







