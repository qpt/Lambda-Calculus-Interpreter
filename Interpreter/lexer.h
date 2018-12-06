#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

typedef std::pair<std::string, std::string> token_pair;

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
	bool isLetter(char token) const;
	bool isDigit(char token) const;
};

#endif // LEXER_H
