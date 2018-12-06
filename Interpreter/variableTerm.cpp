#include <iostream>
#include "variableTerm.h"

variableTerm::variableTerm(const variable _variable, const termType type)
	: term(type), m_variable(_variable)
{
}

//variable_term::~variable_term()
//{
//	std::cout << "Destroy variable term: ";
//	print();
//	std::cout << std::endl;
//}

std::shared_ptr<term> variableTerm::copy() const
{
	return std::make_shared<variableTerm>(variableTerm(m_variable));
}

std::string variableTerm::toString() const
{
	return m_variable.getName();
}

void variableTerm::print() const
{
	std::cout << toString();
}

std::shared_ptr<term> variableTerm::eval()
{
	return copy();
}

bool variableTerm::isBetaRedex() const
{
	return false;
}

bool variableTerm::hasBetaRedex() const
{
	return false;
}

std::set<variable> variableTerm::getFreeVariables() const
{
	// FV(x) = {x}
	auto varSet = std::set<variable>();
	varSet.insert(m_variable);

	return varSet;
}

void variableTerm::alphaRenameBy(const variable varToRename, const variable newVar)
{
	// This variable is free
	return;
}

void variableTerm::naiveRenameBy(const variable varToRename, const variable newVar)
{
	// Naive rename only bound variables
	if (m_variable.getName() == varToRename.getName())
	{
		m_variable.setName(newVar.getName());
	}
}

std::shared_ptr<term> variableTerm::betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree,
	const bool isReduct)
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