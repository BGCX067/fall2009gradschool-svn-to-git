

#include <iostream>
#include "statement_node_assign.h"
#include "name_node.h"

CStatementNodeAssign::CStatementNodeAssign(VariableNodeList variables, ExpressionNodeList expressions)
{
	m_variables = variables;
	m_expressions = expressions;
}

CStatementNodeAssign::~CStatementNodeAssign()
{
}


VariableNodeList CStatementNodeAssign::GetVariables()
{
	return m_variables;
}
ExpressionNodeList CStatementNodeAssign::GetExpressions()
{
	return m_expressions;
}


void CStatementNodeAssign::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Assign " << endl;

	VariableNodeIter it;
	for (it=m_variables->begin(); it!=m_variables->end(); it++)
	{
		VariableNode var = *it;
		var->PrintNode(file, tabCount+1);
	}


	ExpressionNodeIter it2;
	for (it2=m_expressions->begin(); it2!=m_expressions->end(); it2++)
	{
		ExpressionNode exp = *it2;
		exp->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}


BasicBlock* CStatementNodeAssign::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	/* TODO:
	If the list of expressions ends with a function call, then all values returned
	by that call enter the list of values, before the adjustment (except when the
	call is enclosed in parentheses; see §2.5). */


	//create a builder for this block
	IRBuilder<> builder(block);


	//create code to evaluate all the expressions
	list<Value*> expVals;
	ExpressionNodeIter it2;
	for (it2=m_expressions->begin(); it2!=m_expressions->end(); it2++)
	{
		ExpressionNode exp = *it2;
		Value* val = exp->Codegen(&builder);
		expVals.push_back(val);
	}


	/* 2.4.3 If there are fewer values than needed, the list is extended with as many
    nil's as needed.*/
	while (expVals.size() < m_variables->size())
	{
		//TODO: not extending with nils instead just not setting
		expVals.push_back(NULL);
	}


	//create code to assign all the variables
	VariableNodeIter it;
	for (it=m_variables->begin(); it!=m_variables->end(); it++)
	{
		VariableNode var = *it;

		//get value to assign
		Value* val = expVals.front();
		expVals.pop_front();

		//no more values
		if (val == NULL) { break; }

		//is the value a string
		if (val->getType() == PointerType::getUnqual(Type::Int8Ty))
		{		
			//get location of variable in mem
			Value* varValue = var->Codegen(&builder, true);

			//call string copy function
			Function* copyFunction = CLlvmGenerator::GetInstance()->GetCopyFunction();
			builder.CreateCall2(copyFunction, val, varValue);
		}
		else
		{
			//get location of variable in mem
			Value* loc = var->Codegen(&builder, true);

//			loc->getType()->print(std::cout);
//			std::cout << endl;
//			val->getType()->print(std::cout);
//			std::cout << endl;

			//store in mem
			builder.CreateStore(val, loc);
		}

	}


	//return the last block of this statement
	return block;
}

void CStatementNodeAssign::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent && NULL == m_localSymbolTable) return; // TODO: Throw an exception

    if (NULL == m_localSymbolTable)
        m_localSymbolTable = parent;

	CVariableNodeList::iterator   variter = m_variables->begin();
	CExpressionNodeList::iterator expiter = m_expressions->begin();

    for (;
	     variter != m_variables->end() &&
		 expiter != m_expressions->end();
	     variter++,
		 expiter++)
    {
        (*variter)->GenerateSymbolTables(m_localSymbolTable);
        (*expiter)->GenerateSymbolTables(m_localSymbolTable);

        list<BaseNode> varchildren = (*variter)->GetChildren();

        for (list<BaseNode>::iterator varchildIter = varchildren.begin();
			 varchildIter != varchildren.end();
			 varchildIter++)
        {
            (*varchildIter)->GenerateSymbolTables(m_localSymbolTable);
            string varnodeType = (*varchildIter)->GetNodeType();

            if (varnodeType == NAME_NODE_TYPE)
            {
                NameNode name = ((NameNode)(*varchildIter));
                string expType = (*expiter)->GetExpressionType();

                if (expType == "UNIT")
                {
                    EXIT_WITH_ERROR("Not allowed to assign to expressions or functions that return type UNIT: " + name->GetValue());
                }


                if (NULL != parent)
                {
                    globalSymbolTable.insertTableEntry(name->GetValue(), expType);
                }
                else
                {
                    globalSymbolTable.UpdateLocalValueType(name->GetValue(), expType);
                }

                break;
            }
            else
            {
                EXIT_WITH_ERROR("Table, or Object construct found in varlist = explist");
            }
        }
    }

    if (NULL != parent)
    {

        for (list<VariableNode>::iterator childIter = m_variables->begin(); childIter != m_variables->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(m_localSymbolTable);
        }

        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(m_localSymbolTable);
        }

    }
    else
    {
        for (list<VariableNode>::iterator childIter = m_variables->begin(); childIter != m_variables->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }
    }
}

