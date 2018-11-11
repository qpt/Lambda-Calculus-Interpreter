#include <iostream>
#include "variable.h"

variable::variable(const std::string& _name)
	: m_name(_name)
{
}

variable::~variable()
{
	//std::cout << "Destroy variable: " << m_name << std::endl;
}

bool variable::operator<(const variable& rhs) const
{
	return m_name < rhs.getName();
}

std::string variable::getName() const
{
	return m_name;
}

void variable::setName(const std::string& newName)
{
	m_name = newName;
}