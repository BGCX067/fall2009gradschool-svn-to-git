#include "expression_node_number.h"

CExpressionNodeNumber::CExpressionNodeNumber(NumberNode value)
{
	m_value = value;
}

CExpressionNodeNumber::~CExpressionNodeNumber()
{
}

NumberNode CExpressionNodeNumber::GetValue()
{
	return m_value;
}

void CExpressionNodeNumber::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Num " << m_value->GetValue() << " )" << endl;
}

void CExpressionNodeNumber::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_value->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;
    m_value->GenerateSymbolTables(m_localSymbolTable);
}



Value*  CExpressionNodeNumber::Codegen(IRBuilder<>* builder)
{
	return m_value->Codegen();
}

string CExpressionNodeNumber::GetExpressionType()
{
    return VAR_NUMBER__ENTRY_TYPE;
}
