#include "field_node.h"

CFieldNode::CFieldNode()
{
}

CFieldNode::~CFieldNode()
{
}

void CFieldNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}
