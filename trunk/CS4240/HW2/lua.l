%{

#define YYSTYPE void*

#include <stdio.h>
#include <string.h>
#include "yacc.h"
#include "yyvaltype.h"

int linenum = 0;

int equalsCount = -1;
int firstChrOfString3 = 0;

char* curStr = NULL;
int curStrLen = 0;

void resetStr()
{
	free(curStr);
	curStr = malloc(1);
	curStr[0] = '\0';
	curStrLen = 1;
}

void appendStr(char* str, int len)
{
	curStrLen += len;
	curStr = realloc(curStr, curStrLen);
	strncat(curStr, str, len);
}



%}

%x STRING1 STRING2 STRING3 COMMENT1 COMMENT2

%%

<INITIAL>{

	"and"						yylval = (void*)makeyyvalType(linenum, "", "and");	return AND; 
	"or"						yylval = (void*)makeyyvalType(linenum, "", "or");		return OR;
	"not"						yylval = (void*)makeyyvalType(linenum, "", "not");	return NOT;
	"break"						yylval = (void*)makeyyvalType(linenum, "", "break");	return BREAK;
	"do"						yylval = (void*)makeyyvalType(linenum, "", "do");		return DO;
	"else"						yylval = (void*)makeyyvalType(linenum, "", "else");	return ELSE;
	"elseif"					yylval = (void*)makeyyvalType(linenum, "", "elseif");	return ELSEIF;
	"end"						yylval = (void*)makeyyvalType(linenum, "", "end");	return END;
	"false"						yylval = (void*)makeyyvalType(linenum, "", "false");	return FALSE;
	"for"						yylval = (void*)makeyyvalType(linenum, "", "for");	return FOR;
	"function"					yylval = (void*)makeyyvalType(linenum, "", "function");	return FUNCTION;
	"if"						yylval = (void*)makeyyvalType(linenum, "", "if");		return IF;
	"in"						yylval = (void*)makeyyvalType(linenum, "", "in");		return IN;
	"local"						yylval = (void*)makeyyvalType(linenum, "", "local");	return LOCAL;
	"nil"						yylval = (void*)makeyyvalType(linenum, "", "nil");	return NIL;
	"repeat"					yylval = (void*)makeyyvalType(linenum, "", "repeat");	return REPEAT;
	"return"					yylval = (void*)makeyyvalType(linenum, "", "return");	return RETURN;
	"then"						yylval = (void*)makeyyvalType(linenum, "", "then");	return THEN;
	"true"						yylval = (void*)makeyyvalType(linenum, "", "true");	return TRUE;
	"until"						yylval = (void*)makeyyvalType(linenum, "", "until");	return UNTIL;
	"while"						yylval = (void*)makeyyvalType(linenum, "", "while");	return WHILE;


	";" 						yylval = (void*)makeyyvalType(linenum, "", ";");		return SEMI;
	"=" 						yylval = (void*)makeyyvalType(linenum, "", "=");		return EQUALS;
	"," 						yylval = (void*)makeyyvalType(linenum, "", ",");		return COMMA;
	"..." 						yylval = (void*)makeyyvalType(linenum, "", "...");	return DOTDOTDOT;
	".." 						yylval = (void*)makeyyvalType(linenum, "", "..");		return DOTDOT;
	"." 						yylval = (void*)makeyyvalType(linenum, "", ".");		return DOT;
	"[" 						yylval = (void*)makeyyvalType(linenum, "", "[");		return OPEN_BRACK;
	"]" 						yylval = (void*)makeyyvalType(linenum, "", "]");		return CLOSE_BRACK;
	"(" 						yylval = (void*)makeyyvalType(linenum, "", "(");		return OPEN_PAR;
	")" 						yylval = (void*)makeyyvalType(linenum, "", ")");		return CLOSE_PAR;
	"{" 						yylval = (void*)makeyyvalType(linenum, "", "{");		return OPEN_SQUIG;
	"}" 						yylval = (void*)makeyyvalType(linenum, "", "}");		return CLOSE_SQUIG;
	":" 						yylval = (void*)makeyyvalType(linenum, "", ":");		return COLON;
	"+" 						yylval = (void*)makeyyvalType(linenum, "", "+");		return PLUS;
	"-" 						yylval = (void*)makeyyvalType(linenum, "", "-");		return MINUS;
	"*" 						yylval = (void*)makeyyvalType(linenum, "", "*");		return STAR;
	"/" 						yylval = (void*)makeyyvalType(linenum, "", "/");		return FSLASH;
	"^" 						yylval = (void*)makeyyvalType(linenum, "", "^");		return CARET;
	"%" 						yylval = (void*)makeyyvalType(linenum, "", "%");		return PERCENT;
	"<" 						yylval = (void*)makeyyvalType(linenum, "", "<");		return LESS;
	"<=" 						yylval = (void*)makeyyvalType(linenum, "", "<=");		return LESS_EQUAL;
	">" 						yylval = (void*)makeyyvalType(linenum, "", ">");		return MORE;
	">=" 						yylval = (void*)makeyyvalType(linenum, "", ">=");		return MORE_EQUAL;
	"==" 						yylval = (void*)makeyyvalType(linenum, "", "==");		return EQUAL_EQUAL;
	"~=" 						yylval = (void*)makeyyvalType(linenum, "", "~=");		return SQUIG_EQUAL;
	"#"							yylval = (void*)makeyyvalType(linenum, "", "#");		return SHARP;






	[A-Za-z_][A-Za-z0-9_]*				yylval = (void*)makeyyvalType(linenum, yytext, "Name");	return NAME;

	[0-9]+(\.?[0-9]+((e|E)-?[0-9]+)?)?	yylval = (void*)makeyyvalType(linenum, yytext, "Number");	return NUMBER;
	0x[0-9a-fA-F]+						yylval = (void*)makeyyvalType(linenum, yytext, "Number");	return NUMBER;



	\"      					resetStr(); BEGIN(STRING1);
	\'      					resetStr(); BEGIN(STRING2);

	\[\=*\[						{
									resetStr();
									BEGIN(STRING3);
									firstChrOfString3 = 1; /*ignore a \n if its the first thing */
									equalsCount = yyleng - 2;
								}

	--\[\=*\[					{
									BEGIN(COMMENT2);
									equalsCount = yyleng - 4;
								}

	--							BEGIN(COMMENT1);

	
	\n                  		linenum++; 
	[ \t]+                  	/* ignore whitespace */


	.							{ 
									printf("Error:  unreconized char '%s'  line %i\n", yytext, linenum);
									exit(1);
         						}

}


<STRING1>{

	\"	        				{ /*string is over*/
									yylval = (void*)makeyyvalType(linenum, curStr, "String");
									BEGIN(INITIAL);
									return STRING;
         						}

	[^\\\n\"]+      			appendStr(yytext, yyleng);

}

<STRING2>{

	\'	        				{ /*string is over*/							
									yylval = (void*)makeyyvalType(linenum, curStr, "String");						
									BEGIN(INITIAL);
									return STRING;
         						}

	[^\\\n\']+      			appendStr(yytext, yyleng);

}
     
<STRING1,STRING2>{


	\\\n						linenum++; appendStr("\n", 1);

	\n       					{						     		
									printf("Error:  Unescaped new line before end of string constant!!  line %i\n", linenum);
									exit(1);
						     	}

	<<EOF>>   					{
                 					printf("Error:  End of file before end of string constant!!  line %i\n", linenum);
									exit(1);
                  				}


	
	\\[0-7]{1,3} 				{ /* octal escape sequence */
							
									/* convert to an int */
									int result; 
					 				sscanf(yytext + 1, "%o", &result);

					 				if (result > 0xff)
									{
										/* its not a valid octal so try something else */
										REJECT;
									}
									else
									{
										/* add to string as a chr */
										appendStr((char*)&result, 1);
									}
			        			}


	\\a  						appendStr("\a", 1);
	\\b  						appendStr("\b", 1);
	\\f  						appendStr("\f", 1);
	\\r  						appendStr("\r", 1);
	\\t  						appendStr("\t", 1);
	\\v  						appendStr("\v", 1);
	\\n							appendStr("\n", 1);
		

	\\. 	 					appendStr(yytext + 1, 1);

}

<STRING3>{

	<<EOF>>   					{
                 					printf("Error:  End of file before end of string literal!!  line %i\n", linenum);
									exit(1);
                  				}


	\]\=*\]						{
									if (yyleng - 2 != equalsCount)
									{
										/* false alarm its got the wrong number of equals */
										REJECT;
									}
									else
									{
										yylval = (void*)makeyyvalType(linenum, curStr, "String");					
										BEGIN(INITIAL);
										return STRING;
									}
									firstChrOfString3 = 0;
								}

	\n							{
									linenum++;
									if (firstChrOfString3 == 0) /*ignore a \n if its the first thing */
									{
										appendStr("\n", 1);
									}
									firstChrOfString3 = 0;
								}

	\]							appendStr("]", 1); firstChrOfString3 = 0;
	[^\n\]]+      				appendStr(yytext, yyleng); firstChrOfString3 = 0;

}

<COMMENT1>{

	\n							{
									/* comment is over */
									linenum++;
									BEGIN(INITIAL);
								}


	[^\n]+      				/* nothing */

}

<COMMENT2>{

	\]\=*\]						{
									if (yyleng - 2 != equalsCount)
									{
										/* false alarm its got the wrong number of equals */
										REJECT;
									}
									else
									{
					              		/* comment is over */						
										BEGIN(INITIAL);
									}
								}

	\n							{
									linenum++;									
								}

	\]							/* nothing */
	[^\n\]]+      				/* nothing */

}




%%
