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
		else if (isLetter(token))
		{
			std::string varName = std::string(1, token);

			for (size_t j = i + 1; j < lambdaExpressionString.size(); ++j)
			{
				const char nextToken = lambdaExpressionString[j];

				if (isDigit(nextToken))
				{
					i = j;
					varName += std::string(1, nextToken);
				}
				else
				{
					break;
				}
			}
			
			m_tokens.push_back(std::make_pair("var", varName));
		}
		else
		{
			std::string errorMessage = std::string("Unrecognized symbol \'" + std::string(1, token)
				+ "\' at index: " + std::to_string(i));

			throw std::exception(errorMessage.c_str());
		}
	}
}

bool lexer::isLetter(char token) const
{
	return token >= 'a' && token <= 'z';
}

bool lexer::isDigit(char token) const
{
	return token >= '0' && token <= '9';
}