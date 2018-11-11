#pragma once
#include <string>
#include <memory>
#include "term.h"

class interpreter
{
public:
	void start();

private:
	void interpretInput(const std::string& inputStr);
	std::shared_ptr<term> eval(const std::shared_ptr<term>& ast);
};