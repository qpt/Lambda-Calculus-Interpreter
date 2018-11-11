#pragma once
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

	void print();
	std::shared_ptr<term> getAST();

private:
	std::shared_ptr<term> build_ast(const std::vector<token_pair>& tokens);
	std::shared_ptr<term> parse_term(std::vector<token_pair>::iterator& it);
	std::shared_ptr<term> parse_abstraction_term(std::vector<token_pair>::iterator& it);
	std::shared_ptr<term> parse_application_term(std::vector<token_pair>::iterator& it,
		const std::shared_ptr<term>& lhs);
	std::shared_ptr<term> parse_variable_term(std::vector<token_pair>::iterator& it);
	variable parse_variable(std::vector<token_pair>::iterator& it);

	void endOfTermCheck(std::vector<token_pair>::iterator& it, const std::string& termType);
	int getCharIndex(const std::vector<token_pair>::iterator& it) const;
};