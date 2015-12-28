#include "field_node_bracket.h"

CFieldNodeBracket::CFieldNodeBracket(ExpressionNode bracketExpression, ExpressionNode equalsExpression)
{
	m_bracketExpression = bracketExpression;
	m_equalsExpression = equalsExpression;
}

CFieldNodeBracket::~CFieldNodeBracket()
{
}


ExpressionNode CFieldNodeBracket::GetBracketExpression()
{
	return m_bracketExpression;
}

ExpressionNode CFieldNodeBracket::GetEqualsExpression()
{
	return m_equalsExpression;
}

void CFieldNodeBracket::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Field " << m_linenum << endl;

	m_bracketExpression->PrintNode(file, tabCount+1);
	m_equalsExpression->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CFieldNodeBracket::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_bracketExpression->GenerateSymbolTables(NULL);
        m_equalsExpression->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_bracketExpression->GenerateSymbolTables(m_localSymbolTable);
    m_equalsExpression->GenerateSymbolTables(m_localSymbolTable);
}
