#include "variable_node_prefix_bracket.h"

CVariableNodePrefixBracket::CVariableNodePrefixBracket(PrefixNode prefix, ExpressionNode expression)
{
	m_prefix = prefix;
	m_expression = expression;
}

CVariableNodePrefixBracket::~CVariableNodePrefixBracket()
{
}


PrefixNode CVariableNodePrefixBracket::GetPrefix()
{
	return m_prefix;
}

ExpressionNode CVariableNodePrefixBracket::GetExpression()
{
	return m_expression;
}



void CVariableNodePrefixBracket::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Variable " << endl;

	m_prefix->PrintNode(file, tabCount+1);
	m_expression->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CVariableNodePrefixBracket::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_prefix->GenerateSymbolTables(NULL);
        m_expression->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_prefix->GenerateSymbolTables(m_localSymbolTable);
    m_expression->GenerateSymbolTables(m_localSymbolTable);
}

list<BaseNode> CVariableNodePrefixBracket::GetChildren()
{
    list<BaseNode> children;
    children.push_front(m_prefix);
    children.push_front(m_expression);
    return children;
}


Value* CVariableNodePrefixBracket::Codegen(IRBuilder<>* builder, bool locationOnly)
{
	std::cout << "arrays are NOT supported" << endl;
	return NULL;
}



