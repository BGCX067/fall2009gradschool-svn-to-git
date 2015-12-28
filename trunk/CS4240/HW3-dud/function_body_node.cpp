#include "function_body_node.h"

CFunctionBodyNode::CFunctionBodyNode(NameNodeList parameters, bool varparm, ChunkNode block)
{
	m_parameters = parameters;
	m_varparm = varparm;
	m_block = block;
}

CFunctionBodyNode::~CFunctionBodyNode()
{
}


NameNodeList CFunctionBodyNode::GetParameters()
{
	return m_parameters;
}


bool CFunctionBodyNode::GetVarparm()
{
	return m_varparm;
}

ChunkNode CFunctionBodyNode::GetBlock()
{
	return m_block;
}

void CFunctionBodyNode::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( FunctionBody " << endl;

	NameNodeIter it;
	for (it=m_parameters->begin(); it!=m_parameters->end(); it++)
	{
		NameNode name = *it;
		PrintTabs(file, tabCount+1);
		file << "( " << name->GetValue() << " ) " << endl;
	}

	if (m_varparm)
	{
		PrintTabs(file, tabCount+1);
		file << "( ... ) " << endl;
	}

	m_block->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CFunctionBodyNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        for (list<NameNode>::iterator childIter = m_parameters->begin(); childIter != m_parameters->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        m_block->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = new CSymbolTableNode(this, parent);
    parent->insertChildTable(m_localSymbolTable);

    //Inserts the function parameters into a new local symbol table
    //Another symbol table will be created below this for the functions chunk but correctness is maintained
    for (list<NameNode>::iterator childIter = m_parameters->begin(); childIter != m_parameters->end(); childIter++)
    {
        m_localSymbolTable->insertTableEntry((*childIter)->GetValue(), "unknown"); // TODO: Put unknown in a macro somewhere.
    }

    for (list<NameNode>::iterator childIter = m_parameters->begin(); childIter != m_parameters->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }

    m_block->GenerateSymbolTables(m_localSymbolTable);
}


Function* CFunctionBodyNode::Codegen(string functionName)
{
	if (m_varparm)
	{
		std::cout << "varargs are NOT supported" << endl;
	}

	//types of parameters passed to the function
	vector<const Type*> functionParams;

	//TODO: determine return type
	const Type* returnType = Type::VoidTy;

	//loop through all the parameters determineing type
	NameNodeIter it;
	for (it=m_parameters->begin(); it!=m_parameters->end(); it++)
	{
		NameNode name = *it;
		
		//determine the type of the argument
		const Type* argType = NULL;		
		string argTypeStr = m_localSymbolTable->GetVariableTypeByName(name->GetValue());
		if (argTypeStr.compare(VAR_STRING__ENTRY_TYPE) == 0)
		{
			argType = PointerType::getUnqual(Type::Int8Ty);
		}
		else if (argTypeStr.compare(VAR_NUMBER__ENTRY_TYPE) == 0)
		{
			argType = Type::DoubleTy;			
		}
		else if (argTypeStr.compare(VAR_BOOLEAN_ENTRY_TYPE) == 0)
		{
			argType = Type::Int1Ty;			
		}
		else
		{
			EXIT_WITH_ERROR("Unknow type for argument symbol" << name->GetValue());
		}

		//add to params list
		functionParams.push_back(argType);
	}

	//create the function type
	FunctionType* funcType = FunctionType::get(returnType, functionParams, false);

	//make sure we have a unique function name
	string orgFunctionName = functionName;
	Module* mod = CLlvmGenerator::GetInstance()->GetModule();
	while (mod->getFunction(functionName) != NULL)
	{
		functionName += "_a";
	}

	//create the function
	Function* func = cast<Function>(mod->getOrInsertFunction(functionName, funcType));


	//put the subtion in the symbol table
	if (m_localSymbolTable != NULL) //will be null for function main
	{
		m_localSymbolTable->parent->UpdateLLVMValue(orgFunctionName, func);
	}

	//set the names of the the arguments
	Function::arg_iterator args = func->arg_begin();
	NameNodeIter it2;
	for (it2=m_parameters->begin(); it2!=m_parameters->end(); it2++)
	{
		NameNode name = *it2;
		Value* parm = args;
		parm->setName(name->GetValue());
		args++;

		m_localSymbolTable->UpdateLLVMValue(name->GetValue(), parm);

		//TODO: put Value* in symboltable
//		if (name->GetValue().compare("pa") == 0){
//			CLlvmGenerator::GetInstance()->TEMP_pa = parm;
//		}else if (name->GetValue().compare("pb") == 0){
//			CLlvmGenerator::GetInstance()->TEMP_pb = parm;
//		}
	}

		
	//std::cout << m_block->m_localSymbolTable << endl;


	//m_block->m_localSymbolTable->PrintSymbolTableHierarchy();
	
	//create the blocks to allocate local variables
	BasicBlock* blockAllocate = BasicBlock::Create("allocateLocals", func);
	IRBuilder<> blockAllocateBuilder(blockAllocate);

	if (m_block->m_localSymbolTable != NULL)
	{
		list<CSymbolTableNode*> funcSymTables;
		if (m_localSymbolTable != NULL)
		{
			funcSymTables = m_localSymbolTable->GetTablesInSameFunction();
		}
		else //main function
		{
			funcSymTables = m_block->m_localSymbolTable->GetTablesInSameFunction();
		}
		list<CSymbolTableNode*>::iterator tablesIt;
	
		for (tablesIt = funcSymTables.begin(); tablesIt != funcSymTables.end(); tablesIt++)
		{
			CSymbolTableNode* symTbl = *tablesIt;
			
			//get the list of local vars for this table
			list<string> localVars;
			list<pair<string, string> > locals = symTbl->GetVariableSymbols();
			list<pair<string, string> >::iterator localIt;
			for (localIt = locals.begin(); localIt != locals.end(); localIt++)
			{
				pair<string, string> localPair = *localIt;
				localVars.push_back(localPair.first);
			}

			//go through all the local vars
			list<string>::iterator localVarIt;
			for (localVarIt = localVars.begin(); localVarIt != localVars.end(); localVarIt++)
			{
				string localVarName = *localVarIt;

				AllocaInst* allocInst;

				//determine the type of the local var, and make an alloc for it
				string locTypeStr = symTbl->GetVariableTypeByName(localVarName);
				if (locTypeStr.compare(VAR_STRING__ENTRY_TYPE) == 0)
				{
					allocInst = blockAllocateBuilder.CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT), localVarName.c_str());
				}
				else if (locTypeStr.compare(VAR_NUMBER__ENTRY_TYPE) == 0)
				{
					allocInst = blockAllocateBuilder.CreateAlloca(Type::DoubleTy,  NULL, localVarName.c_str());	
				}
				else if (locTypeStr.compare(VAR_BOOLEAN_ENTRY_TYPE) == 0)
				{
					allocInst = blockAllocateBuilder.CreateAlloca(Type::Int1Ty,  NULL, localVarName.c_str());
				}
				else
				{
					EXIT_WITH_ERROR("Unknow type for local symbol" << localVarName);
				}
	
				//std::cout << "alloc " << localVarName << endl;

				//its an argument variable
				if (m_localSymbolTable == symTbl)
				{
					//get value of argument
					Value* defaultVal = symTbl->GetLLVMValue(localVarName);
					std::cout << defaultVal << endl;
					if (locTypeStr.compare(VAR_STRING__ENTRY_TYPE) == 0)
					{
						//call string copy function
						Function* copyFunction = CLlvmGenerator::GetInstance()->GetCopyFunction();
						blockAllocateBuilder.CreateCall2(copyFunction, defaultVal, allocInst);
					}
					else
					{
						blockAllocateBuilder.CreateStore(defaultVal, allocInst);
					}
				}
			
				//update Value* in the symbol table
				symTbl->UpdateLLVMValue(localVarName, allocInst);
			}

			
		}
	
	}

	//create first block of function
	BasicBlock* blockOne = BasicBlock::Create(functionName, func);

	//jump to the first block in the function after allocatingLocals
	blockAllocateBuilder.CreateBr(blockOne);

	//generate code for the function block
	BasicBlock* lastBlock = m_block->Codegen(blockOne, func, NULL);

	//add retrun void to end of last block b/c llvm must have return type
	IRBuilder<> lastBlockBuilder(lastBlock);

	lastBlockBuilder.CreateRetVoid();



	return func;

}

