#include "expression_node_binary_operation.h"

CExpressionNodeBinaryOperation::CExpressionNodeBinaryOperation(BinaryOperationType type, ExpressionNode left, ExpressionNode right)
{
	m_type = type;
	m_left = left;
	m_right = right;
}

CExpressionNodeBinaryOperation::~CExpressionNodeBinaryOperation()
{
}



BinaryOperationType CExpressionNodeBinaryOperation::GetType()
{
	return m_type;
}

ExpressionNode CExpressionNodeBinaryOperation::GetLeft()
{
	return m_left;
}

ExpressionNode CExpressionNodeBinaryOperation::GetRight()
{
	return m_right;
}

string CExpressionNodeBinaryOperation::GetTypeAsString()
{
	if (m_type == Plus)
		return "Plus";
	else if (m_type == Minus)
		return "Minus";
	else if (m_type == Times)
		return "Times";
	else if (m_type == Divide)
		return "Divide";
	else if (m_type == Raise)
		return "Raise";
	else if (m_type == Modulus)
		return "Modulus";
	else if (m_type == Concat)
		return "Concat";
	else if (m_type == Less)
		return "Less";
	else if (m_type == LessEqual)
		return "LessEqual";
	else if (m_type == More)
		return "More";
	else if (m_type == MoreEqual)
		return "MoreEqual";
	else if (m_type == Equal)
		return "Equal";
	else if (m_type == NotEqual)
		return "NotEqual";
	else if (m_type == And)
		return "And";
	else if (m_type == Or)
		return "Or";
	else
		return "??";
}



void CExpressionNodeBinaryOperation::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Binop " << m_linenum << endl;

	m_left->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount+1);
	file << "( " << this->GetTypeAsString() << " )" << endl;

	m_right->PrintNode(file, tabCount+1);


	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CExpressionNodeBinaryOperation::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_left->GenerateSymbolTables(NULL);
        m_right->GenerateSymbolTables(NULL);
        return;
    }

    m_localSymbolTable = parent;
    m_left->GenerateSymbolTables(m_localSymbolTable);
    m_right->GenerateSymbolTables(m_localSymbolTable);
}

string CExpressionNodeBinaryOperation::GetExpressionType()
{
    string leftExpType = m_left->GetExpressionType();
    string rightExpType = m_right->GetExpressionType();

	if (m_type == Plus)
		return VAR_NUMBER__ENTRY_TYPE;
	else if (m_type == Minus)
		return VAR_NUMBER__ENTRY_TYPE;
	else if (m_type == Times)
		return VAR_NUMBER__ENTRY_TYPE;
	else if (m_type == Divide)
		return VAR_NUMBER__ENTRY_TYPE;
	else if (m_type == Raise)
		return VAR_NUMBER__ENTRY_TYPE;
	else if (m_type == Modulus)
		return VAR_NUMBER__ENTRY_TYPE;
	else if (m_type == Concat)
		return VAR_STRING__ENTRY_TYPE;
	else if (m_type == Less)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == LessEqual)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == More)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == MoreEqual)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == Equal)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == NotEqual)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == And)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else if (m_type == Or)
		return VAR_BOOLEAN_ENTRY_TYPE;
	else
		return VAR_BOOLEAN_ENTRY_TYPE;

//    if (leftExpType.compare(rightExpType) == 0)
//    {
//        switch (m_type)
//        {
//			case Concat: return VAR_STRING__ENTRY_TYPE;

//			case Less:
//			case LessEqual:
//			case More:
//			case MoreEqual:
//			case Equal:
//			case NotEqual:
//			case And:
//			case Or: return VAR_BOOLEAN_ENTRY_TYPE;
//			default: return leftExpType;
//		}
//    }
//    else
//    {
//		 switch (m_type)
//        {
//			case Concat: return VAR_STRING__ENTRY_TYPE;

//			case Less:
//			case LessEqual:
//			case More:
//			case MoreEqual:
//			case Equal:
//			case NotEqual:
//			case And:
//			case Or: return VAR_BOOLEAN_ENTRY_TYPE;
//			default: return leftExpType;
//		}
//        EXIT_WITH_ERROR("We do not currently support mixed type expressions.  left:" << leftExpType << "  right:" << rightExpType << "  type:" << m_type);
//    }
}

Value* CExpressionNodeBinaryOperation::Codegen(IRBuilder<>* builder)
{

	Value* left = m_left->Codegen(builder);
	Value* right = m_right->Codegen(builder);

//	std::cout << "left";
//	left->getType()->print(std::cout);
//	std::cout << endl;

//	std::cout << "right";
//	right->getType()->print(std::cout);
//	std::cout << endl;

	if (m_type == Plus)
	{
		return builder->CreateAdd(left, right);
	}
	else if (m_type == Minus)
	{
		return builder->CreateSub(left, right);
	}
	else if (m_type == Times)
	{
		return builder->CreateMul(left, right);
	}
	else if (m_type == Divide)
	{
		return builder->CreateFDiv(left, right);
	}
	else if (m_type == Raise)
	{
		std::cout << "EXPRESSION Raise NOT YET IMPLEMENTED" << endl;
	}
	else if (m_type == Modulus)
	{
		return builder->CreateFRem(left, right);
	}
	else if (m_type == Concat)
	{
		Value* concatFunction = CLlvmGenerator::GetInstance()->GetConcatFunction();
		Value* doubleToString = CLlvmGenerator::GetInstance()->GetToStringFunction();

		if (left->getType() == Type::DoubleTy)
		{
			//create a space for a string to hold the result
			Value* leftToStr = builder->CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT));
			//call to string
			builder->CreateCall2(doubleToString, left, leftToStr);
			//use the converted type
			left = leftToStr;
		}
		if (right->getType() == Type::DoubleTy)
		{
			//create a space for a string to hold the result
			Value* rightToStr = builder->CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT));
			//call to string
			builder->CreateCall2(doubleToString, right, rightToStr);
			//use the converted type
			right = rightToStr;
		}

		//create a space for a string to hold the result
		Value* strRet = builder->CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT));

		//call concatination function
		builder->CreateCall3(concatFunction, left, right, strRet);

		return strRet;
	}
	else if (m_type == Less)
	{
		return builder->CreateFCmpOLT(left, right);
	}
	else if (m_type == LessEqual)
	{
		return builder->CreateFCmpOLE(left, right);
	}
	else if (m_type == More)
	{
		return builder->CreateFCmpOGT(left, right);
	}
	else if (m_type == MoreEqual)
	{
		return builder->CreateFCmpOGE(left, right);
	}
	else if (m_type == Equal)
	{
		return builder->CreateFCmpOEQ(left, right);
	}
	else if (m_type == NotEqual)
	{
		return builder->CreateFCmpONE(left, right);
	}
	else if (m_type == And)
	{
		return builder->CreateAnd(left, right);
	}
	else if (m_type == Or)
	{
		return builder->CreateOr(left, right);
	}
	else
	{
		std::cout << "EXPRESSION UNKNOWN" << endl;
	}


	return NULL;
}

