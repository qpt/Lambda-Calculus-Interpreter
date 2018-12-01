#ifndef LCIAPI_H
#define LCIAPI_H
#include <memory>
#include "../Interpreter/term.h"
#include "../Interpreter/prepostprocessor.h"

namespace lci
{
	std::string getNormalForm(const std::string& input, const bool isProcessed);

	static prepostprocessor g_prePostProcessor;
	static std::shared_ptr<term> eval(const std::shared_ptr<term>& ast);
}

#endif // LCIAPI_H
