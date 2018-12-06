#ifndef APPLICATIONTERM_H
#define APPLICATIONTERM_H

#include <memory>
#include "term.h"
#include "variable.h"

class applicationTerm : public term
{
	std::shared_ptr<term> m_lhs;
	std::shared_ptr<term> m_rhs;

public:
	applicationTerm(const std::shared_ptr<term>& _lhs, const std::shared_ptr<term>& _rhs,
		const termType type = termType::Application);
	//virtual ~application_term();

	virtual std::shared_ptr<term> copy() const override final;
	virtual std::string toString() const override final;
	virtual void print() const override final;
	virtual std::shared_ptr<term> eval() override final;
	virtual bool isBetaRedex() const override final;
	virtual bool hasBetaRedex() const override final;
	virtual std::set<variable> getFreeVariables() const override final;
	virtual void alphaRenameBy(const variable varToRename, const variable newVar) override final;
	virtual void naiveRenameBy(const variable varToRename, const variable newVar) override final;
	virtual std::shared_ptr<term> betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree,
		const bool isReduct) override final;
};

#endif // APPLICATIONTERM_H