#include "statement_node_funtion_call.h"
#include "statement_node_function_definition.h"

CStatementNodeFuntionCall::CStatementNodeFuntionCall(FunctionCallNode functionCall)
{
	m_functionCall = functionCall;
}

CStatementNodeFuntionCall::~CStatementNodeFuntionCall()
{
}

FunctionCallNode CStatementNodeFuntionCall::GetFunctionCall()
{
	return m_functionCall;
}


void CStatementNodeFuntionCall::PrintNode(ostream& file, int tabCount)
{
	m_functionCall->PrintNode(file, tabCount);
}

void CStatementNodeFuntionCall::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_functionCall->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_functionCall->GenerateSymbolTables(m_localSymbolTable);

    if (m_functionCall->GetPrefix()->GetNameNode()->GetValue() != "print")
    {
        // Ideal Code commented out.
       // m_functionCall->GetPrefix()->GetPrefixType();
        GetFunctionCallType(m_functionCall->GetPrefix()->GetNameNode()->GetValue());
    }
}

// XXX: This is a hack, because the prefix type of a function statement call
// is a variable, which calls the wrong prefix type.
string CStatementNodeFuntionCall::GetFunctionCallType(string functionName)
{

    // Get Prefix Node then Name
    string functionNameStr = functionName;

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

//                 std::cout << callArgType << "(" << defParamName <<  ")" << ", ";


                if (functionSymbolTable->GetVariableTypeByName(defParamName) !=
                    callArgType)
                {
                    EXIT_WITH_ERROR("Arguments to function " + functionNameStr + " have already been infered. There is a miss match between the definition and the call.");
                }

            }
        }

        return symbolType;
    }
    else
    {
        EXIT_WITH_ERROR(functionNameStr + " is not defined in the current lexical scope.");
    }

}



BasicBlock* CStatementNodeFuntionCall::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	IRBuilder<> builder(block);
	m_functionCall->Codegen(&builder);
	return block;
}

