#include "prepostprocessor.h"

prepostprocessor::prepostprocessor()
{
	auto consPair = std::make_pair("Cons", Cons);
	m_lispToLambda.push_back(consPair);
	auto cdrPair = std::make_pair("Cdr", Cdr);
	m_lispToLambda.push_back(cdrPair);
	auto carPair = std::make_pair("Car", Car);
	m_lispToLambda.push_back(carPair);
	auto orPair = std::make_pair("Or", Or);
	m_lispToLambda.push_back(orPair);
	auto andPair = std::make_pair("And", And);
	m_lispToLambda.push_back(andPair);
	auto atomPair = std::make_pair("Atom", Atom);
	m_lispToLambda.push_back(atomPair);
	auto falsePair = std::make_pair("False", False);
	m_lispToLambda.push_back(falsePair);
	auto ifPair = std::make_pair("If", If);
	m_lispToLambda.push_back(ifPair);
	auto nullPair = std::make_pair("Null", Null);
	m_lispToLambda.push_back(nullPair);
	auto trPair = std::make_pair("1\'", Tr);
	m_lispToLambda.push_back(trPair);
	auto nilPair = std::make_pair("0\'", Nil);
	m_lispToLambda.push_back(nilPair);
	auto fPair = std::make_pair("F", F);
	m_lispToLambda.push_back(fPair);
	auto tPair = std::make_pair("T", T);
	m_lispToLambda.push_back(tPair);
	auto yCombPair = std::make_pair("Y", yComb);
	m_lispToLambda.push_back(yCombPair);
	auto loopPair = std::make_pair("Omega", loop);
	m_lispToLambda.push_back(loopPair);
}

void prepostprocessor::preprocess(std::string& inputStr)
{
	for (auto& elem : m_lispToLambda)
	{
		replaceAll(inputStr, elem.first, elem.second);
	}
}

void prepostprocessor::postprocess(std::string& inputStr)
{
	for (auto& elem : m_lispToLambda)
	{
		replaceAll(inputStr, elem.second, elem.first);
	}
}

//copy-paste from https://stackoverflow.com/a/15372760/4222679
void prepostprocessor::replaceAll(std::string &s, const std::string &search, const std::string &replace)
{
	for (size_t pos = 0; ; pos += replace.length())
	{
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == std::string::npos) break;
		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}
