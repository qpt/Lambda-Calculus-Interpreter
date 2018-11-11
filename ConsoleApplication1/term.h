#pragma once
#include <memory>
#include <set>
#include "variable.h"

enum class termType : char
{
	Variable,
	Application,
	Abstraction,
};

class term
{
protected:
	termType m_termType;

public:
	term(termType type);
	//virtual ~term() = 0 {};

	termType getType() const;
	virtual std::shared_ptr<term> copy() = 0;
	virtual std::shared_ptr<term> eval() = 0;
	virtual void print() const = 0;
	virtual bool isBetaRedex() const = 0;
	virtual bool hasBetaRedex() const = 0;
	virtual std::set<variable> getFreeVariables() const = 0;
	virtual void alphaRenameBy(const variable varToRename, const variable newVar) = 0;
	virtual void naiveRenameBy(const variable varToRename, const variable newVar) = 0;
	virtual std::shared_ptr<term> betaReduce(const variable varToReplace, const std::shared_ptr<term>& subTree) = 0;
};