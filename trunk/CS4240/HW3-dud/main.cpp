#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "chunk_node.h"
#include "name_node.h"
#include "function_body_node.h"


#include "llvm_generator.h"

#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;


extern CSymbolTableNode globalSymbolTable;

extern "C"
{
	extern int linenum;
	extern int yylval;
	extern FILE *yyin;

	int yyparse(void);

	extern void* topnode;
}


int main(int argc, char** argv)
{
	int i;
	for(i=1;i<argc;i++)
	{

		//printf("opening %s\n", argv[i]);
		yyin = fopen(argv[i], "r");
		linenum = 0;

		yyparse();
		fclose(yyin);


		int len = strlen( argv[i] );
		argv[i][len-1] = 't';
		argv[i][len-2] = 's';
		argv[i][len-3] = 'a';
		//printf("writting %s\n", argv[i]);

		string outFileName = argv[i];
		outFileName = outFileName.substr(0, outFileName.size() - 4) + ".ll";

		ofstream fileout(argv[i]);

		ChunkNode top = (ChunkNode)topnode;



		top->PrintNode(fileout, 0);

		fileout.close();



		//create Function body node that wraps everything else this is the main function
        FunctionBodyNode mainFunction = new CFunctionBodyNode(new CNameNodeList(), false, top);
		globalSymbolTable.functionIn = mainFunction;

        top->GenerateSymbolTables(&globalSymbolTable);
 		globalSymbolTable.PrintSymbolTableHierarchy();


		//llvm generator generates globals stuff and built in string functions
		CLlvmGenerator* llvmGen = CLlvmGenerator::GetInstance();
		llvmGen->Initilize();


		//generate code for the tree
		mainFunction->Codegen("main");


		//so this disaster of code below here is printing the llvm to the file
		//i could not figure out how to get a call to printf in there using the
		//llvm api so im sticking it in there just as a string

		fstream filestr (outFileName.c_str(), fstream::out);

		std::string llvmString;

		raw_string_ostream stringStream(llvmString);

 		PassManager PM;
 		PM.add(createPrintModulePass(&stringStream));
 		PM.run(*(llvmGen->GetModule()));

		string toReplace = "call_printf:\t\t; preds = %block";
		string replaceWith = toReplace + "\n\t\%tmp1 = call i32 (i8*, ...)* @printf( i8* noalias  \%withNewLine ) nounwind";
		size_t loc = llvmString.find(toReplace);
		llvmString.replace(loc, toReplace.length(), replaceWith);

		string toReplace2 = "call_fprintf:\t\t; preds = %block";
		string replaceWith2 = toReplace2 + "\n\t%tmp1 = call i32 (i8*, i8*, ...)* @sprintf( i8* noalias  %str, i8* noalias  %formatConstant, double %val ) nounwind";
		size_t loc2 = llvmString.find(toReplace2);
		llvmString.replace(loc2, toReplace2.length(), replaceWith2);

		filestr << llvmString;
		filestr << "\ndeclare i32 @printf(i8* noalias , ...) nounwind";
		filestr << "\ndeclare i32 @sprintf(i8* noalias , i8* noalias , ...) nounwind ";

		filestr.close();

		std::cout << "Wrote " << outFileName << endl;

	}
}


