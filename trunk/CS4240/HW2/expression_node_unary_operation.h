#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_UNARY_OPERATION_H
#define EXPRESSION_NODE_UNARY_OPERATION_H


#include "base_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

#include "llvm_generator.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

enum UnaryOperationType
{
	Negate, Not, Lenght
};

class CExpressionNodeUnaryOperation : public CExpressionNode
{
    public:

        CExpressionNodeUnaryOperation(UnaryOperationType type, ExpressionNode expression);
        virtual ~CExpressionNodeUnaryOperation();

		UnaryOperationType GetType();
		ExpressionNode GetExpression();

		string GetTypeAsString();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();

		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:
		UnaryOperationType m_type;
		ExpressionNode m_expression;


};

typedef CExpressionNodeUnaryOperation* ExpressionNodeUnaryOperation;
typedef list<ExpressionNodeUnaryOperation> CExpressionNodeUnaryOperationList;
typedef CExpressionNodeUnaryOperationList* ExpressionNodeUnaryOperationList;
typedef CExpressionNodeUnaryOperationList::iterator ExpressionNodeUnaryOperationIter;



#endif // EXPRESSION_NODE_UNARY_OPERATION_H

