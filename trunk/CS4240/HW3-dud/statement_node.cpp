#include "statement_node.h"

CStatementNode::CStatementNode()
{
}

CStatementNode::~CStatementNode()
{
}

void CStatementNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}
