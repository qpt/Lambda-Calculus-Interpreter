#include <iostream>
#include <algorithm>
#include "application_term.h"
#include "abstraction_term.h"

application_term::application_term(const std::shared_ptr<term>& _lhs, const std::shared_ptr<term>& _rhs,
	const termType type)
	: term(type), m_lhs(_lhs), m_rhs(_rhs)
{
}

//application_term::~application_term()
//{
//	std::cout << "Destroy application term: ";
//	print();
//	std::cout << std::endl;
//}

std::shared_ptr<term> application_term::copy()
{
	std::shared_ptr<term>& newLhs = m_lhs->copy();
	std::shared_ptr<term>& newRhs = m_rhs->copy();

	return std::make_shared<application_term>(application_term(newLhs, newRhs));
}

void application_term::print() const
{
	std::cout << "(";
	m_lhs->print();
	std::cout << " ";
	m_rhs->print();
	std::cout << ")";
}

bool application_term::isBetaRedex() const
{
	return m_lhs->getType() == termType::Abstraction;
}

bool application_term::hasBetaRedex() const
{
	return isBetaRedex() || m_lhs->hasBetaRedex() || m_rhs->hasBetaRedex();
}

std::shared_ptr<term> application_term::eval()
{
	if (isBetaRedex())
	{
		std::set<variable> freeVarsRhs = m_rhs->getFreeVariables();

		// construct alpha-congruent left subtree
		for (auto& currentVariable : freeVarsRhs)
		{
			m_lhs->alphaRenameBy(currentVariable, currentVariable.getName() + "'");
		}

		std::shared_ptr<abstraction_term>& reduct = std::dynamic_pointer_cast<abstraction_term>(m_lhs);
		std::shared_ptr<abstraction_term>& reduced = std::dynamic_pointer_cast<abstraction_term>(
			reduct->betaReduce(reduct->getCapturedVariable(), m_rhs));

		return reduced->getBodyTerm();
	}
	else
	{
		m_lhs = m_lhs->eval();
		m_rhs = m_rhs->eval();

		return copy();
	}
}

std::set<variable> application_term::getFreeVariables() const
{
	// FV(t r) = FV(t) U FV(r)
	auto lhsFreeVars = m_lhs->getFreeVariables();
	auto rhsFreeVars = m_rhs->getFreeVariables();

	std::set<variable> unionFreeVars = lhsFreeVars;

	for (auto& currentVariable : rhsFreeVars)
	{
		unionFreeVars.insert(currentVariable);
	}

	return unionFreeVars;
}

void application_term::alphaRenameBy(const variable varToRename, const variable newVar)
{
	// A(t r){x:=y} = A(t{x:=y}) and A(r{x:=y})
	m_lhs->alphaRenameBy(varToRename, newVar);
	m_rhs->alphaRenameBy(varToRename, newVar);
}

void application_term::naiveRenameBy(const variable varToRename, const variable newVar)
{
	m_lhs->naiveRenameBy(varToRename, newVar);
	m_rhs->naiveRenameBy(varToRename, newVar);
}

std::shared_ptr<term> application_term::betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree)
{
	auto& newLhs = m_lhs->betaReduce(varToReplace, subTree);
	auto& newRhs = m_rhs->betaReduce(varToReplace, subTree);

	return std::make_shared<application_term>(application_term(newLhs, newRhs));
}