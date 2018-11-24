#pragma once
#include "term.h"
#include <memory>

class abstractionTerm : public term
{
private:
	variable m_capture;
	std::shared_ptr<term> m_body;

public:
	abstractionTerm(const variable _capture, const std::shared_ptr<term>& _body, 
		const termType type = termType::Abstraction);
	//virtual ~abstraction_term();

	virtual std::shared_ptr<term> copy() override final;
	virtual void print() const override final;
	virtual std::shared_ptr<term> eval() override final;
	virtual bool isBetaRedex() const override final;
	virtual bool hasBetaRedex() const override final;
	virtual std::set<variable> getFreeVariables() const override final;
	virtual void alphaRenameBy(const variable varToRename, const variable newVar) override final;
	virtual void naiveRenameBy(const variable varToRename, const variable newVar) override final;
	virtual std::shared_ptr<term> betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree,
		const bool isReduct) override final;

	variable getCapturedVariable() const;
	std::shared_ptr<term> getBodyTerm() const;
};