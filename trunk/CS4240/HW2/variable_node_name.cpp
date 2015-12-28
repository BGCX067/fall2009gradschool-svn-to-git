#include "variable_node_name.h"

CVariableNodeName::CVariableNodeName(NameNode name)
{
	m_name = name;
}

CVariableNodeName::~CVariableNodeName()
{
}

NameNode CVariableNodeName::GetName()
{
	return m_name;
}

void CVariableNodeName::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Variable " << endl;

	m_name->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CVariableNodeName::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_name->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_name->GenerateSymbolTables(m_localSymbolTable);
}

list<BaseNode> CVariableNodeName::GetChildren()
{
    list<BaseNode> children;
    children.push_front(m_name);
    return children;
}

Value* CVariableNodeName::Codegen(IRBuilder<>* builder, bool locationOnly)
{
	return m_name->Codegen(builder, locationOnly);
}


