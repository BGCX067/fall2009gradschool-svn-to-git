/****************************************************/
/* File: parse.h                                    */
/* The parser interface for the LUA compiler       */
/* Haicheng                                        */
/****************************************************/

#ifndef _PARSE_H_
#define _PARSE_H_

/* Function parse returns the newly 
 * constructed syntax tree
 */
TreeNode * parse(void);

extern int funNum;

#endif
