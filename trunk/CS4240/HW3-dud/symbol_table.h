#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include "error_handling.h"

#include "variable_info.h"



class CStatementNode;
class CFunctionBodyNode;

using namespace std;

// Never use a literal for
// the symbol type, use these
// macros.

// Insert types just tell the insert function
// What map to use.
#define FUNCTION_INSERT_TYPE          "FUNCTION"

// Entry types are the actual types stored in the table.
#define UNKNOWN_ENTRY_TYPE            "UNKNOWN"
#define VAR_NIL_ENTRY_TYPE            "NULL"
#define VAR_BOOLEAN_ENTRY_TYPE        "BOOLEAN"
#define VAR_NUMBER__ENTRY_TYPE        "NUMBER"
#define VAR_STRING__ENTRY_TYPE        "STRING"

typedef map<string, string>        SymbolMap;
typedef map<string, CStatementNode*> StatementNodeMap;
typedef map<string, Value*> LLVMValueMap;

void PrintSymbolMap(SymbolMap symbolMap);
// void PrintFunctionNodeMap(FunctionNodeMap symbolMap);


class CSymbolTableNode
{
public:


	CSymbolTableNode();
    CSymbolTableNode(CFunctionBodyNode* functionIn);
	CSymbolTableNode(CFunctionBodyNode* functionIn, CSymbolTableNode* parent);
	CSymbolTableNode(CSymbolTableNode* parent);
	virtual ~CSymbolTableNode();

	list<CSymbolTableNode*> GetTablesInSameFunction();

    void setParent(CSymbolTableNode* parent);
	void insertChildTable(CSymbolTableNode* child);
    void UpdateLLVMValue(string name, Value* value);
	Value* GetLLVMValue(string name);
    void UpdateLocalValueType(string name, string type);
    void UpdateFunctionType(string name, string type);
    bool insertFunctionEntry(string name, CStatementNode* statement);
	bool insertTableEntry(string name, string type);
	bool checkTable(string name, string type);
	int getChildCount();
    list<pair<string, string> > GetFunctionSymbols();
    list<pair<string, string> > GetVariableSymbols();
    vector<CSymbolTableNode*> GetChildren();
    CSymbolTableNode*  GetParent() { return parent; }
	void PrintSymbolTableHierarchy();
    string GetVariableTypeByName(string name);
    string GetFunctionTypeByName(string name);
    CSymbolTableNode* FindSymbolTableInLexicalScope_Function(string symbol);
    CSymbolTableNode* FindSymbolTableInLexicalScope(string symbol, string type);
    CStatementNode* GetFunctionStatementByName(string name);

	CFunctionBodyNode* functionIn;
	CSymbolTableNode*  parent;

private:


    LLVMValueMap valueMap;
    StatementNodeMap functionNodeMap;
	SymbolMap functionSymbolTable;
	SymbolMap variableSymbolTable;
	vector<CSymbolTableNode*> children;
};

typedef CSymbolTableNode* SymbolTableNode;

#endif // SYMBOL_TABLE_H
