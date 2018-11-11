#pragma once

#include "term.h"
#include "variable.h"

class variable_term : public term
{
private:
	variable m_variable;

public:
	variable_term(const variable _variable, const termType type = termType::Variable);
	//virtual ~variable_term();

	virtual std::shared_ptr<term> copy() override final;
	virtual void print() const override final;
	virtual std::shared_ptr<term> eval() override final;
	virtual bool isBetaRedex() const override final;
	virtual bool hasBetaRedex() const override final;
	virtual std::set<variable> getFreeVariables() const override final;
	virtual void alphaRenameBy(const variable varToRename, const variable newVar) override final;
	virtual void naiveRenameBy(const variable varToRename, const variable newVar) override final;
	virtual std::shared_ptr<term> betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree) override final;
};