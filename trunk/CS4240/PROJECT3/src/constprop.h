#ifndef CONSTPROP_H
#define CONSTPROP_H

#include "code.h"

int constProp(FUNC *f);
int blockConstProp(BLOCK * blk);
int replaceWithConstFloat(Inst *instruction, char *def, BLOCK *block, float num);
int replaceWithConstInt(Inst *instruction, char *def, BLOCK *block, int num);
void condToUncond(FUNC *f);
void changeToUncond(BLOCK *blk);

#endif
