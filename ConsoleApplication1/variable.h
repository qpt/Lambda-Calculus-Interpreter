#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class variable
{
private:
	std::string m_name;

public:
	variable(const std::string& _name);
	//~variable();
	bool operator<(const variable& rhs) const;

	std::string getName() const;
	void setName(const std::string& newName);
};

#endif // VARIABLE_H