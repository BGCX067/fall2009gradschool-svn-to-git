#include "expression_node_string.h"

CExpressionNodeString::CExpressionNodeString(StringNode value)
{
	m_value = value;
}

CExpressionNodeString::~CExpressionNodeString()
{
}


StringNode CExpressionNodeString::GetValue()
{
	return m_value;
}

void CExpressionNodeString::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( " << m_value->GetValue() << " )" << endl;
}

void CExpressionNodeString::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_value->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;
    m_value->GenerateSymbolTables(m_localSymbolTable);
}

string CExpressionNodeString::GetExpressionType()
{
    return VAR_STRING__ENTRY_TYPE;
}

Value* CExpressionNodeString::Codegen(IRBuilder<>* builder)
{
	return m_value->Codegen(builder);
}

