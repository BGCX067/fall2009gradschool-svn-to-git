/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the LUA compiler       */
/* Haicheng                                         */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN (256)

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN+1];
//extern char b4TokenString[MAXTOKENLEN+1];
extern char nameTokenString[MAXTOKENLEN+1];
extern char numTokenString[MAXTOKENLEN+1];
extern char stringTokenString[MAXTOKENLEN+1];

/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void);

#endif
