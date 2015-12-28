#include "expression_node_unary_operation.h"

CExpressionNodeUnaryOperation::CExpressionNodeUnaryOperation(UnaryOperationType type, ExpressionNode expression)
{
	m_type = type;
	m_expression = expression;
}

CExpressionNodeUnaryOperation::~CExpressionNodeUnaryOperation()
{
}



UnaryOperationType CExpressionNodeUnaryOperation::GetType()
{
	return m_type;
}

ExpressionNode CExpressionNodeUnaryOperation::GetExpression()
{
	return m_expression;
}


string CExpressionNodeUnaryOperation::GetTypeAsString()
{
	if (m_type == Negate)
		return "Negate";
	else if (m_type == Not)
		return "Not";
	else if (m_type == Lenght)
		return "Lenght";
	else
		return "??";
}


void CExpressionNodeUnaryOperation::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Unop " << m_linenum << endl;

	PrintTabs(file, tabCount+1);
	file << "( " << this->GetTypeAsString() << " )" << endl;

	m_expression->PrintNode(file, tabCount+1);


	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CExpressionNodeUnaryOperation::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_expression->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;
    m_expression->GenerateSymbolTables(m_localSymbolTable);
}

string CExpressionNodeUnaryOperation::GetExpressionType()
{
    switch(m_type)
    {
        case Negate: return VAR_NUMBER__ENTRY_TYPE;
        case Not: return VAR_BOOLEAN_ENTRY_TYPE;
        case Lenght: return VAR_NUMBER__ENTRY_TYPE;
        default: EXIT_WITH_ERROR("Invalid unop.");
    }
}

Value* CExpressionNodeUnaryOperation::Codegen(IRBuilder<>* builder)
{

	Value* exp = m_expression->Codegen(builder);

	if (m_type == Negate)
	{
		return builder->CreateNeg(exp);
	}
	else if (m_type == Not)
	{
		return builder->CreateNot(exp);
	}
	else if (m_type == Lenght)
	{
		//call lenght function
		Value* lenghtFunction = CLlvmGenerator::GetInstance()->GetLenghtFunction();
		Value* lenInt = builder->CreateCall(lenghtFunction, exp);
		Value* lenDouble = builder->CreateSIToFP(lenInt, Type::DoubleTy);
		return lenDouble;
	}
	else
	{
		std::cout << "EXPRESSION UNKNOWN" << endl;
	}

	return NULL;
}


