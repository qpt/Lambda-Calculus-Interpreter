#include <iostream>
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"

void interpreter::start()
{
	char name[2048];
	std::cout << "Lambda Calculus Interpreter v0.1a" << std::endl;
	std::cout << std::endl << ">>> ";

	while (std::cin.getline(name, 2048))
	{
		std::string inputStr(name);

		try
		{
			interpretInput(inputStr);
		}
		catch (const std::exception& e)
		{
			std::cout << "Syntax error: " << e.what() << std::endl;
			std::cout << ">>> ";
		}
	}
}

void interpreter::interpretInput(const std::string& inputStr)
{
	lexer l(inputStr);

	if (l.getTokens().size() == 0)
	{
		std::cout << ">>> ";
		return;
	}

	parser p(l.getTokens());
	p.print();
	std::shared_ptr<term>& ast = p.getAST();

	if (ast != nullptr)
	{
		std::cout << "Starting beta-Reduction" << std::endl;

		int i = 0;
		while (ast != nullptr && ast->hasBetaRedex())
		{
			std::cout << std::endl << ++i << ": ";
			ast = eval(ast);
		}

		std::cout << std::endl << "Normal Form found: ";
		ast->print();
		std::cout << std::endl;
	}

	std::cout << std::endl << ">>> ";
}

std::shared_ptr<term> interpreter::eval(const std::shared_ptr<term>& ast)
{
	std::shared_ptr<term>& reducedAST = ast->eval();
	reducedAST->print();
	std::cout << std::endl;

	return reducedAST;
}