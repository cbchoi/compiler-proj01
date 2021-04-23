/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
//#include "treenode.h"
/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void print_token(std::ostream& out, TokenType, std::string );
void print_msg(std::ostream& out, std::string msg);
void print_error(std::ostream& out, std::string msg);


/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
//TreeNode * newStmtNode(StmtKind, int);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
//TreeNode * newExpNode(ExpKind, int);

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
//void print_tree(std::ostream&, TreeNode * );

#endif
