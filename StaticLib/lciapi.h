#ifndef LCIAPI_H
#define LCIAPI_H
#include <memory>
#include "../Interpreter/term.h"

namespace lci
{
	// input - Here's one example "(Lx.x)(Ly.y)"
	// isProcessed - This boolean should be set to `true` if we want to parse McCarthy functions as well
	//
	// Note that this function might run forever for countably infinite number of cases,
	// so it is better to run it on a separate thread and use some kind of producer-consumer pattern!
	std::string getNormalForm(const std::string& input, const bool isProcessed);
}

#endif // LCIAPI_H
