#ifndef PARSER_H
#define PARSER_H

#include "term.h"
#include "lexer.h"
#include "variable.h"
#include <memory>

class parser
{
private:
	std::vector<token_pair> m_tokens;
	std::shared_ptr<term> m_ast;

public:
	parser(const std::vector<token_pair>& _lexer);

	std::string toString();
	std::shared_ptr<term> getAST();

private:
	std::shared_ptr<term> buildAST();
	std::shared_ptr<term> parseApplicationTerm(std::vector<token_pair>::iterator& it);
	std::shared_ptr<term> parseTerm(std::vector<token_pair>::iterator& it);
	std::shared_ptr<term> parseAbstractionTerm(std::vector<token_pair>::iterator& it);
	std::shared_ptr<term> parseVariableTerm(std::vector<token_pair>::iterator& it);
	variable parseVariable(std::vector<token_pair>::iterator& it);

	void endOfTermCheck(std::vector<token_pair>::iterator& it, const std::string& termType);
	int getCharIndex(const std::vector<token_pair>::iterator& it) const;
};

#endif // PARSER_H
