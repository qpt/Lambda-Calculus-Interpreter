#include <iostream>
#include "parser.h"
#include "variable_term.h"
#include "application_term.h"
#include "abstraction_term.h"

parser::parser(const std::vector<token_pair>& _tokens)
	: m_tokens(_tokens)
{
	m_ast = build_ast(_tokens);
}

void parser::print()
{
	std::cout << std::endl << "Your input is parsed as:" << std::endl << std::endl;
	m_ast->print();
	std::cout << std::endl << std::endl;
}

std::shared_ptr<term> parser::build_ast(const std::vector<token_pair>& tokens)
{
	return parse_term(m_tokens.begin());
}

std::shared_ptr<term> parser::parse_term(std::vector<token_pair>::iterator& it)
{
	if (it->first == "var") // variable
	{
		 std::shared_ptr<term> newVariableTerm = parse_variable_term(it);
		 return parse_application_term(it, newVariableTerm);
	}
	else if (it->first == "(") // nested term in
	{
		++it;
		endOfTermCheck(it, "nested term");

		std::shared_ptr<term> nestedTerm = parse_term(it);
		
		return parse_application_term(it, nestedTerm);
	}
	else if (it->first == ")") // nested term out
	{
		++it;
		return nullptr;
	}
	else if (it->first == "L") // abstraction
	{
		std::shared_ptr<term> newAbstractionTerm =  parse_abstraction_term(it);
		return parse_application_term(it, newAbstractionTerm);
	}
	else
	{
		throw std::exception(std::string("CH" + std::to_string(getCharIndex(it))
			+ ": Unexpected token \'" + it->first + " " + it->second + "\' found!").c_str());
	}
}

std::shared_ptr<term> parser::parse_abstraction_term(std::vector<token_pair>::iterator& it)
{
	++it;
	endOfTermCheck(it, "abstraction term");
	variable captured = parse_variable(it);
	
	if (it == m_tokens.end() || it->first != ".")
	{
		throw std::exception(std::string("CH" + std::to_string(getCharIndex(it))
			+ ": Abstractor end symbol \'.\' not found!").c_str());
	}

	++it;
	endOfTermCheck(it, "abstraction term");
	std::shared_ptr<term> body = parse_term(it);

	abstraction_term newAbstractionTerm = abstraction_term(captured, body);

	return std::make_shared<abstraction_term>(newAbstractionTerm);
}

std::shared_ptr<term> parser::parse_application_term(std::vector<token_pair>::iterator& it,
	const std::shared_ptr<term>& lhs)
{
	if (it == m_tokens.end())
	{
		return lhs;
	}

	std::shared_ptr<term> rhs = parse_term(it);
	if (rhs == nullptr)
	{
		return lhs;
	}

	return std::make_shared<application_term>(application_term(lhs, rhs));
}

std::shared_ptr<term> parser::parse_variable_term(std::vector<token_pair>::iterator& it)
{
	variable newVariable = parse_variable(it);
	return std::make_shared<variable_term>(variable_term(newVariable));
}

variable parser::parse_variable(std::vector<token_pair>::iterator& it)
{
	if (it->first != "var")
	{
		throw std::exception(std::string("CH" + std::to_string(getCharIndex(it))
			+ ": \'" + it->second + "\' is not a variable").c_str());
	}
	variable newVariable = variable(it->second);
	++it;

	return newVariable;
}

void parser::endOfTermCheck(std::vector<token_pair>::iterator& it, const std::string& termType)
{
	if (it == m_tokens.end())
	{
		throw std::exception(std::string("CH" + std::to_string(getCharIndex(it))
			+ ": Unexpected ending after parsing " + termType + "!").c_str());
	}
}

int parser::getCharIndex(const std::vector<token_pair>::iterator& it) const
{
	return it - m_tokens.begin();
}

std::shared_ptr<term> parser::getAST()
{
	return m_ast;
}