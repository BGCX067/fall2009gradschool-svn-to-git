#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_BINARY_OPERATION_H
#define EXPRESSION_NODE_BINARY_OPERATION_H


#include "base_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>

#include "llvm_generator.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;


enum BinaryOperationType
{
	Plus, Minus, Times, Divide, Raise, Modulus, Concat, Less, LessEqual, More, MoreEqual, Equal, NotEqual, And, Or
};


class CExpressionNodeBinaryOperation : public CExpressionNode
{
    public:
        CExpressionNodeBinaryOperation(BinaryOperationType type, ExpressionNode left, ExpressionNode right);
        virtual ~CExpressionNodeBinaryOperation();

		BinaryOperationType GetType();
		ExpressionNode GetLeft();
		ExpressionNode GetRight();

		string GetTypeAsString();

		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();

		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:
		BinaryOperationType m_type;
		ExpressionNode m_left;
		ExpressionNode m_right;

};

typedef CExpressionNodeBinaryOperation* ExpressionNodeBinaryOperation;
typedef list<ExpressionNodeBinaryOperation> CExpressionNodeBinaryOperationList;
typedef CExpressionNodeBinaryOperationList* ExpressionNodeBinaryOperationList;
typedef CExpressionNodeBinaryOperationList::iterator ExpressionNodeBinaryOperationIter;



#endif // EXPRESSION_NODE_BINARY_OPERATION_H

