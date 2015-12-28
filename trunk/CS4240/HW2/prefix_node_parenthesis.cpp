#include "prefix_node_parenthesis.h"

CPrefixNodeParenthesis::CPrefixNodeParenthesis(ExpressionNode expressionNode)
{
	m_expressionNode = expressionNode;
}

CPrefixNodeParenthesis::~CPrefixNodeParenthesis()
{
}


ExpressionNode CPrefixNodeParenthesis::GetExpressionNode()
{
	return m_expressionNode;
}


void CPrefixNodeParenthesis::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Prefix Paren " << endl;

	m_expressionNode->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CPrefixNodeParenthesis::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_expressionNode->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_expressionNode->GenerateSymbolTables(m_localSymbolTable);
}

string CPrefixNodeParenthesis::GetPrefixType()
{
    return m_expressionNode->GetExpressionType();
}

Value* CPrefixNodeParenthesis::Codegen(IRBuilder<>* builder)
{
	return m_expressionNode->Codegen(builder);
}
