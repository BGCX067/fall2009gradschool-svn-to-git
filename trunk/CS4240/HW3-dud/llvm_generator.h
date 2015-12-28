#ifndef LLVM_GENERATOR_H
#define LLVM_GENERATOR_H

#define STRING_LENGHT 100.0

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <map>


#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace llvm;
using namespace std;

class CLlvmGenerator
{
public:
	CLlvmGenerator();
	virtual ~CLlvmGenerator();

	static CLlvmGenerator* GetInstance();

	void Initilize();

	
	Function* GetConcatFunction();
	Function* GetLenghtFunction();
	Function* GetCopyFunction();
	Function* GetPrintFunction();
	Function* GetToStringFunction();

	Module* GetModule();




protected:	
private:
	static CLlvmGenerator* m_instance;




	Function* m_concatFunction;
	Function* m_lenghtFunction;
	Function* m_copyFunction;
	Function* m_printFunction;
	Function* m_toStringFunction;

	Module* m_mod;

	void CreateGlobals();
	void CreateConcatStringFunction();
	void CreateStringLenghtFunction();
	void CreateCopyStringFunction();
	void CreatePrintStringFunction();
	void CreateToStringFunction();
	
};


#endif // LLVM_GENERATOR_H
