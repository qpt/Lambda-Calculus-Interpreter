#include "lexer.h"
#include <iostream>

lexer::lexer(const std::string& lambdaExpressionString)
{
	tokenize(lambdaExpressionString);
}

void lexer::print()
{
	std::cout << "Lexer pass: " << std::endl;

	for (auto& elem : m_tokens)
	{
		std::cout << "[ " << elem.first << " : " << elem.second << " ]" << std::endl;
	}
	std::cout << std::endl;
}

std::vector<token_pair> lexer::getTokens()
{
	return m_tokens;
}

void lexer::tokenize(const std::string& lambdaExpressionString)
{
	for (size_t i = 0; i < lambdaExpressionString.size(); ++i)
	{
		char token = lambdaExpressionString[i];

		if (token == ' ' || token == '\n' || token == '\t')
		{
			continue;
		}
		else if (token == '(' || token == ')' || token == 'L' || token == '.')
		{
			m_tokens.push_back(std::make_pair(std::string(1, token), ""));
		}
		else if (token >= 'a' && token <= 'z')
		{
			m_tokens.push_back(std::make_pair("var", std::string(1, token)));
		}
		else
		{
			std::string errorMessage = std::string("Unrecognized symbol \'" + std::string(1, token)
				+ "\' at index: " + std::to_string(i));

			throw std::exception(errorMessage.c_str());
		}
	}
}