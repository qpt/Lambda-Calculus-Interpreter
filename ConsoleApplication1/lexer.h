#pragma once
#include <string>
#include <vector>

using token_pair = std::pair<std::string, std::string>;

class lexer
{
private:
	std::vector<token_pair> m_tokens;

public:
	lexer(const std::string& lambdaExpressionString);
	void print();

	std::vector<token_pair> getTokens();

private:
	void tokenize(const std::string& lambdaExpressionString);
};