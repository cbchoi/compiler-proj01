/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "utils.h"
//#include "treenode.h"

#include <iostream>
#include <string>
#include <sstream>

/*
void print_node(std::ostream& out, TreeNode* node)
{
	out << "childs" << std::endl;

	for(int i = 0; i < MAXCHILDREN; i++)
	{
		if(node->get_child(i) != nullptr)
			out << "> p" << i << ": " << node->attr.name << std::endl;	
	}
	
}*/

/* Procedure printToken prints a token
* and its lexeme to the listing file
*/
void print_token(std::ostream& out, TokenType token, std::string tokenString)
{
	switch (token)
	{
	// 6 TOKENS WILL BE USED
	case IF:
	case WHILE:
	case RETURN:
	case INT:
	case VOID:
	case ELSE:
		out << "reserved word:" << tokenString << std::endl;
		break;

	// ADDITION AND MODIFICATION OF SOME TOKENS
	case ASSIGN:  out << "=" << std::endl; break;
	case EQ: 	  out << "=="<< std::endl; break;
	case NE: 	  out << "!="<< std::endl; break;
	case LT: 	  out << "<" << std::endl; break;
	case LE: 	  out << "<="<< std::endl; break;
	case GT: 	  out << ">" << std::endl; break;
	case GE: 	  out << ">="<< std::endl; break;
	case LPAREN:  out << "("<<  std::endl; break;
	case RPAREN:  out << ")"<<  std::endl; break;
	case LBRACE:  out << "["<<  std::endl; break;
	case RBRACE:  out << "]"<<  std::endl; break;
	case LCURLY:  out << "{"<<  std::endl; break;
	case RCURLY:  out << "}"<<  std::endl; break;
	case SEMI:    out << ";"<<  std::endl; break;
	case COMMA:   out << ","<<  std::endl; break;
	case PLUS:    out << "+"<<  std::endl; break;
	case MINUS:   out << "-"<<  std::endl; break;
	case TIMES:   out << "*"<<  std::endl; break;
	case OVER:    out << "/"<<  std::endl; break;
	case ENDFILE: out << "EOF" << std::endl; break;
	case NUM:
		out << "NUM, val= " << tokenString << std::endl;
		break;
	case ID:
		out << "ID, name= " << tokenString << std::endl;
		break;
	case ERROR:
		out << "ERROR: " << tokenString << std::endl;
		break;
	default: /* should never happen */
		out << "Unknown token:" << token << std::endl;
	}
}

void print_msg(std::ostream& out, std::string msg)
{
	out << msg << std::endl;
}

void print_error(std::ostream& out, std::string msg)
{
	out << msg << std::endl;
}


#if 0
/* Function newStmtNode creates a new statement
* node for syntax tree construction
*/
TreeNode * newStmtNode(StmtKind kind, int lineno)
{
	TreeNode * t = new StmtTreeNode(kind, lineno, false);
	if (t == NULL)
	{
		std::stringstream sstream;
		sstream <<"Out of memory error at line " << lineno << std::endl;
		print_error(std::cerr, sstream.str());
	}
	
	return t;
}

/* Function newExpNode creates a new expression
* node for syntax tree construction
*/
TreeNode * newExpNode(ExpKind kind, int lineno)
{
	TreeNode * t = new ExpTreeNode(kind, lineno, false);
	if (t == NULL)
	{
		std::stringstream sstream;
		sstream <<"Out of memory error at line " << lineno << std::endl;
		print_error(std::cerr, sstream.str());
	}
	return t;
}

#ifdef 0
/* Function copyString allocates and makes a new
* copy of an existing string
*/
char * copyString(char * s)
{
	int n;
	char * t;
	if (s == NULL) return NULL;
	n = strlen(s) + 1;
	t = malloc(n);
	if (t == NULL)
		out << "Out of memory error at line %d\n", lineno);
	else strcpy(t, s);
	return t;
}
#endif

/* Variable indentno is used by printTree to
* store current number of spaces to indent
*/
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(std::ostream& out)
{
	int i;
	for (i = 0; i< indentno; i++)
		out << " ";
}

std::string typeName(ExpType type)
{
	static std::string i = "int";
	static std::string v = "void";
	static std::string invalid = "<<invalid type>>";

	switch (type)
	{
	case Integer: return i; break;
	case Void:    return v; break;
	default:      return invalid;
	}
}


/* procedure printTree prints a syntax tree to the
* listing file using indentation to indicate subtrees
*/
void print_tree(std::ostream& out, TreeNode * tree)
{
	int i;
	INDENT;
	while (tree != NULL) {
		printSpaces(out);
		if (tree->get_node_kind() == StmtK)
		{
			switch (tree->get_kind().stmt) {
			case CompStmtK:
				out << "Compound Statement :" << std::endl;
				break;
			case SelStmtK:
				if(tree->get_child(2)!=NULL)
					out << "If (condition) (body) (else) " << std::endl;
				else
					out << "If (condition) (body)" << std::endl;
				break;
			case IterStmtK:
				out << "While (condition) (body) " << std::endl;
				break;
			case RetStmtK:
				if(tree->get_child(0)==NULL)
					out << "Return Statement, with NOTHING" << std::endl;
				else
					out << "Return Statement, with below" << std::endl;
				break;
			case CallK:
				if(tree->get_child(0)!=NULL)
					out << "Call, name : " << tree->attr.name << " with arguments below" << std::endl;
				else
					out << "Call, name :" << tree->attr.name << ", with NOTHING" << std::endl;
				break;
			default:
				out << "Unknown Stmt kind" << std::endl;
				break;
			}
		}
		else if (tree->get_node_kind() == ExpK)
		{
			switch (tree->get_kind().exp) {
			case VarDeclK:
				if(tree->is_param() )
					out << "Single Parameter, name : " << tree->attr.name << ", type : " << typeName(tree->get_type()) << std::endl;
				else
					out << "Var Declaration, name : " << tree->attr.name << ", type : " << typeName(tree->get_type()) << std::endl;
				break;
			case VarArrayDeclK:
				if(tree->is_param() )
					out << "Array Parameter, name : "<< tree->attr.name << ", type : " << typeName(tree->get_type()) << std::endl;
				else
					out << "Array Var Declaration, name : " << tree->attr.name << ", type : " << typeName(tree->get_type()) << std::endl;
				break;
			case FuncDeclK:
				out << "Function Declaration, name : "<< tree->attr.name << ", type : " << typeName(tree->get_type()) << std::endl;
				break;
			case AssignK:
				out << "Assign : (destination) (source) " << std::endl;
				break;
			case OpK:
				out << "Op : " ;
				print_token(out, tree->attr.op, std::string("\0"));
				break;
			case IdK:
				out << "Id : " << tree->attr.name << std::endl;
				break;
			case ConstK:
				out << "Const : " << tree->attr.val << std::endl;
				break;
			default:
				out << "Unknown ExpNode kind" << std::endl;
				break;
			}
		}
		else 
			out << "Unknown node kind" << std::endl;
		
		for (i = 0;i < MAXCHILDREN;i++)
			print_tree(out, tree->get_child(i));
		tree = tree->get_sibling();
	}
	UNINDENT;
}
#endif