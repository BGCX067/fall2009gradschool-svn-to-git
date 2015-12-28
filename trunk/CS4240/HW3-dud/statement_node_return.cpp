#include "statement_node_return.h"

CStatementNodeReturn::CStatementNodeReturn(ExpressionNodeList expressions)
{
	m_expressions = expressions;
}

CStatementNodeReturn::~CStatementNodeReturn()
{
}

ExpressionNodeList CStatementNodeReturn::GetExpressions()
{
	return m_expressions;
}


void CStatementNodeReturn::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Return " << endl;


	ExpressionNodeIter it;
	for (it=m_expressions->begin(); it!=m_expressions->end(); it++)
	{
		ExpressionNode expression = *it;
		expression->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeReturn::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }
}

BasicBlock* CStatementNodeReturn::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	//create a builder for this block
	IRBuilder<> builder(block);
	Value* evalExp = m_expressions->front()->Codegen(&builder);
	builder.CreateRet(evalExp);	
	return block;
}

