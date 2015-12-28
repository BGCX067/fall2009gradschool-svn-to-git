#include "expression_node_prefix.h"

CExpressionNodePrefix::CExpressionNodePrefix(PrefixNode prefixNode)
{
	m_prefixNode = prefixNode;
}

CExpressionNodePrefix::~CExpressionNodePrefix()
{
}


PrefixNode CExpressionNodePrefix::GetPrefixNode()
{
	return m_prefixNode;
}

void CExpressionNodePrefix::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Prefix " << endl;

	m_prefixNode->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CExpressionNodePrefix::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_prefixNode->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;
    m_prefixNode->GenerateSymbolTables(m_localSymbolTable);
}

string CExpressionNodePrefix::GetExpressionType()
{
    return m_prefixNode->GetPrefixType();
}

Value* CExpressionNodePrefix::Codegen(IRBuilder<>* builder)
{
	return m_prefixNode->Codegen(builder);
}


