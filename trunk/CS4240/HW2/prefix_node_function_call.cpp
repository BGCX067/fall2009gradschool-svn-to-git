#include "prefix_node_function_call.h"
#include "statement_node_function_definition.h"

CPrefixNodeFunctionCall::CPrefixNodeFunctionCall(FunctionCallNode functionCall)
{
	m_functionCall = functionCall;
}

CPrefixNodeFunctionCall::~CPrefixNodeFunctionCall()
{
}


FunctionCallNode CPrefixNodeFunctionCall::GetFunctionCall()
{
	return m_functionCall;
}

void CPrefixNodeFunctionCall::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Prefix " << endl;

	m_functionCall->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}


void CPrefixNodeFunctionCall::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_functionCall->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;
    m_functionCall->GenerateSymbolTables(m_localSymbolTable);
}

string CPrefixNodeFunctionCall::GetPrefixType()
{
    // XXX
    NameNode functionNameNode =
        ((VariableNodeName)
            (((PrefixNodeVariable)
                (m_functionCall->GetPrefix()))->GetVariableNode()))->GetName();

    if (functionNameNode->GetNodeType() == NAME_NODE_TYPE)
    {
        // Get Prefix Node then Name
        string functionNameStr = functionNameNode->GetValue();

        SymbolTableNode symbolTable = m_localSymbolTable->FindSymbolTableInLexicalScope_Function(functionNameStr);
        goto checktable;

        argmismatch:
        if (NULL != symbolTable->GetParent())
        {
                symbolTable = symbolTable->GetParent()->FindSymbolTableInLexicalScope_Function(functionNameStr);
        }
        else
        {
            EXIT_WITH_ERROR("Arguments to function " + functionNameStr + " have already been infered. There is a miss match between the definition and the call.");
        }

        checktable:
        if (symbolTable)
        {
            string symbolType = symbolTable->GetFunctionTypeByName(functionNameStr);

            if (symbolType == "")
            {
                EXIT_WITH_ERROR("SymbolTable returned an empty type for function " + functionNameStr);
            }
            else if (symbolType == UNKNOWN_ENTRY_TYPE)
            {
                StatementNode statement = symbolTable->GetFunctionStatementByName(functionNameStr);

                // Update function param types
                SymbolTableNode functionSymbolTable = ((StatementNodeFunctionDefinition)statement)->GetFunctionBody()->GetLocalSymbolTable();
                ExpressionNodeList functionCallArgs = m_functionCall->GetArguments();
                NameNodeList functionDefParams = ((StatementNodeFunctionDefinition)statement)->GetFunctionBody()->GetParameters();


                if (functionCallArgs->size() != functionDefParams->size())
                {
                    goto argmismatch;
                }

                list<ExpressionNode>::iterator calArgIter = functionCallArgs->begin();
                list<NameNode>::iterator defParamIter = functionDefParams->begin();

//                 std::cout << "Function args: ";

                for (;
                     calArgIter != functionCallArgs->end() &&
                     defParamIter != functionDefParams->end();
                     calArgIter++,
                     defParamIter++)
                {


                    string callArgType = (*calArgIter)->GetExpressionType();
                    string defParamName = (*defParamIter)->GetValue();

//                     std::cout << callArgType << "(" << defParamName <<  ")" << ", ";

                    functionSymbolTable->UpdateLocalValueType(defParamName, callArgType);
                }

                ((StatementNodeFunctionDefinition)statement)->GetFunctionBody()->GetBlock()->GenerateSymbolTables(NULL);
                /*
                SymbolTableNode functionChunkSymbolTable = ((StatementNodeFunctionDefinition)statement)->GetFunctionBody()->GetBlock()->GetLocalSymbolTable();
                list<pair<string, string> > functionVarSymbols = functionChunkSymbolTable->GetVariableSymbols();
//                 vector<CSymbolTableNode*> functionSymbolChildren =  functionSymbolTable->GetChildren();

                std::cout << std::endl << "Function Variable Symbols For " << functionNameStr << std::endl;
                for (list<pair<string, string> >::iterator functionVarIter = functionVarSymbols.begin();
                     functionVarIter != functionVarSymbols.end();
                     functionVarIter++)
                {
                    std::cout << "First: " << functionVarIter->first << " " << "Second: " << functionVarIter->second << std::endl;
                }*/

//                 std::cout << std::endl;

                // Update function type (return value) in symbol table
                string functionReturnType = statement->GetStatementType();
                symbolTable->UpdateFunctionType(functionNameStr, functionReturnType);
                return functionReturnType;
            }
            else
            // Real type checking
            {
                StatementNode statement = symbolTable->GetFunctionStatementByName(functionNameStr);

                // Update function param types
                SymbolTableNode functionSymbolTable = ((StatementNodeFunctionDefinition)statement)->GetFunctionBody()->GetLocalSymbolTable();
                ExpressionNodeList functionCallArgs = m_functionCall->GetArguments();
                NameNodeList functionDefParams = ((StatementNodeFunctionDefinition)statement)->GetFunctionBody()->GetParameters();

                list<ExpressionNode>::iterator calArgIter = functionCallArgs->begin();
                list<NameNode>::iterator defParamIter = functionDefParams->begin();

//                 std::cout << "Function args: ";


                if (functionCallArgs->size() != functionDefParams->size())
                {
                    goto argmismatch;
                }

                for (;
                      calArgIter != functionCallArgs->end() &&
                      defParamIter != functionDefParams->end();
                      calArgIter++,
                      defParamIter++)
                {


                    string callArgType = (*calArgIter)->GetExpressionType();
                    string defParamName = (*defParamIter)->GetValue();

//                     std::cout << callArgType << "(" << defParamName <<  ")" << ", ";


                    if (functionSymbolTable->GetVariableTypeByName(defParamName) !=
                        callArgType)
                    {
                        EXIT_WITH_ERROR("Arguments to function " + functionNameStr + " have already been infered. There is a miss match between the definition and the call.");
                    }

//                     functionSymbolTable->UpdateLocalValueType(defParamName, callArgType);
                }
            }

            return symbolType;
        }
        else
        {
            EXIT_WITH_ERROR(functionNameStr + " is not defined in the current lexical scope.");
        }
    }
    else
    {
        EXIT_WITH_ERROR("Only Name types are supported for inference, no arrays or complex types.");
    }
}

Value* CPrefixNodeFunctionCall::Codegen(IRBuilder<>* builder)
{
	return m_functionCall->Codegen(builder);
}


