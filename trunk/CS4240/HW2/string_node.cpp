#include "string_node.h"
#include <string>
using namespace std;

CStringNode::CStringNode(string value, int linenum)
{
    m_value = value;
	m_linenum = linenum;
}
CStringNode::CStringNode(yyvalType* yyvaltype)
{
    m_value = string(yyvaltype->value);
	m_linenum = yyvaltype->linenum;
}
CStringNode::~CStringNode()
{
}


string CStringNode::GetValue()
{
	return m_value;
}


void CStringNode::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( StrNode " << m_value << " )" << endl;
}

void CStringNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}


Value* CStringNode::Codegen(IRBuilder<>* builder)
{
	//alocate space for the string
	Value* strStart = builder->CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT), "stringConstant");	
	int offsetCount = 0;


	//add each character to string
	string::iterator it;
  	for (it = m_value.begin(); it < m_value.end(); it++)
	{
    	char chr = *it;
		Value* chrVal = ConstantInt::get(Type::Int8Ty, chr);
		Value* offsetVal = ConstantInt::get(Type::Int32Ty, offsetCount);		
		Value* offsetPtr = builder->CreateGEP(strStart, offsetVal);
		//store the char at that position
		builder->CreateStore(chrVal, offsetPtr);

		offsetCount += 1;
	}

	//add null terminator to string
	Value* chrValNullTerm = ConstantInt::get(Type::Int8Ty, 0);
	Value* offsetValNullTerm = ConstantInt::get(Type::Int32Ty, offsetCount);		
	Value* offsetPtrNullTerm = builder->CreateGEP(strStart, offsetValNullTerm);
	//store the char at that position
	builder->CreateStore(chrValNullTerm, offsetPtrNullTerm);


	return strStart;
}



