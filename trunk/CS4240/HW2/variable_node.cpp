#include "variable_node.h"

CVariableNode::CVariableNode()
{
}

CVariableNode::~CVariableNode()
{
}

void CVariableNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}
