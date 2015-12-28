#include "prefix_node_variable.h"
#include "name_node.h"

CPrefixNodeVariable::CPrefixNodeVariable(VariableNode variableNode)
{
	m_variableNode = variableNode;
}

CPrefixNodeVariable::~CPrefixNodeVariable()
{
}

VariableNode CPrefixNodeVariable::GetVariableNode()
{
	return m_variableNode;
}


void CPrefixNodeVariable::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Prefix " << endl;

	m_variableNode->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}


void CPrefixNodeVariable::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_variableNode->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_variableNode->GenerateSymbolTables(m_localSymbolTable);
}

string CPrefixNodeVariable::GetPrefixType()
{
    NameNode varNodeName = ((VariableNodeName)m_variableNode)->GetName();

    if (varNodeName->GetNodeType() == NAME_NODE_TYPE)
    {
        string variableNameStr = varNodeName->GetValue();

        SymbolTableNode symbolTable = m_localSymbolTable->FindSymbolTableInLexicalScope(variableNameStr, UNKNOWN_ENTRY_TYPE);

        if (symbolTable)
        {
            string symbolType = symbolTable->GetVariableTypeByName(variableNameStr);

            if (symbolType == "" || variableNameStr == UNKNOWN_ENTRY_TYPE)
            {
                EXIT_WITH_ERROR(variableNameStr + " is not defined in the current lexical scope. The value is empty or Unknown.");
            }

            return symbolType;
        }
        else
        {
            EXIT_WITH_ERROR(variableNameStr + " is not defined in the current lexical scope.");
        }
    }
    else
    {
        EXIT_WITH_ERROR("Only Name types are supported for inference, no arrays or complex types.");
    }

}

Value* CPrefixNodeVariable::Codegen(IRBuilder<>* builder)
{
	return m_variableNode->Codegen(builder, false);
}
