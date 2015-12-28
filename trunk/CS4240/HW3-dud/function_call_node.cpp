#include "function_call_node.h"

CFunctionCallNode::CFunctionCallNode(PrefixNode prefix, ExpressionNodeList args)
{
	m_args = args;
	m_prefix = prefix;
}

CFunctionCallNode::~CFunctionCallNode()
{
}


ExpressionNodeList CFunctionCallNode::GetArguments()
{
	return m_args;
}

PrefixNode CFunctionCallNode::GetPrefix()
{
	return m_prefix;
}

void CFunctionCallNode::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( FunctionCall " << endl;

	m_prefix->PrintNode(file, tabCount+1);

	ExpressionNodeIter it;
	for (it=m_args->begin(); it!=m_args->end(); it++)
	{
		ExpressionNode expression = *it;
		expression->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CFunctionCallNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_prefix->GenerateSymbolTables(NULL);

        for (list<ExpressionNode>::iterator childIter = m_args->begin(); childIter != m_args->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_prefix->GenerateSymbolTables(m_localSymbolTable);

    for (list<ExpressionNode>::iterator childIter = m_args->begin(); childIter != m_args->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }
}

Value* CFunctionCallNode::Codegen(IRBuilder<>* builder)
{
	NameNode functionName = m_prefix->GetNameNode();
	if (functionName == NULL)
	{
		std::cout << "only var node expression supported for function call" << endl;
	}

	//evaluate expressions to pass to function
	vector<Value*> expressionValues;
	ExpressionNodeIter it;
	for (it=m_args->begin(); it!=m_args->end(); it++)
	{
		ExpressionNode expression = *it;
		Value* val = expression->Codegen(builder);
		expressionValues.push_back(val);
	}


	//special case print function
	if (functionName->GetValue().compare("print") == 0)
	{
		Value* param = expressionValues[0];

		//make sure its a string
		if (param->getType() == Type::DoubleTy)
		{
			//create a space for a string to hold the result
			Value* paramToStr = builder->CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT));
			//call to string
		    Value* doubleToString = CLlvmGenerator::GetInstance()->GetToStringFunction();
			builder->CreateCall2(doubleToString, param, paramToStr);
			//use the converted type
			param = paramToStr;
		}

		//call print function
		Value* printFunction = CLlvmGenerator::GetInstance()->GetPrintFunction();
		return builder->CreateCall(printFunction, param);
	}
	else
	{
		SymbolTableNode table = m_localSymbolTable->FindSymbolTableInLexicalScope_Function(functionName->GetValue());

		Value* function = table->GetLLVMValue(functionName->GetValue());


		if (function == NULL)
		{
			std::cout << "Function " << functionName->GetValue() << " not found." << endl;
		}


		return builder->CreateCall<vector<Value*>::iterator>(function, expressionValues.begin(), expressionValues.end());
	}



}

