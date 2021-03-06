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
	void start();

private:
	void interpretInput(const std::string& inputStr);
	std::shared_ptr<term> eval(const std::shared_ptr<term>& ast);
};

#endif // INTERPRETER_H