#ifndef VARIABLETERM_H
#define VARIABLETERM_H

#include "term.h"
#include "variable.h"

class variableTerm : public term
{
private:
	variable m_variable;

public:
	variableTerm(const variable _variable, const termType type = termType::Variable);
	//virtual ~variable_term();

	virtual std::shared_ptr<term> copy() override final;
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

#endif // VARIABLETERM_H