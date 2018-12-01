#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <memory>
#include "term.h"
#include "prepostprocessor.h"

class interpreter
{
	prepostprocessor m_prepostprocessor;

public:
    std::string start(const char input[], std::vector<std::string>* reductions);

private:
	std::string interpretInput(const std::string& inputStr, std::vector<std::string>* strings);
	std::shared_ptr<term> eval(const std::shared_ptr<term>& ast, std::string* reducedASTStr);
};

#endif // INTERPRETER_H
