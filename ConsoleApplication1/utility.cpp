#include "utility.h"
#include <sstream>

std::string misc::to_string(const int i)
{
	std::ostringstream s;
	s << i;
	return std::string(s.str());
}
