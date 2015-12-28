#include <stdio.h>
#include <string.h>
#include "parsetree.h"

extern int linenum;
extern int yylval;
extern FILE *yyin;

/*char * tok_names[] =
{
  "NAME", "NUMBER", "STRING", "AND",
  "BREAK", "DO", "ELSE", "ELSEIF", "END", "FALSE", "FOR", "FUNCTION", "IF",
  "IN", "LOCAL", "NIL", "NOT", "OR", "REPEAT", "RETURN", "THEN", "TRUE",
  "UNTIL", "WHILE", "SEMI", "EQUALS", "COMMA", "DOT", "OPEN_BRACK",
  "CLOSE_BRACK", "DOTDOT", "DOTDOTDOT", "OPEN_PAR", "CLOSE_PAR",
  "OPEN_SQUIG", "CLOSE_SQUIG", "COLON", "PLUS", "MINUS", "STAR", "FSLASH",
  "CARET", "PERCENT", "LESS", "LESS_EQUAL", "MORE", "MORE_EQUAL",
  "EQUAL_EQUAL", "SQUIG_EQUAL", "SHARP", "$accept", "chunk", 0
};*/

treenode* topNode;

main(int argc, char** argv)
{	
	
	/*
		int ret = yylex();

		while(ret)
		{
			char* name = tok_names[ret-258];

			if (ret-258 <= 2)  //name number and string
			{
				printf("%s  (%s)\n", name, (char*)yylval);
			}
			else
			{
				printf("%s\n",name);		
			}
			ret = yylex();
		}
	*/

		int i;
		for(i=1;i<argc;i++)
		{			
			
			printf("opening %s\n", argv[i]);
			yyin = fopen(argv[i], "r");
			linenum = 0;
			yyparse();		
			fclose(yyin);


			int len = strlen( argv[i] );
			argv[i][len-1] = 't';
			argv[i][len-2] = 's';
			argv[i][len-3] = 'a';


			printf("writting %s\n", argv[i]);
			FILE* out = fopen(argv[i], "w");
			printTreeNode(topNode, out);
			fclose(out);



		}


}


int yywrap()
{
	return 1;
}

