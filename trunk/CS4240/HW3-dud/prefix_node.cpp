#include "prefix_node.h"

CPrefixNode::CPrefixNode()
{
}

CPrefixNode::~CPrefixNode()
{
}

void CPrefixNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}
