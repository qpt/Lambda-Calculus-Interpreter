#include <iostream>
#include "abstractionTerm.h"

abstractionTerm::abstractionTerm(const variable _capture, const std::shared_ptr<term>& _body,
	const termType type)
	: term(type), m_capture(_capture), m_body(_body)
{
}

//abstraction_term::~abstraction_term()
//{
//	std::cout << "Destroy abstraction term: ";
//	print();
//	std::cout << std::endl;
//}

std::shared_ptr<term> abstractionTerm::copy()
{
	std::shared_ptr<term>& newBody = m_body->copy();
	return std::make_shared<abstractionTerm>(abstractionTerm(m_capture, newBody));
}

std::string abstractionTerm::toString() const
{
	return "(L" + m_capture.getName() + "." + m_body->toString() + ")";
}

void abstractionTerm::print() const
{
	std::cout << toString();
}

std::shared_ptr<term> abstractionTerm::eval()
{
	return std::make_shared<abstractionTerm>(abstractionTerm(m_capture, m_body->eval()));
}

bool abstractionTerm::isBetaRedex() const
{
	return false;
}

bool abstractionTerm::hasBetaRedex() const
{
	return m_body->hasBetaRedex();
}

std::set<variable> abstractionTerm::getFreeVariables() const
{
	// FV([x].t) = FV(t) \ {x}
	auto varSet = m_body->getFreeVariables();
	varSet.erase(m_capture);

	return varSet;
}

void abstractionTerm::alphaRenameBy(const variable varToRename, const variable newVar)
{
	// A([x].t){y:=z} = { [z].t{y:=z}    if y == x
	//                    [x].t{y:=z}    else
	if (m_capture.getName() == varToRename.getName())
	{
		m_capture.setName(newVar.getName());
		m_body->naiveRenameBy(varToRename, newVar);
	}
	else
	{
		m_body->alphaRenameBy(varToRename, newVar);
	}
}

void abstractionTerm::naiveRenameBy(const variable varToRename, const variable newVar)
{
	if (m_capture.getName() == varToRename.getName())
	{
		m_capture.setName(newVar.getName() + "'");
		m_body->naiveRenameBy(varToRename, newVar.getName() + "'");
		return;
	}
	else
	{
		m_body->naiveRenameBy(varToRename, newVar);
	}
}

std::shared_ptr<term> abstractionTerm::betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree,
	const bool isReduct)
{
	if (!isReduct && m_capture.getName() == varToReplace.getName())
	{
		return std::make_shared<abstractionTerm>(abstractionTerm(m_capture, m_body));//copy();
	}

	auto& newBodyTerm = m_body->betaReduce(varToReplace, subTree, false);
	return std::make_shared<abstractionTerm>(abstractionTerm(m_capture, newBodyTerm/*->copy()*/));
}

variable abstractionTerm::getCapturedVariable() const
{
	return m_capture;
}

std::shared_ptr<term> abstractionTerm::getBodyTerm() const
{
	return m_body;
}