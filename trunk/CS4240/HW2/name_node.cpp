#include "name_node.h"
#include <string>
using namespace std;


CNameNode::CNameNode(string value, int linenum)
{
    m_value = value;
	m_linenum = linenum;
}

CNameNode::CNameNode(yyvalType* yyvaltype)
{
    m_value = string(yyvaltype->value);
	m_linenum = yyvaltype->linenum;
}
CNameNode::~CNameNode()
{
}


string CNameNode::GetValue()
{
	return m_value;
}

void CNameNode::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( " << m_value << " )" << endl;
}

void CNameNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}


Value* CNameNode::Codegen(IRBuilder<>* builder, bool locationOnly)
{
	//std::cout << "Var " << m_name->GetValue() << "     locOnly: " << locationOnly << endl;

	Value* varLoc = NULL;


	//get symbol table the var is in
	SymbolTableNode table = m_localSymbolTable->FindSymbolTableInLexicalScope(m_value, "");

	if (table != NULL)
	{
		varLoc = table->GetLLVMValue(m_value);

		//determine if the variable is a string
		//with strings we always want the location and not the var
		if(table->GetVariableTypeByName(m_value).compare(VAR_STRING__ENTRY_TYPE) == 0)
		{
			locationOnly = true;
		}
	}


	if (varLoc == NULL)
	{
		std::cout << "variable not found: " << m_value << endl;
	}


	/*
	global strings are of type [100 x i8]* they need to be of type i8* (point to the first element)
	took me like 2 hours to figure out how to get that to happen i think this works.  The following
	c code run with llvm-gcc leads me to belive it should:  "char a[5];  char* c;  c = a;"
	*/
	if (varLoc->getType()->getNumContainedTypes() != 0)
	{
		if (varLoc->getType()->getContainedType(0)->getTypeID() == Type::ArrayTyID)
		{
			varLoc = builder->CreateBitCast(varLoc, PointerType::getUnqual(Type::Int8Ty));
		}
	}

	
	if (locationOnly)
	{		
		return varLoc;
	}
	else
	{
		LoadInst* load = builder->CreateLoad(varLoc);
		return load;
	}
}


