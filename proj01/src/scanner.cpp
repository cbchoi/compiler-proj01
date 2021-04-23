#include "scanner.h"
#include "utils.h"

#include <iostream>
Scanner::Scanner(std::ifstream& in, bool trace_flag)
:fin(in), bTraceScan(trace_flag)
{
	line_no = 1;
	getline(fin, cur_line);
	cur_pos = cur_line.begin();

	reservedWords.push_back({ "if",IF });
	reservedWords.push_back({ "else",ELSE });
	reservedWords.push_back({ "while",WHILE });
	reservedWords.push_back({ "return",RETURN });
	reservedWords.push_back({ "int",INT });
	reservedWords.push_back({ "void",VOID });
}

int Scanner::get_next_char()
{
	if (cur_pos < cur_line.end())
	{
		return *cur_pos++;
	}
	else
	{
		if(!fin.eof())
		{
			line_no++;
			getline(fin, cur_line);
			cur_pos = cur_line.begin();		
			return *cur_pos++;	
		}
		else
			return EOF;
	}
}

TokenType Scanner::reservedLookup(std::string s)
{
	for (std::vector<ReservedWords>::iterator iter = reservedWords.begin();
		iter != reservedWords.end(); iter++)
	{
		if (s == (*iter).str)
			return (*iter).tok;
	}
		
	return ID;
}

void Scanner::unget_next_char()
{
	cur_pos--;
}

TokenType Scanner::get_token()
{




}