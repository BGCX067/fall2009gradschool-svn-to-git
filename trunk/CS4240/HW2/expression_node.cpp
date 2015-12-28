#include "expression_node.h"

CExpressionNode::CExpressionNode()
{
}

CExpressionNode::~CExpressionNode()
{
}

void CExpressionNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}

