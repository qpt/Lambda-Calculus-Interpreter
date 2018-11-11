#include <iostream>
#include "abstraction_term.h"

abstraction_term::abstraction_term(const variable _capture, const std::shared_ptr<term>& _body,
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

std::shared_ptr<term> abstraction_term::copy()
{
	std::shared_ptr<term>& newBody = m_body->copy();
	return std::make_shared<abstraction_term>(abstraction_term(m_capture, newBody));
}

void abstraction_term::print() const
{
	std::cout << "(L" << m_capture.getName() << ".";
	m_body->print();
	std::cout << ")";
}

std::shared_ptr<term> abstraction_term::eval()
{
	return m_body->eval();
}

bool abstraction_term::isBetaRedex() const
{
	return false;
}

bool abstraction_term::hasBetaRedex() const
{
	return m_body->hasBetaRedex();
}

std::set<variable> abstraction_term::getFreeVariables() const
{
	// FV([x].t) = FV(t) \ {x}
	auto varSet = m_body->getFreeVariables();
	varSet.erase(m_capture);

	return varSet;
}

void abstraction_term::alphaRenameBy(const variable varToRename, const variable newVar)
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

void abstraction_term::naiveRenameBy(const variable varToRename, const variable newVar)
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

std::shared_ptr<term> abstraction_term::betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree)
{
	auto& newBodyTerm = m_body->betaReduce(varToReplace, subTree);
	return std::make_shared<abstraction_term>(abstraction_term(m_capture, newBodyTerm/*->copy()*/));
}

variable abstraction_term::getCapturedVariable() const
{
	return m_capture;
}

std::shared_ptr<term> abstraction_term::getBodyTerm() const
{
	return m_body;
}