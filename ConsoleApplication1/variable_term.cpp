#include <iostream>
#include "variable_term.h"

variable_term::variable_term(const variable _variable, const termType type)
	: term(type), m_variable(_variable)
{
}

//variable_term::~variable_term()
//{
//	std::cout << "Destroy variable term: ";
//	print();
//	std::cout << std::endl;
//}

std::shared_ptr<term> variable_term::copy()
{
	return std::make_shared<variable_term>(variable_term(m_variable));
}

void variable_term::print() const
{
	std::cout << m_variable.getName();
}

std::shared_ptr<term> variable_term::eval()
{
	return copy();
}

bool variable_term::isBetaRedex() const
{
	return false;
}

bool variable_term::hasBetaRedex() const
{
	return false;
}

std::set<variable> variable_term::getFreeVariables() const
{
	// FV(x) = {x}
	auto varSet = std::set<variable>();
	varSet.insert(m_variable);

	return varSet;
}

void variable_term::alphaRenameBy(const variable varToRename, const variable newVar)
{
	// This variable is free
	return;
}

void variable_term::naiveRenameBy(const variable varToRename, const variable newVar)
{
	// Naive rename only bound variables
	if (m_variable.getName() == varToRename.getName())
	{
		m_variable.setName(newVar.getName());
	}
}

std::shared_ptr<term> variable_term::betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree)
{
	if (varToReplace.getName() == m_variable.getName())
	{
		return subTree->copy();
	}
	else
	{
		return copy();
	}
}