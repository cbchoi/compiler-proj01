/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>

/* MAXRESERVED = the number of reserved words */
// 6 WILL BE USED + 6 WILL NOT BE USED = 12
#define MAXRESERVED 6

typedef enum
/* book-keeping tokens */
{
	ENDFILE, ERROR,

	/* reserved words */
	IF, ELSE, WHILE, RETURN, INT, VOID,

	/* multicharacter tokens */
	ID, NUM,

	/* special symbols */
	ASSIGN, EQ, NE, LT, LE, GT, GE, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, LBRACE, RBRACE, LCURLY, RCURLY, SEMI, COMMA, SKIP
} TokenType;

extern int lineno; /* source line number for listing */

				   /**************************************************/
				   /***********   Syntax tree for parsing ************/
				   /**************************************************/

typedef enum { StmtK, ExpK } NodeKind;
typedef enum { CompStmtK, SelStmtK, IterStmtK, RetStmtK, CallK } StmtKind;
typedef enum { VarDeclK, VarArrayDeclK, FuncDeclK, AssignK, OpK, IdK, ConstK } ExpKind;

class Scope;

typedef union { StmtKind stmt; ExpKind exp; } Kind;

class Attributes
{
public:
	Attributes(): scope(nullptr), name("not_defined"){}

public:
	TokenType op;
	int val;
	std::string name;
	Scope* scope;
};

/* ExpType is used for type checking */
typedef enum { Void, Integer, Boolean } ExpType;

#define MAXCHILDREN 3

/* Error = TRUE prevents further passes if an error occurs */
extern int Error;
#endif