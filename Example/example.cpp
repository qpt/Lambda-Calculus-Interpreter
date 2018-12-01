#include <iostream>
#include <thread>
#include "../StaticLib/lciapi.h"

int main()
{
	std::string normalForm = lci::getNormalForm("(Lx.x)", false);
	std::string normalFormProcessed = lci::getNormalForm("0'", true);

	std::cout << normalForm << std::endl << normalFormProcessed << std::endl;

	return 0;
}