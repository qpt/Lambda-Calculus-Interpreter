#include "term.h"

term::term(termType type)
	: m_termType(type)
{
}

termType term::getType() const
{
	return m_termType;
}