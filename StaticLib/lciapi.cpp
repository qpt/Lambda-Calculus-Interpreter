#include "lciapi.h"
#include "../Interpreter/lexer.h"
#include "../Interpreter/parser.h"

bool isTopLeftMostTermReduced;

std::string lci::getNormalForm(const std::string& inputStr, const bool isProcessed)
{
	std::string preProcessedStr = inputStr;

	if (isProcessed)
	{
		lci::g_prePostProcessor.preprocess(preProcessedStr);
	}

	lexer l(preProcessedStr);

	if (l.getTokens().size() == 0)
	{
		return std::string();
	}

	parser p(l.getTokens());

	std::string parsedPostProcessedStr = p.toString();

	if (isProcessed)
	{
		lci::g_prePostProcessor.postprocess(parsedPostProcessedStr);
	}

	std::shared_ptr<term> ast = p.getAST();

	if (ast != nullptr)
	{
		// This might take forever for a countably infinite number of cases,
		// so it's better to run this function on a separate thread!
		while (ast != nullptr && ast->hasBetaRedex())
		{
			ast = eval(ast);
		}

		std::string reducedNormalForm = ast->toString();

		if (isProcessed)
		{
			lci::g_prePostProcessor.postprocess(reducedNormalForm);
		}

		return reducedNormalForm;
	}

	return std::string();
}

std::shared_ptr<term> lci::eval(const std::shared_ptr<term>& ast)
{
	isTopLeftMostTermReduced = false;
	std::shared_ptr<term> reducedAST = ast->eval();

	return reducedAST;
}