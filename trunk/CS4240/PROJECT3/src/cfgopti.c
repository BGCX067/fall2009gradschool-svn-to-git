/****************************************************/
/* File: cfgopti.c                                  */
/* Control flow related optimizations               */
/* for the LUA compiler                             */
/* Puyan                                            */
/****************************************************/

#include "cfgopti.h"
#include "globals.h"
/*
 * CFG Optimization #1
 */
BOOL RemoveBrToUncondBr(FUNC* f)
{
    BLOCK* currBlock = NULL;
    BOOL change = FALSE;

    if (!f) return change;
    if (!f->block) return change;

    /*    if (!cfg) return FALSE;*/
    /*    if (!cfg->node) return FALSE;*/
    /*    if (!cfg->node->basicBlock) return FALSE;*/

    currBlock = f->block;

    while (currBlock)
    { if(currBlock->ignore ==0)
        switch (currBlock->lastInst->instType)
        {
            case UncondBrI:
                {
                    UncondBrInst* uncondBrInst = (UncondBrInst*)currBlock->lastInst->inst;
                    BLOCK* fstSuccBB = currBlock->cfg->fstSuccNode->basicBlock;

                    if ((fstSuccBB->lastInst == fstSuccBB->inst) && fstSuccBB->lastInst->instType == UncondBrI)
                    {
                        uncondBrInst->dst.name = fstSuccBB->cfg->fstSuccNode->basicBlock->name;
                        currBlock->cfg->fstSuccNode = fstSuccBB->cfg->fstSuccNode;

                        {
                            int succPredCount = 0;
                            CFGList* currSuccPred = fstSuccBB->cfg->preds;
                            CFGList* onlySuccPred = currSuccPred;

                            while (currSuccPred)
                            {
                                succPredCount++;
                                currSuccPred = currSuccPred->next;
                            }

                            if (succPredCount == 1 &&
                                    !strcmp(onlySuccPred->value->basicBlock->name, currBlock->name))
                            {
                                fstSuccBB->ignore = 1;
                                // printf("Only: %s \n", onlySuccPred->value->basicBlock->name);
                                // printf("curr: %s\n",  currBlock->name);
                                // printf("pred 1: %s\n", fstSuccBB->name);
                            }
                        }

                        RemovePredFromCFGNode(fstSuccBB->cfg, currBlock->name);
                        change = TRUE;
                    }

                    break;
                }
            case CondBrI:
                {
                    BLOCK* fstSuccBB = currBlock->cfg->fstSuccNode->basicBlock;
                    BLOCK* sndSuccBB = currBlock->cfg->sndSuccNode->basicBlock;
                    CondBrInst* condBrInst = (CondBrInst*)currBlock->lastInst->inst;

                    if ((fstSuccBB->lastInst == fstSuccBB->inst) && fstSuccBB->lastInst->instType == UncondBrI)
                    {
                        // condBrInst->dstTrue.name = fstSuccBB->cfg->fstSuccNode->basicBlock->name;
                        condBrInst->dstTrue.name = strdup(fstSuccBB->cfg->fstSuccNode->basicBlock->name);
                        currBlock->cfg->fstSuccNode = fstSuccBB->cfg->fstSuccNode;

                        {
                            int succPredCount = 0;
                            CFGList* currSuccPred = fstSuccBB->cfg->preds;
                            CFGList* onlySuccPred = currSuccPred;

                            while (currSuccPred)
                            {
                                succPredCount++;
                                currSuccPred = currSuccPred->next;
                            }

                            if (succPredCount == 1 &&
                                    !strcmp(onlySuccPred->value->basicBlock->name, currBlock->name))
                            {
                                fstSuccBB->ignore = 1;
                                // printf("Only: %s \n", onlySuccPred->value->basicBlock->name);
                                // printf("curr: %s\n",  currBlock->name);
                                // printf("pred 2: %s\n", fstSuccBB->name);
                            }
                        }

                        RemovePredFromCFGNode(fstSuccBB->cfg, currBlock->name);
                        change = TRUE;
                    }

                    if ((sndSuccBB->lastInst == sndSuccBB->inst) && sndSuccBB->lastInst->instType == UncondBrI)
                    {
                        // condBrInst->dstFalse.name = sndSuccBB->cfg->fstSuccNode->basicBlock->name;
                        condBrInst->dstFalse.name = strdup(sndSuccBB->cfg->fstSuccNode->basicBlock->name);
                        currBlock->cfg->sndSuccNode = sndSuccBB->cfg->fstSuccNode;

                        {
                            int succPredCount = 0;
                            CFGList* currSuccPred = sndSuccBB->cfg->preds;
                            CFGList* onlySuccPred = currSuccPred;

                            while (currSuccPred)
                            {
                                succPredCount++;
                                currSuccPred = currSuccPred->next;
                            }



                            if (succPredCount == 1 &&
                                    !strcmp(onlySuccPred->value->basicBlock->name, currBlock->name))
                            {
                                sndSuccBB->ignore = 1;
                                // printf("Only: %s \n", onlySuccPred->value->basicBlock->name);
                                // printf("curr: %s\n",  currBlock->name);
                                // printf("pred 3: %s\n", sndSuccBB->name);

                            }
                        }

                        RemovePredFromCFGNode(sndSuccBB->cfg, currBlock->name);
                        change = TRUE;
                    }

                    break;
                }
            case RetI:
                {
                    break;
                }
            default:
                // Error = TRUE;
                break;
        }

        currBlock = currBlock->next;
    }

    /*    if (cfg->next)*/
    /*        cfg->next->backedges = cfg->backedges;*/

    /*    change |= RemoveBrToUncondBr(cfg->next);*/

    return change;
}

/*
 * CFG Optimization #2
 *
 * Remove BBs that aren't dominated by entry.
 *
 */
BOOL RemoveUnreachableFromEntry(FUNC* cfg)
{
    return FALSE;
}

/*
 * CFG Optimization #4
 */
BOOL MergeSingleEdgeBrToBlock(FUNC* f)
{
    BLOCK* currBlock = NULL;
    BOOL change = FALSE;

    if (!f) return change;
    if (!f->block) return change;
    /*    if (!cfg) return;*/
    /*    if (!cfg->node) return;*/
    /*    if (!cfg->node->basicBlock) return;*/

    currBlock = f->block;

    while (currBlock)
    { if(currBlock->ignore ==0) 
        switch (currBlock->lastInst->instType)
        {
            case UncondBrI:
                {
                    UncondBrInst* uncondBrInst = (UncondBrInst*)currBlock->lastInst->inst;
                    BLOCK* fstSuccBB = currBlock->cfg->fstSuccNode->basicBlock;

                    int succPredCount = 0;
                    CFGList* currSuccPred = fstSuccBB->cfg->preds;
                    CFGList* onlySuccPred = currSuccPred;

                    while (currSuccPred)
                    {
                        succPredCount++;
                        currSuccPred = currSuccPred->next;
                    }

                    if (succPredCount == 1 &&
                            !strcmp(onlySuccPred->value->basicBlock->name, currBlock->name))
                    {
                        Inst* oldLastInst = currBlock->lastInst;
                        Inst* instInsertionLocation = oldLastInst->prev;
                        Inst* firstInstOfSucc = fstSuccBB->inst;

                        if (!firstInstOfSucc) return;

                        while (firstInstOfSucc->prev)
                        {
                            firstInstOfSucc = firstInstOfSucc->prev;
                        }

                        if (instInsertionLocation)
                        {
                            instInsertionLocation->next = firstInstOfSucc;
                            firstInstOfSucc->prev = instInsertionLocation;
                            change = TRUE;

                            currBlock->cfg->fstSuccNode = fstSuccBB->cfg->fstSuccNode;
                            currBlock->cfg->sndSuccNode = fstSuccBB->cfg->sndSuccNode;
                            currBlock->lastInst = fstSuccBB->lastInst;

                            fstSuccBB->ignore = 1;
                            RemovePredFromCFGNode(fstSuccBB->cfg, currBlock->name); // unnecessary


                            // free(fstSuccBB->cfg);
                            // free(fstSuccBB->inst);
                            // free(fstSuccBB);
                        }
                        else
                        {
                            currBlock->inst = fstSuccBB->inst;
                            change = TRUE;

                            currBlock->cfg->fstSuccNode = fstSuccBB->cfg->fstSuccNode;
                            currBlock->cfg->sndSuccNode = fstSuccBB->cfg->sndSuccNode;
                            currBlock->lastInst = fstSuccBB->lastInst;

                            fstSuccBB->ignore = 1;
                            RemovePredFromCFGNode(fstSuccBB->cfg, currBlock->name); // unnecessary

                            // free(fstSuccBB->cfg);
                            // free(fstSuccBB->inst);
                            // free(fstSuccBB);
                        }
                    }

                    break;
                }
            case CondBrI:
                {
                    break;
                }
            case RetI:
                {
                    break;
                }
            default:
                // Error = TRUE;
                break;
        }

        currBlock = currBlock->next;
    }

    return change;
    /*    if (cfg->next)*/
    /*        cfg->next->backedges = cfg->backedges;*/

    /*    MergeSingleEdgeBrToBlock(cfg->next);*/
}

/*
 * CFG Optimization #5
 */
BOOL MergeIdenticalBrsToBlock(FUNC* f)
{
    BLOCK* currBlock = NULL;
    BOOL change = FALSE;

    if (!f) return change;
    if (!f->block) return change;
    /*    if (!cfg) return;*/
    /*    if (!cfg->node) return;*/
    /*    if (!cfg->node->basicBlock) return;*/

    currBlock = f->block;

    while (currBlock)
    { if(currBlock->ignore ==0) 
        switch (currBlock->lastInst->instType)
        {
            case UncondBrI:
                {
                    break;
                }
            case CondBrI:
                {
                    BLOCK* fstSuccBB = currBlock->cfg->fstSuccNode->basicBlock;
                    BLOCK* sndSuccBB = currBlock->cfg->sndSuccNode->basicBlock;
                    CondBrInst* condBrInst = (CondBrInst*)currBlock->lastInst->inst;

                    if (!strcmp(condBrInst->dstFalse.name, condBrInst->dstTrue.name))
                    {
                        Inst* oldLastInst = NULL;
                        Inst* replacementInst = (Inst*)malloc(sizeof(Inst));
                        UncondBrInst* innerInst = (UncondBrInst*)malloc(sizeof(UncondBrInst));

                        if (!replacementInst)
                        {
                            printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                            exit(0);
                        }

                        if (!innerInst)
                        {
                            printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                            exit(0);
                        }

                        replacementInst->inst = innerInst;
                        innerInst->dst.name = strdup(condBrInst->dstFalse.name);
                        replacementInst->instType = UncondBrI;
                        replacementInst->parent = currBlock->lastInst->parent;
                        replacementInst->prev = currBlock->lastInst->prev;
                        replacementInst->next = NULL;
                        currBlock->lastInst->prev->next = replacementInst;
                        oldLastInst = currBlock->lastInst;
                        currBlock->lastInst = replacementInst;

                        change = TRUE;

                        // free((UncondBrInst*)oldLastInst->inst);
                        // free(oldLastInst);

                    }
                    break;
                }
            case RetI:
                {
                    break;
                }
            default:
                // Error = TRUE;
                break;
        }

        currBlock = currBlock->next;
    }


    return change;
}

