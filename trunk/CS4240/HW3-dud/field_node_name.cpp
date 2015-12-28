#include "field_node_name.h"

CFieldNodeName::CFieldNodeName(NameNode name, ExpressionNode expression)
{
	m_name = name;
	m_expression = expression;
}

CFieldNodeName::~CFieldNodeName()
{
}

NameNode CFieldNodeName::GetName()
{
	return m_name;
}
ExpressionNode CFieldNodeName::GetExpression()
{
	return m_expression;
}


void CFieldNodeName::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Field " << m_linenum << endl;

	PrintTabs(file, tabCount+1);
	file << "( " << m_name->GetValue() << " )" << endl;

	m_expression->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CFieldNodeName::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_expression->GenerateSymbolTables(NULL);
        m_name->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_expression->GenerateSymbolTables(m_localSymbolTable);
    m_name->GenerateSymbolTables(m_localSymbolTable);
}
