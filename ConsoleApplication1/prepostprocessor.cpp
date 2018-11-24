#include "prepostprocessor.h"

prepostprocessor::prepostprocessor()
{
	auto& consPair1 = std::make_pair("Cons", Cons);
	m_lispToLambda.push_back(consPair1);
	auto& cdrPair1 = std::make_pair("Cdr", Cdr);
	m_lispToLambda.push_back(cdrPair1);
	auto& carPair1 = std::make_pair("Car", Car);
	m_lispToLambda.push_back(carPair1);
	auto& orPair1 = std::make_pair("Or", Or);
	m_lispToLambda.push_back(orPair1);
	auto& andPair1 = std::make_pair("And", And);
	m_lispToLambda.push_back(andPair1);
	auto& atomPair1 = std::make_pair("Atom", Atom);
	m_lispToLambda.push_back(atomPair1);
	auto& falsePair1 = std::make_pair("False", False);
	m_lispToLambda.push_back(falsePair1);
	auto& ifPair1 = std::make_pair("If", If);
	m_lispToLambda.push_back(ifPair1);
	auto& nullPair1 = std::make_pair("Null", Null);
	m_lispToLambda.push_back(nullPair1);
	auto& trPair1 = std::make_pair("1\'", Tr);
	m_lispToLambda.push_back(trPair1);
	auto& nilPair1 = std::make_pair("0\'", Nil);
	m_lispToLambda.push_back(nilPair1);
	auto& fPair1 = std::make_pair("F", F);
	m_lispToLambda.push_back(fPair1);
	auto& tPair1 = std::make_pair("T", T);
	m_lispToLambda.push_back(tPair1);
	auto& yCombPair1 = std::make_pair("Y", yComb);
	m_lispToLambda.push_back(yCombPair1);
	auto& loopPair1 = std::make_pair("Omega", loop);
	m_lispToLambda.push_back(loopPair1);
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