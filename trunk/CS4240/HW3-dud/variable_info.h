#ifndef VARIABLE_INFO_H
#define VARIABLE_INFO_H

#include <string>
#include <map>
#include <vector>
#include "error_handling.h"


#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;
using namespace llvm;

enum VariableType
{
	Number,
	String,
	Boolean,
	Null
};

class CVariableInfo
{
public:
	string name;
	bool function;

	VariableType type; //or return type

	vector<VariableType> arguments;

	Value* varLocation;
};


#endif // VARIABLE_INFO_H
