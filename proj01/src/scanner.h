#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "globals.h"

#define BUFLEN 256

typedef struct
{
	std::string str;
	TokenType tok;
} ReservedWords;

class Scanner
{
public:
	Scanner(std::ifstream& in, bool trace_flag = true);

public:
	TokenType get_token();

	int get_next_char();
	void unget_next_char();

	std::string get_current_token(){ return token.str();}
	int get_line_no(){ return line_no; }
private:
	std::ifstream& fin;
	
	std::string cur_line;
	std::string::iterator cur_pos;

	std::stringstream token;

	TokenType reservedLookup(std::string);

	int line_no;
	
	typedef enum
	{
		START, INEQ, INCOMMENT, INNUM, INID, DONE, INLT, INGT, INNE, INOVER, INCOMMENT_
	} StateType;

	std::vector<ReservedWords> reservedWords;


	bool bTraceScan;
};
