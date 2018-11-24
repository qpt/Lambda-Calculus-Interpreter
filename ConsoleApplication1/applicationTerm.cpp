#include <iostream>
#include <algorithm>
#include "applicationTerm.h"
#include "abstractionTerm.h"

applicationTerm::applicationTerm(const std::shared_ptr<term>& _lhs, const std::shared_ptr<term>& _rhs,
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

std::shared_ptr<term> applicationTerm::copy() const
{
	std::shared_ptr<term>& newLhs = m_lhs->copy();
	std::shared_ptr<term>& newRhs = m_rhs->copy();

	return std::make_shared<applicationTerm>(applicationTerm(newLhs, newRhs));
}

std::string applicationTerm::toString() const
{
	return "(" + m_lhs->toString() + " " + m_rhs->toString() + ")";
}

void applicationTerm::print() const
{
	std::cout << toString();
}

bool applicationTerm::isBetaRedex() const
{
	return m_lhs->getType() == termType::Abstraction;
}

bool applicationTerm::hasBetaRedex() const
{
	return isBetaRedex() || m_lhs->hasBetaRedex() || m_rhs->hasBetaRedex();
}

std::shared_ptr<term> applicationTerm::eval()
{
	if (isBetaRedex())
	{
		std::set<variable> freeVarsRhs = m_rhs->getFreeVariables();

		// construct alpha-congruent left subtree
		for (auto& currentVariable : freeVarsRhs)
		{
			m_lhs->alphaRenameBy(currentVariable, currentVariable.getName() + "'");
		}

		std::shared_ptr<abstractionTerm>& reduct = std::dynamic_pointer_cast<abstractionTerm>(m_lhs);
		std::shared_ptr<abstractionTerm>& reduced = std::dynamic_pointer_cast<abstractionTerm>(
			reduct->betaReduce(reduct->getCapturedVariable(), m_rhs, true));

		return reduced->getBodyTerm();
	}
	else
	{
		m_lhs = m_lhs->eval();
		m_rhs = m_rhs->eval();

		return std::make_shared<applicationTerm>(applicationTerm(m_lhs, m_rhs));// copy();
	}
}

std::set<variable> applicationTerm::getFreeVariables() const
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

void applicationTerm::alphaRenameBy(const variable varToRename, const variable newVar)
{
	// A(t r){x:=y} = A(t{x:=y}) and A(r{x:=y})
	m_lhs->alphaRenameBy(varToRename, newVar);
	m_rhs->alphaRenameBy(varToRename, newVar);
}

void applicationTerm::naiveRenameBy(const variable varToRename, const variable newVar)
{
	m_lhs->naiveRenameBy(varToRename, newVar);
	m_rhs->naiveRenameBy(varToRename, newVar);
}

std::shared_ptr<term> applicationTerm::betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree,
	const bool isReduct)
{
	auto& newLhs = m_lhs->betaReduce(varToReplace, subTree, isReduct);
	auto& newRhs = m_rhs->betaReduce(varToReplace, subTree, isReduct);

	return std::make_shared<applicationTerm>(applicationTerm(newLhs, newRhs));
}