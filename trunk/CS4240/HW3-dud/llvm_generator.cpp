#include "llvm_generator.h"


extern CSymbolTableNode globalSymbolTable;


CLlvmGenerator* CLlvmGenerator::m_instance = NULL;

CLlvmGenerator* CLlvmGenerator::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new CLlvmGenerator();
	}
	return m_instance;
}


Function* CLlvmGenerator::GetConcatFunction()
{
	return m_concatFunction;
}

Function* CLlvmGenerator::GetLenghtFunction()
{
	return m_lenghtFunction;
}

Function* CLlvmGenerator::GetCopyFunction()
{
	return m_copyFunction;
}

Function* CLlvmGenerator::GetPrintFunction()
{
	return m_printFunction;
}

Function* CLlvmGenerator::GetToStringFunction()
{
	return m_toStringFunction;
}

Module* CLlvmGenerator::GetModule()
{
	return m_mod;
}

CLlvmGenerator::CLlvmGenerator()
{

}

CLlvmGenerator::~CLlvmGenerator()
{
}



void CLlvmGenerator::Initilize()
{
	//create modules
	m_mod = new Module("module");	

	//create string functions	
	CreateStringLenghtFunction();
	CreateConcatStringFunction();
	CreateCopyStringFunction();
	CreatePrintStringFunction();
	CreateToStringFunction();

	//create global vars and functions
	CreateGlobals();
}


void CLlvmGenerator::CreateGlobals()
{	

	//create array of STRING_LENGHT 0's llvm gets mad if we dont initilize
	Constant* zero = ConstantInt::get(Type::Int8Ty, 0);
	vector<Constant*> zeros;
	int i;
	for(i=0; i<STRING_LENGHT; i++)
	{	
		zeros.push_back(zero);
	}
	Constant* zeroArray = ConstantArray::get(ArrayType::get(Type::Int8Ty, STRING_LENGHT), zeros);

	//create inits for bools and dooubles
	Constant* zeroBool = ConstantInt::get(Type::Int1Ty, 0);
	Constant* zeroDouble = ConstantFP::get(Type::DoubleTy, 0.0);



	//get the list of globals from the symbol table
	list<string> globalVariables;

	list<pair<string, string> > globals = globalSymbolTable.GetVariableSymbols();
	list<pair<string, string> >::iterator globalIt;
	for (globalIt = globals.begin(); globalIt != globals.end(); globalIt++)
	{
		pair<string, string> globalPair = *globalIt;
		globalVariables.push_back(globalPair.first);
	}




	list<string>::iterator it;
	for (it = globalVariables.begin(); it != globalVariables.end(); it++)
	{
		string varName = *it;

		Value* varValue;

		string varTypeStr = globalSymbolTable.GetVariableTypeByName(varName);
		if (varTypeStr.compare(VAR_STRING__ENTRY_TYPE) == 0)
		{
			ArrayType* varType = ArrayType::get(Type::Int8Ty, STRING_LENGHT);
			GlobalVariable* varAccess = new GlobalVariable(varType, false, GlobalVariable::WeakLinkage, zeroArray, varName, m_mod, false, 0);			
			varValue = varAccess;
		}
		else if (varTypeStr.compare(VAR_NUMBER__ENTRY_TYPE) == 0)
		{
			const Type* varType = Type::DoubleTy;
			GlobalVariable* varAccess = new GlobalVariable(varType, false, GlobalVariable::WeakLinkage, zeroDouble, varName, m_mod, false, 0);			
			varValue = varAccess;
		}
		else if (varTypeStr.compare(VAR_BOOLEAN_ENTRY_TYPE) == 0)
		{
			const Type* varType = Type::Int1Ty;
			GlobalVariable* varAccess = new GlobalVariable(varType, false, GlobalVariable::WeakLinkage, zeroBool, varName, m_mod, false, 0);			
			varValue = varAccess;
		}
		else
		{
			EXIT_WITH_ERROR("Unknow type for global symbol" << varName);
		}

		//put Value* in symbol table
		globalSymbolTable.UpdateLLVMValue(varName, varValue);
		
		
	}

		
}











void CLlvmGenerator::CreateConcatStringFunction()
{	
		//function arguments and return type
		Type* arg1Type = PointerType::getUnqual(Type::Int8Ty);
		Type* arg2Type = PointerType::getUnqual(Type::Int8Ty);
		Type* arg3Type = PointerType::getUnqual(Type::Int8Ty);
		const Type* returnType = Type::VoidTy;

		vector<const Type*> functionParams;
		functionParams.push_back(arg1Type);
		functionParams.push_back(arg2Type);
		functionParams.push_back(arg3Type);
		
		FunctionType* funcType = FunctionType::get(returnType, functionParams, false);  
		

		//create the function
		Function* func = cast<Function>(m_mod->getOrInsertFunction("string_concat", funcType));  
		
		//function args
		Function::arg_iterator args = func->arg_begin();
		Value* str1 = args++;
		str1->setName("str1");
		Value* str2 = args++;
		str2->setName("str2");
		Value* copyTo = args++;
		copyTo->setName("copyTo");


		//create the blocks and thier builders
		BasicBlock* blockInit = BasicBlock::Create("initblock", func);
		IRBuilder<> blockInitBuilder(blockInit);

		BasicBlock* blockFindEndTest = BasicBlock::Create("findendtest", func);
		IRBuilder<> blockFindEndTestBuilder(blockFindEndTest);

		BasicBlock* blockFindEndLoop = BasicBlock::Create("findendloop", func);
		IRBuilder<> blockFindEndLoopBuilder(blockFindEndLoop);

		BasicBlock* blockCopyTest = BasicBlock::Create("copytest", func);
		IRBuilder<> blockCopyTestBuilder(blockCopyTest);

		BasicBlock* blockCopyLoop = BasicBlock::Create("copyloop", func);
		IRBuilder<> blockCopyLoopBuilder(blockCopyLoop);

		BasicBlock* blockLast = BasicBlock::Create("lastblock", func);
		IRBuilder<> blockLastBuilder(blockLast);



		//allocate space for location in str1 and str2
		Value* str1LocVar = blockInitBuilder.CreateAlloca(Type::Int32Ty, 0, "str1Variable");
		Value* str2LocVar = blockInitBuilder.CreateAlloca(Type::Int32Ty, 0, "str2Variable");
		blockInitBuilder.CreateStore(ConstantInt::get(Type::Int32Ty, 0), str1LocVar);
		blockInitBuilder.CreateStore(ConstantInt::get(Type::Int32Ty, 0), str2LocVar);
		blockInitBuilder.CreateBr(blockFindEndTest);

		//TODO: check that lenght of str1 and str2 is not greater than STRING_LENGHT

		//loop until str1LocVar points to null pointer in str1
		Value* str1Loc = blockFindEndTestBuilder.CreateLoad(str1LocVar, "str1Loc");
		Value* str1LocPtr = blockFindEndTestBuilder.CreateGEP(str1, str1Loc, "str1LocPtr");
		Value* str1LocVal = blockFindEndTestBuilder.CreateLoad(str1LocPtr, "str1Val");
		Value* atEnd = blockFindEndTestBuilder.CreateICmpNE(str1LocVal, ConstantInt::get(Type::Int8Ty, 0));
		blockFindEndTestBuilder.CreateCondBr(atEnd, blockFindEndLoop, blockCopyTest);

		//get location to make the copy at and the pointers into the array
		Value* str1Loc2 = blockFindEndLoopBuilder.CreateLoad(str1LocVar, "str1Loc2");
		Value* str1LocPtr2 = blockFindEndLoopBuilder.CreateGEP(str1, str1Loc2, "str1LocPtr2");
		Value* copyToLocPtr = blockFindEndLoopBuilder.CreateGEP(copyTo, str1Loc2, "copyToLocPtr");
		//get the value from str1 and put in copyTo
		Value* str1LocVal2 = blockFindEndLoopBuilder.CreateLoad(str1LocPtr2, "str1Val2");
		blockFindEndLoopBuilder.CreateStore(str1LocVal2, copyToLocPtr);
		//increment str1 location
		str1Loc2 = blockFindEndLoopBuilder.CreateAdd(str1Loc2, ConstantInt::get(Type::Int32Ty, 1));
		blockFindEndLoopBuilder.CreateStore(str1Loc2, str1LocVar);
		blockFindEndLoopBuilder.CreateBr(blockFindEndTest);



		//loop while str1LocVar is less than STRING_LENGHT
		Value* str1Loc3 = blockCopyTestBuilder.CreateLoad(str1LocVar, "str1Loc3");
		Value* doneLooping = blockCopyTestBuilder.CreateICmpULT(str1Loc3, ConstantInt::get(Type::Int32Ty, STRING_LENGHT));
		blockCopyTestBuilder.CreateCondBr(doneLooping, blockCopyLoop, blockLast);


		//get str2 character
		Value* str2Loc = blockCopyLoopBuilder.CreateLoad(str2LocVar, "str2Loc");
		Value* str2LocPtr = blockCopyLoopBuilder.CreateGEP(str2, str2Loc, "str2LocPtr");
		Value* str2LocVal = blockCopyLoopBuilder.CreateLoad(str2LocPtr, "str2Val");
		//and put it into return string
		Value* str1Loc4 = blockCopyLoopBuilder.CreateLoad(str1LocVar, "str1Loc4");
		Value* copyToLocPtr2 = blockCopyLoopBuilder.CreateGEP(copyTo, str1Loc4, "copyToLocPtr2");
		blockCopyLoopBuilder.CreateStore(str2LocVal, copyToLocPtr2);
		//increment both pointers
		str1Loc4 = blockCopyLoopBuilder.CreateAdd(str1Loc4, ConstantInt::get(Type::Int32Ty, 1));
		blockCopyLoopBuilder.CreateStore(str1Loc4, str1LocVar);
		str2Loc = blockCopyLoopBuilder.CreateAdd(str2Loc, ConstantInt::get(Type::Int32Ty, 1));
		blockCopyLoopBuilder.CreateStore(str2Loc, str2LocVar);
		//branch to loop check
		blockCopyLoopBuilder.CreateBr(blockCopyTest);


		//return
		blockLastBuilder.CreateRetVoid();


		//set class variable
		m_concatFunction = func;

}

void CLlvmGenerator::CreateStringLenghtFunction()
{
		//function arguments and return type
		Type* arg1Type = PointerType::getUnqual(Type::Int8Ty);
		const Type* returnType = Type::Int32Ty;

		vector<const Type*> functionParams;
		functionParams.push_back(arg1Type);
		
		FunctionType* funcType = FunctionType::get(returnType, functionParams, false);  
		

		//create the function
		Function* func = cast<Function>(m_mod->getOrInsertFunction("string_lenght", funcType));  
		
		//function args
		Function::arg_iterator args = func->arg_begin();
		Value* str1 = args++;
		str1->setName("str1");


		//create the blocks and thier builders
		BasicBlock* blockInit = BasicBlock::Create("initblock", func);
		IRBuilder<> blockInitBuilder(blockInit);

		BasicBlock* blockFindEndTest = BasicBlock::Create("findendtest", func);
		IRBuilder<> blockFindEndTestBuilder(blockFindEndTest);

		BasicBlock* blockFindEndLoop = BasicBlock::Create("findendloop", func);
		IRBuilder<> blockFindEndLoopBuilder(blockFindEndLoop);

		BasicBlock* blockLast = BasicBlock::Create("lastblock", func);
		IRBuilder<> blockLastBuilder(blockLast);



		//allocate space for location in str1
		Value* str1LocVar = blockInitBuilder.CreateAlloca(Type::Int32Ty, 0, "str1Variable");
		blockInitBuilder.CreateStore(ConstantInt::get(Type::Int32Ty, 0), str1LocVar);
		blockInitBuilder.CreateBr(blockFindEndTest);

		//loop until str1LocVar points to null pointer in str1
		Value* str1Loc = blockFindEndTestBuilder.CreateLoad(str1LocVar, "str1Loc");
		Value* str1LocPtr = blockFindEndTestBuilder.CreateGEP(str1, str1Loc, "str1LocPtr");
		Value* str1LocVal = blockFindEndTestBuilder.CreateLoad(str1LocPtr, "str1Val");
		Value* atEnd = blockFindEndTestBuilder.CreateICmpNE(str1LocVal, ConstantInt::get(Type::Int8Ty, 0));
		blockFindEndTestBuilder.CreateCondBr(atEnd, blockFindEndLoop, blockLast);

		//increment str1LocVar by 1
		Value* str1Loc2 = blockFindEndLoopBuilder.CreateLoad(str1LocVar, "str1Loc2");
		str1Loc2 = blockFindEndLoopBuilder.CreateAdd(str1Loc2, ConstantInt::get(Type::Int32Ty, 1));
		blockFindEndLoopBuilder.CreateStore(str1Loc2, str1LocVar);
		blockFindEndLoopBuilder.CreateBr(blockFindEndTest);

		//return the lenght
		Value* str1Loc3 = blockLastBuilder.CreateLoad(str1LocVar, "str1Loc3");
		blockLastBuilder.CreateRet(str1Loc3);


		//set class variable
		m_lenghtFunction = func;
}



void CLlvmGenerator::CreateCopyStringFunction()
{	
		//function arguments and return type
		Type* arg1Type = PointerType::getUnqual(Type::Int8Ty);
		Type* arg2Type = PointerType::getUnqual(Type::Int8Ty);
		const Type* returnType = Type::VoidTy;

		vector<const Type*> functionParams;
		functionParams.push_back(arg1Type);
		functionParams.push_back(arg2Type);
		
		FunctionType* funcType = FunctionType::get(returnType, functionParams, false);  
		

		//create the function
		Function* func = cast<Function>(m_mod->getOrInsertFunction("string_copy", funcType));  
		
		//function args
		Function::arg_iterator args = func->arg_begin();
		Value* from = args++;
		from->setName("from");
		Value* to = args++;
		to->setName("to");


		//create the blocks and thier builders
		BasicBlock* blockInit = BasicBlock::Create("initblock", func);
		IRBuilder<> blockInitBuilder(blockInit);

		BasicBlock* blockCopyTest = BasicBlock::Create("copytest", func);
		IRBuilder<> blockCopyTestBuilder(blockCopyTest);

		BasicBlock* blockCopyLoop = BasicBlock::Create("copyloop", func);
		IRBuilder<> blockCopyLoopBuilder(blockCopyLoop);

		BasicBlock* blockLast = BasicBlock::Create("lastblock", func);
		IRBuilder<> blockLastBuilder(blockLast);



		//allocate space for location in from string
		Value* fromLocVar = blockInitBuilder.CreateAlloca(Type::Int32Ty, 0, "fromLocVar");
		blockInitBuilder.CreateStore(ConstantInt::get(Type::Int32Ty, 0), fromLocVar);
		blockInitBuilder.CreateBr(blockCopyTest);

		//loop until str1LocVar points to null pointer in str1
		Value* fromLoc = blockCopyTestBuilder.CreateLoad(fromLocVar, "fromLoc");
		Value* fromLocPtr = blockCopyTestBuilder.CreateGEP(from, fromLoc, "fromLocPtr");
		Value* fromLocVal = blockCopyTestBuilder.CreateLoad(fromLocPtr, "fromLocVal");
		Value* atEnd = blockCopyTestBuilder.CreateICmpNE(fromLocVal, ConstantInt::get(Type::Int8Ty, 0));
		blockCopyTestBuilder.CreateCondBr(atEnd, blockCopyLoop, blockLast);

		//get location to make the copy at and the pointers into the array
		Value* fromLoc2 = blockCopyLoopBuilder.CreateLoad(fromLocVar, "fromLoc2");
		Value* fromLocPtr2 = blockCopyLoopBuilder.CreateGEP(from, fromLoc2, "fromLocPtr2");
		Value* toLocPtr = blockCopyLoopBuilder.CreateGEP(to, fromLoc2, "toLocPtr");
		//get the value from from and put in to
		Value* fromLocVal2 = blockCopyLoopBuilder.CreateLoad(fromLocPtr2, "fromLocVal2");
		blockCopyLoopBuilder.CreateStore(fromLocVal2, toLocPtr);
		//increment fromLoc
		fromLoc2 = blockCopyLoopBuilder.CreateAdd(fromLoc2, ConstantInt::get(Type::Int32Ty, 1));
		blockCopyLoopBuilder.CreateStore(fromLoc2, fromLocVar);
		blockCopyLoopBuilder.CreateBr(blockCopyTest);


		//add null pointer to the end
		Value* fromLoc3 = blockLastBuilder.CreateLoad(fromLocVar, "fromLoc3");
		Value* toLocPtr2 = blockLastBuilder.CreateGEP(to, fromLoc3, "toLocPtr2");
		blockLastBuilder.CreateStore(ConstantInt::get(Type::Int8Ty, 0), toLocPtr2);
		blockLastBuilder.CreateRetVoid();


		//set class variable
		m_copyFunction = func;

}



void CLlvmGenerator::CreatePrintStringFunction()
{
		//function arguments and return type
		Type* arg1Type = PointerType::getUnqual(Type::Int8Ty);
		const Type* returnType = Type::VoidTy;

		vector<const Type*> functionParams;
		functionParams.push_back(arg1Type);
		
		FunctionType* funcType = FunctionType::get(returnType, functionParams, false);  
		

		//create the function
		Function* func = cast<Function>(m_mod->getOrInsertFunction("string_print", funcType));  
		
		//function args
		Function::arg_iterator args = func->arg_begin();
		Value* str = args++;
		str->setName("str");

		//create the blocks and thier builders
		BasicBlock* block = BasicBlock::Create("block", func);
		IRBuilder<> blockBuilder(block);
		BasicBlock* block2 = BasicBlock::Create("call_printf", func);
		IRBuilder<> block2Builder(block2);


		//alocate space for a newline string
		Value* strNewLine = blockBuilder.CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT), "newLineConstant");	

		//add new line to string
		Value* offsetPtrNewLine = blockBuilder.CreateGEP(strNewLine, ConstantInt::get(Type::Int32Ty, 0));
		blockBuilder.CreateStore(ConstantInt::get(Type::Int8Ty, '\n'), offsetPtrNewLine);
		//add null terminator to string
		Value* offsetPtrNullTerm = blockBuilder.CreateGEP(strNewLine, ConstantInt::get(Type::Int32Ty, 1));
		blockBuilder.CreateStore(ConstantInt::get(Type::Int8Ty, '\0'), offsetPtrNullTerm);


		//create a space for a string to hold the result
		Value* strRet = blockBuilder.CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT), "withNewLine");

		//call concatination function
		Value* concatFunction = GetConcatFunction();
		blockBuilder.CreateCall3(concatFunction, str, strNewLine, strRet);

		//to next block
		blockBuilder.CreateBr(block2);
		
		//After a string of the llvm ir is generated a call to the C
		//printf function will be placed here
		

		//return void
		block2Builder.CreateRetVoid();


		//set class variable
		m_printFunction = func;
}




void CLlvmGenerator::CreateToStringFunction()
{
		//function arguments and return type
		const Type* arg1Type = Type::DoubleTy;
		Type* arg2Type = PointerType::getUnqual(Type::Int8Ty);
		const Type* returnType = Type::VoidTy;

		vector<const Type*> functionParams;
		functionParams.push_back(arg1Type);
		functionParams.push_back(arg2Type);
		
		FunctionType* funcType = FunctionType::get(returnType, functionParams, false);  
		

		//create the function
		Function* func = cast<Function>(m_mod->getOrInsertFunction("string_double_to_string", funcType));  
		
		//function args
		Function::arg_iterator args = func->arg_begin();
		Value* val = args++;
		val->setName("val");
		Value* str = args++;
		str->setName("str");

		//create the blocks and thier builders
		BasicBlock* block = BasicBlock::Create("block", func);
		IRBuilder<> blockBuilder(block);
		BasicBlock* block2 = BasicBlock::Create("call_fprintf", func);
		IRBuilder<> block2Builder(block2);


		//alocate space for a "%d" string
		Value* strFormat = blockBuilder.CreateAlloca(Type::Int8Ty,  ConstantInt::get(Type::Int32Ty, STRING_LENGHT), "formatConstant");	

		//add new line to string
		Value* offsetPtrPercent = blockBuilder.CreateGEP(strFormat, ConstantInt::get(Type::Int32Ty, 0));
		blockBuilder.CreateStore(ConstantInt::get(Type::Int8Ty, '%'), offsetPtrPercent);
		//add null terminator to string
		Value* offsetPtrD = blockBuilder.CreateGEP(strFormat, ConstantInt::get(Type::Int32Ty, 1));
		blockBuilder.CreateStore(ConstantInt::get(Type::Int8Ty, 'f'), offsetPtrD);
		//add null terminator to string
		Value* offsetPtrNullTerm = blockBuilder.CreateGEP(strFormat, ConstantInt::get(Type::Int32Ty, 2));
		blockBuilder.CreateStore(ConstantInt::get(Type::Int8Ty, '\0'), offsetPtrNullTerm);

		//can get it to print a double but it will print an int so just to that
		//blockBuilder.CreateFPToSI(val, Type::Int32Ty, "asInt");

		//to next block
		blockBuilder.CreateBr(block2);


		
		//After a string of the llvm ir is generated a call to the C
		//sprintf function will be placed here
		

		//return void
		block2Builder.CreateRetVoid();


		//set class variable
		m_toStringFunction = func;
}



