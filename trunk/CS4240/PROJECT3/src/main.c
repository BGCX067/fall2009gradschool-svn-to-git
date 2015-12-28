/****************************************************/
/* File: main.c                                     */
/* Main program for LUA compiler                    */
/* Haicheng                                         */
/****************************************************/

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
#include "symtab.h"
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif

/* allocate global variables */
int lineno = 0;
int firstTime = TRUE;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;
int DFGTrace = FALSE;

int Error = FALSE;
main( int argc, char * argv[] )
{  TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  char *pgmName;
  int i;
  int exitCode = 0;
  
  if (argc < 2)
  { fprintf(stderr,"usage: %s <filename1> <filename2> <filename3> ...\n",argv[0]);
      exit(1);
  }
  
  for (i = 1; i < argc; i++)
  {
    lineno = 0;
    firstTime = TRUE;
    Error = FALSE;
    
    strcpy(pgm,argv[i]) ;
    if ((pgmName = strrchr (pgm, '.')) == NULL)
    { fprintf(stderr, "the suffix of File %s is wrong", pgm);
      exit(1);
    }



    source = fopen(pgm,"r");
    if (source == NULL)
    { fprintf(stderr,"File %s not found\n",pgm);
      exit(1);
    }
    
    listing = stdout;
        
    sprintf(pgmName, ".ll");
    code = /*stdout;*/fopen(pgm,"w");
    
    if (code == NULL)
    { fprintf(stderr,"Cannot open output file %s\n",pgmName);
      exit(1);
    }
    

#if NO_PARSE
    while (getToken() != ENDFILE);
#else
    syntaxTree = parse();
    if (TraceParse) {
      printTree(syntaxTree);
      fprintf(listing,"\n");
    }
#if !NO_ANALYZE
  if (! Error)
  { int i;
    buildSymtab(syntaxTree);
    
    for (i = 0; i < funNum + 2; i++)
    { typeCheck(syntaxTree);}
    
    if (TraceAnalyze) printTypeTree(syntaxTree);
  }
#if !NO_CODE
  if (! Error)
  { codeGen(syntaxTree,pgmName);
    fclose(code);
  }
#endif
#endif
#endif
    if(Error) exitCode = 1;
    fclose(source);
  }
  exit(exitCode);
}

