#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "yyvaltype.h"


yyvalType* makeyyvalType(int linenum, char* value, char* token)
{
	yyvalType* ret = (yyvalType*)malloc(sizeof(yyvalType));

	ret->linenum = linenum;
	ret->value = strdup(value);
	ret->tokText = strdup(token);

	return ret;
}

