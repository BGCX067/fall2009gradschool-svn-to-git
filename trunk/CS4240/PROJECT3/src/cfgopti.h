/****************************************************/
/* File: cfgopti.h                                  */
/* The control flow opti interface to the           */
/* LUA compiler                                     */
/* Puyan                                            */
/****************************************************/


#ifndef _CFGOPTI_H_
#define _CFGOPTI_H_

#include "cfg.h"

BOOL RemoveBrToUncondBr(FUNC* f);                  // CFG Opti #1
BOOL RemoveUnreachableFromEntryBlocks(FUNC* f);    // CFG Opti #2
// CFG Opti #3
BOOL MergeSingleEdgeBrToBlock(FUNC* f);            // CFG Opti #4
BOOL MergeIdenticalBrsToBlock(FUNC* f);            // CFG Opti #5

#endif
