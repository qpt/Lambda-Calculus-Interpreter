#include <iostream>
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"

bool isTopLeftMostTermReduced;

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
	std::string preProcessedStr = inputStr;
	m_prepostprocessor.preprocess(preProcessedStr);

	lexer l(preProcessedStr);

	if (l.getTokens().size() == 0)
	{
		std::cout << ">>> ";
		return;
	}

	parser p(l.getTokens());

	std::string parsedPostProcessedStr = p.toString();
	m_prepostprocessor.postprocess(parsedPostProcessedStr);
	std::cout << std::endl << "Your input is parsed as:" << std::endl;
	std::cout << parsedPostProcessedStr << std::endl << std::endl;
	std::shared_ptr<term> ast = p.getAST();

	if (ast != nullptr)
	{
		std::cout << "Starting beta-Reduction" << std::endl;

		int i = 0;
		while (ast != nullptr && ast->hasBetaRedex())
		{
			std::cout << std::endl << ++i << ": ";
			ast = eval(ast);
		}


		std::string reducedNormalForm = ast->toString();
		m_prepostprocessor.postprocess(reducedNormalForm);
		std::cout << std::endl << "Normal Form found: " << std::endl << reducedNormalForm << std::endl;
	}

	std::cout << std::endl << ">>> ";
}

std::shared_ptr<term> interpreter::eval(const std::shared_ptr<term>& ast)
{
	isTopLeftMostTermReduced = false;
	std::shared_ptr<term> reducedAST = ast->eval();
	std::string reducedASTStr = reducedAST->toString();
	m_prepostprocessor.postprocess(reducedASTStr);
	std::cout << reducedASTStr << std::endl;

	return reducedAST;
}
