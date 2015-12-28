#include "field_node_expression.h"

CFieldNodeExpression::CFieldNodeExpression(ExpressionNode expression)
{
	m_expression = expression;
}

CFieldNodeExpression::~CFieldNodeExpression()
{
}


ExpressionNode CFieldNodeExpression::GetExpression()
{
	return m_expression;
}


void CFieldNodeExpression::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Field " << m_linenum << endl;

	m_expression->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CFieldNodeExpression::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_expression->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_expression->GenerateSymbolTables(m_localSymbolTable);
}
