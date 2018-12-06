#include "parser.h"
#include <iostream>
#include <stdexcept>
#include "utility.h"
#include "variableTerm.h"
#include "applicationTerm.h"
#include "abstractionTerm.h"

parser::parser(const std::vector<token_pair>& _tokens)
	: m_tokens(_tokens)
{
	m_ast = buildAST();
}

std::string parser::toString()
{
	if (m_ast != nullptr)
	{
		return m_ast->toString();
	}

	return std::string();
}

std::shared_ptr<term> parser::buildAST()
{
    auto it = m_tokens.begin();
	return parseApplicationTerm(it);
}

std::shared_ptr<term> parser::parseApplicationTerm(std::vector<token_pair>::iterator& it)
{
	std::shared_ptr<term> lhs = nullptr;

	while (it != m_tokens.end() && it->first != ")")
	{
		std::shared_ptr<term> newAst = parseTerm(it);

		if (lhs == nullptr)
		{
			lhs = newAst;
		}
		else
		{
			lhs = std::make_shared<applicationTerm>(applicationTerm(lhs, newAst));
		}
	}

	return lhs;
}

std::shared_ptr<term> parser::parseTerm(std::vector<token_pair>::iterator& it)
{
	if (it->first == "var") // variable
	{
		return parseVariableTerm(it);
	}
	else if (it->first == "(") // nested term in
	{
		++it;
		endOfTermCheck(it, "nested term");

		std::shared_ptr<term> nestedTerm = parseApplicationTerm(it);
		endOfTermCheck(it, "nested term");

		if (it->first != ")") // nested term out
		{
			throw std::runtime_error(std::string("CH" + misc::to_string(getCharIndex(it))
				+ ": Close parenthesis not found!").c_str());
		}
		++it;

		return nestedTerm;
	}
	else if (it->first == "L") // abstraction
	{
		return parseAbstractionTerm(it);
	}
	else
	{
		throw std::runtime_error(std::string("CH" + misc::to_string(getCharIndex(it))
			+ ": Unexpected token \'" + it->first + " " + it->second + "\' found!").c_str());
	}
}

std::shared_ptr<term> parser::parseAbstractionTerm(std::vector<token_pair>::iterator& it)
{
	++it;
	endOfTermCheck(it, "abstraction term");
	variable captured = parseVariable(it);

	if (it == m_tokens.end() || it->first != ".")
	{
		throw std::runtime_error(std::string("CH" + misc::to_string(getCharIndex(it))
			+ ": Abstractor end symbol \'.\' not found!").c_str());
	}

	++it;
	endOfTermCheck(it, "abstraction term");
	std::shared_ptr<term> body = parseApplicationTerm(it);

	abstractionTerm newAbstractionTerm = abstractionTerm(captured, body);

	return std::make_shared<abstractionTerm>(newAbstractionTerm);
}

std::shared_ptr<term> parser::parseVariableTerm(std::vector<token_pair>::iterator& it)
{
	variable newVariable = parseVariable(it);
	return std::make_shared<variableTerm>(variableTerm(newVariable));
}

variable parser::parseVariable(std::vector<token_pair>::iterator& it)
{
	if (it->first != "var")
	{
		throw std::runtime_error(std::string("CH" + misc::to_string(getCharIndex(it))
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
		throw std::runtime_error(std::string("CH" + misc::to_string(getCharIndex(it))
			+ ": Unexpected ending after parsing " + termType + "!").c_str());
	}
}

int parser::getCharIndex(const std::vector<token_pair>::iterator& it) const
{
	return (int)(it - m_tokens.begin());
}

std::shared_ptr<term> parser::getAST()
{
	return m_ast;
}
