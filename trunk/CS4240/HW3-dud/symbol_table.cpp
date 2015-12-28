#include <iostream>
#include <string>
#include <stdlib.h>
#include <utility>
#include "symbol_table.h"

CSymbolTableNode globalSymbolTable;

using namespace std;

CSymbolTableNode::CSymbolTableNode(CFunctionBodyNode* functionIn, CSymbolTableNode* parent)
{
    // TODO: Check for NULL
	this->functionIn = functionIn;
    this->parent = parent;
}

CSymbolTableNode::CSymbolTableNode(CSymbolTableNode* parent)
{
	this->functionIn = NULL;
    this->parent = parent;
}

CSymbolTableNode::CSymbolTableNode(CFunctionBodyNode* functionIn)
{
	this->functionIn = functionIn;
    this->parent = NULL;
}

CSymbolTableNode::CSymbolTableNode()
{
	this->functionIn = NULL;
    this->parent = NULL;
}

CSymbolTableNode::~CSymbolTableNode()
{
    this->parent = NULL;
    this->children.clear();
}


list<CSymbolTableNode*> CSymbolTableNode::GetTablesInSameFunction()
{

	//add self to list
	list<CSymbolTableNode*> toRet;
	toRet.push_back(this);

	if (this->functionIn != NULL)
	{
		//go through all my children
		vector<CSymbolTableNode*>::iterator it;
		for (it = children.begin(); it != children.end(); it++)
		{

			//if its in the same function as me
			CSymbolTableNode* childTable = *it;
			if (childTable->functionIn == this->functionIn)
			{
			
				//get the tables in same function as it and add them too
				list<CSymbolTableNode*> childSame = childTable->GetTablesInSameFunction();			
				list<CSymbolTableNode*>::iterator it2;
				for (it2 = childSame.begin(); it2 != childSame.end(); it2++)
				{
					toRet.push_back(*it2);
				}
			}
		}
	}

	return toRet;
}


void CSymbolTableNode::setParent(CSymbolTableNode* parent)
{
    // TODO: Check for NULL

    this->parent = parent;
}

int CSymbolTableNode::getChildCount()
{
    return this->children.size();
}

void CSymbolTableNode::insertChildTable(SymbolTableNode child)
{
    if (NULL == child) return ; // TODO: Throw Exception

    this->children.push_back(child);
}



//Returns true if the name was already in the table
bool CSymbolTableNode::insertFunctionEntry(string name, CStatementNode* statement)
{
    if (this->checkTable(name, FUNCTION_INSERT_TYPE))
    {
        //Already in the table
        return true;
    }

    this->functionSymbolTable.insert(pair<string, string>(name, UNKNOWN_ENTRY_TYPE));
    this->functionNodeMap.insert(pair<string, CStatementNode*>(name, statement));



    this->valueMap.insert(pair<string, Value*>(name, NULL));

    return false;
}


//Returns true if the name was already in the table
bool CSymbolTableNode::insertTableEntry(string name, string type)
{
    if (this->checkTable(name, type))
    {
        //Already in the table
        return true;
    }

    if (FUNCTION_INSERT_TYPE == type)
    {
        this->functionSymbolTable.insert(pair<string, string>(name, UNKNOWN_ENTRY_TYPE));
    }
    else
    {
        this->variableSymbolTable.insert(pair<string, string>(name, type));
    }


    this->valueMap.insert(pair<string, Value*>(name, NULL));

    return false;
}

//Returns true if the name is in the appropriate table
bool CSymbolTableNode::checkTable(string name, string type)
{
    SymbolMap::iterator iter;

    if (FUNCTION_INSERT_TYPE == type)
    {
        iter = this->functionSymbolTable.find(name);

        if (iter != this->functionSymbolTable.end())
        {
            //We found it!
//             EXIT_WITH_ERROR("Multiple functions with same name found. Exiting...");
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        iter = this->variableSymbolTable.find(name);

        if (iter != this->variableSymbolTable.end())
        {
            //We found it!
/*            if(iter->second != UNKNOWN_ENTRY_TYPE && iter->second != type)
            {
            	EXIT_WITH_ERROR("Attempted to redefine variable with type defined to another type. Exiting...");
            }*/
            return true;
        }
        else
        {
            return false;
        }
    }
}

CStatementNode* CSymbolTableNode::GetFunctionStatementByName(string name)
{
    StatementNodeMap::iterator iter = this->functionNodeMap.find(name);

    if (iter != this->functionNodeMap.end())
    {
        CStatementNode* statement = (*iter).second;
        return statement;
//         return statement->GetStatementType();
    }
    else
    {
        return NULL;
    }
}

string CSymbolTableNode::GetFunctionTypeByName(string name)
{
    SymbolMap::iterator iter = this->functionSymbolTable.find(name);

    if (iter != this->functionSymbolTable.end())
    {
        if ((*iter).second == UNKNOWN_ENTRY_TYPE)
        {
            return UNKNOWN_ENTRY_TYPE;

//             (*iter).second = GetFunctionStatementByName(name)->GetStatementType();

//             return GetFunctionStatementByName(name)->GetStatementType();

//             StatementNodeMap::iterator functioNodeMapIter =
//                 this->functionNodeMap.find(name);
//
//             CStatementNode* functionNode = (*functioNodeMapIter).second;
        }
        else
        {
            return (*iter).second;
        }
    }
    else
    {
        return "";
    }

}

void CSymbolTableNode::UpdateLLVMValue(string name, Value* value)
{
    LLVMValueMap::iterator iter = this->valueMap.find(name);

    if (iter != this->valueMap.end())
    {
        this->valueMap[name] = value;
    }
}

Value* CSymbolTableNode::GetLLVMValue(string name)
{
    LLVMValueMap::iterator iter = this->valueMap.find(name);

    if (iter != this->valueMap.end())
    {
        return this->valueMap[name];
    }
	return NULL;
}

void CSymbolTableNode::UpdateLocalValueType(string name, string type)
{
    SymbolMap::iterator iter = this->variableSymbolTable.find(name);

    if (iter != this->variableSymbolTable.end())
    {
        this->variableSymbolTable[name] = type;
    }
}

void CSymbolTableNode::UpdateFunctionType(string name, string type)
{
    SymbolMap::iterator iter = this->functionSymbolTable.find(name);

    if (iter != this->functionSymbolTable.end())
    {
        this->functionSymbolTable[name] = type;
    }
}

string CSymbolTableNode::GetVariableTypeByName(string name)
{
    SymbolMap::iterator iter = this->variableSymbolTable.find(name);

    if (iter != this->variableSymbolTable.end())
    {
        return (*iter).second;
    }
    else
    {
        return "";
    }
}

vector<CSymbolTableNode*> CSymbolTableNode::GetChildren()
{
    return this->children;
}

void CSymbolTableNode::PrintSymbolTableHierarchy()
{

    std::cout << "\n\n---------------------------" <<endl;

    if (this == &globalSymbolTable)
    std::cout << "The Global Symbol Table: " << endl;
    else
    std::cout << "A Local Symbol Table: " << endl;

    std::cout << "Function Table" << std::endl;
    std::cout << "name    " << "type    " << endl;
    PrintSymbolMap(this->functionSymbolTable);

	for (SymbolMap::iterator iter2 = functionSymbolTable.begin();
		 iter2 != functionSymbolTable.end();
		 iter2++)
	{
		std::cout << "LLVM_Val  " << (*iter2).first << " =   " << GetLLVMValue((*iter2).first) << endl;
	}

    std::cout << endl;

    std::cout << "Variable Table" << std::endl;
    std::cout << "name    " << "type    " << endl;
    PrintSymbolMap(this->variableSymbolTable);

    vector<CSymbolTableNode*> children = this->GetChildren();

    for (vector<CSymbolTableNode*>::iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        (*iter)->PrintSymbolTableHierarchy();
    }
}

void PrintSymbolMap(SymbolMap symbolMap)
{
    for (SymbolMap::iterator iter = symbolMap.begin();
		 iter != symbolMap.end();
		 iter++)
	{
		std::cout << (*iter).first << "        " << (*iter).second << endl;
	}
}

CSymbolTableNode* CSymbolTableNode::FindSymbolTableInLexicalScope_Function(string symbol)
{
    return this->FindSymbolTableInLexicalScope(symbol, FUNCTION_INSERT_TYPE);
}

CSymbolTableNode* CSymbolTableNode::FindSymbolTableInLexicalScope(string symbol, string type)
{
    if (this->checkTable(symbol, type))
    {
        return this;
    }

    for (SymbolTableNode currentSymbolTable = this->parent;
        currentSymbolTable;
        currentSymbolTable = currentSymbolTable->parent)
    {
        if (currentSymbolTable->checkTable(symbol, type))
        {
            return currentSymbolTable;
        }
    }

    return NULL;
}

list<pair<string, string> > CSymbolTableNode::GetFunctionSymbols()
{
    list<pair<string, string> > functionSymbolList;

    for (SymbolMap::iterator iter = functionSymbolTable.begin();
         iter != functionSymbolTable.end();
         iter++)
    {
        functionSymbolList.push_back(*iter);
    }

    return functionSymbolList;
}

list<pair<string, string> > CSymbolTableNode::GetVariableSymbols()
{
    list<pair<string, string> > variableSymbolList;

    for (SymbolMap::iterator iter = variableSymbolTable.begin();
         iter != variableSymbolTable.end();
         iter++)
    {
        variableSymbolList.push_back(*iter);
    }

    return variableSymbolList;
}

