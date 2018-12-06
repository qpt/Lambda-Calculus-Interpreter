#include <iostream>
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"

bool isTopLeftMostTermReduced;

std::string interpreter::start(const char input[], std::vector<std::string>* reductions)
{
	std::cout << "Lambda Calculus Interpreter v0.1a" << std::endl;

		std::string inputStr(input);

		try
		{
			return interpretInput(inputStr, reductions);
		}
		catch (const std::exception& e)
		{
#if DEBUG
            std::rethrow_exception(std::current_exception());
#else
            std::rethrow_exception(std::current_exception());
#endif
            return "";
		}
}

std::string interpreter::interpretInput(const std::string& inputStr, std::vector<std::string>* strings)
{
	std::string preProcessedStr = inputStr;
	m_prepostprocessor.preprocess(preProcessedStr);

	lexer l(preProcessedStr);

	if (l.getTokens().size() == 0)
	{
		std::cout << ">>> ";
		return "";
	}

	parser p(l.getTokens());

	std::string parsedPostProcessedStr = p.toString();
	m_prepostprocessor.postprocess(parsedPostProcessedStr);
#if DEBUG
	std::cout << std::endl << "Your input is parsed as:" << std::endl;
	std::cout << parsedPostProcessedStr << std::endl << std::endl;
#endif
	std::shared_ptr<term> ast = p.getAST();

	if (ast != nullptr)
	{
#if DEBUG
		std::cout << "Starting beta-Reduction" << std::endl;
#endif
		while (ast != nullptr && ast->hasBetaRedex())
		{
            std::string retVal;
			ast = eval(ast, &retVal);
            strings->push_back(retVal);
#if DEBUG
            std::cout << retVal << std::endl;
#endif
		}


		std::string reducedNormalForm = ast->toString();
		m_prepostprocessor.postprocess(reducedNormalForm);
#if DEBUG
		std::cout << std::endl << "Normal Form found: " << std::endl << reducedNormalForm << std::endl;
#endif
        return reducedNormalForm;
	}

#if DEBUG
    std::cout << std::endl << ">>> ";
#endif
    return "";
}

std::shared_ptr<term> interpreter::eval(const std::shared_ptr<term>& ast, std::string* reducedASTStr)
{
	isTopLeftMostTermReduced = false;
	std::shared_ptr<term> reducedAST = ast->eval();
	(*reducedASTStr) = reducedAST->toString();
	m_prepostprocessor.postprocess((*reducedASTStr));

	return reducedAST;
}
