#ifndef PREPOSTPROCESSOR_H
#define PREPOSTPROCESSOR_H

#include <string>
#include <vector>
#include <utility>

class prepostprocessor
{
	const std::string loop  = "((Lx.(x x)) (Lx.(x x)))";
	const std::string yComb = "(Lf.((Lx.(f (x x))) (Lx.(f (x x)))))";
	const std::string T     = "(Lx.(Ly.x))";
	const std::string F     = "(Lx.(Ly.y))";
	const std::string Nill   = "(Lx.x)";
	const std::string Tr    = "(Lx.((x (Lx.(Ly.y))) (Lx.x)))";
	const std::string Null  = "(Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x)))))";
	const std::string If    = "(Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly"
							  ".y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z))))";
	const std::string False = "(Lx.((((x (Lx.(Ly.(Lz.(Lx.x))))) (Lx.(Ly.x))) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) (Lx"
							  ".(Ly.y))))";
	const std::string Atom  = "(Lx.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x "
							  "(Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (L"
							  "x.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x)) (Lx.((x (Lx.(Ly.y))) (Lx."
							  "x)))) ((Lx.((((x (Lx.(Ly.(Lz.(Lx.x))))) (Lx.(Ly.x))) (Lx.((x (Lx.(Ly.y))) (Lx.x)"
							  "))) (Lx.(Ly.y)))) (x (Lx.(Ly.x))))))";
	const std::string And   = "(Lx.(Ly.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx."
							  "((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))"
							  ") (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x)) x) y)))";
	const std::string Or    = "(Lx.(Ly.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx."
							  "((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))"
							  ") (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x)) y) x)))";
	const std::string Car   = "(Lx.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x "
							  "(Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)))) ((Lx.((((Lx.(Ly.(Lz.(((((Lx.((("
							  "(x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx"
							  ".(Ly.x))) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx"
							  ".(Ly.y))) (Lx.x))))) x)) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) ((Lx.((((x (Lx.(Ly.(Lz.("
							  "Lx.x))))) (Lx.(Ly.x))) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) (Lx.(Ly.y)))) (x (Lx.(Ly.x"
							  ")))))) x)) ((Lx.(x x)) (Lx.(x x)))) (x (Lx.(Ly.x)))))";
	const std::string Cdr   = "(Lx.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x "
							  "(Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)))) ((Lx.((((Lx.(Ly.(Lz.(((((Lx.((("
							  "(x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx"
							  ".(Ly.x))) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx"
							  ".(Ly.y))) (Lx.x))))) x)) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) ((Lx.((((x (Lx.(Ly.(Lz.("
							  "Lx.x))))) (Lx.(Ly.x))) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) (Lx.(Ly.y)))) (x (Lx.(Ly.x"
							  ")))))) x)) ((Lx.(x x)) (Lx.(x x)))) (x (Lx.(Ly.y)))))";
	const std::string Cons =  "(Lx.(Ly.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx."
							  "((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)))) (((Lx.(Ly.((((Lx.(Ly.(Lz.(("
							  "(((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x)))"
							  ")) x) (Lx.(Ly.x))) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (L"
							  "x.((x (Lx.(Ly.y))) (Lx.x))))) x)) x) y))) ((Lx.((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx."
							  "(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x)"
							  ")) y) z)))) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y)"
							  ")) (Lx.x))))) x)) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) ((Lx.((((x (Lx.(Ly.(Lz.(Lx.x)))"
							  ")) (Lx.(Ly.x))) (Lx.((x (Lx.(Ly.y))) (Lx.x)))) (Lx.(Ly.y)))) (x (Lx.(Ly.x)))))) "
							  "y)) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x"
							  "))))) ((Lx.((((x (Lx.(Ly.(Lz.z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx"
							  ".x))))) y)))) ((Lx.(x x)) (Lx.(x x)))) ((((Lx.(Ly.(Lz.(((((Lx.((((x (Lx.(Ly.(Lz."
							  "z)))) (Lx.(Ly.x))) (Lx.x)) (Lx.((x (Lx.(Ly.y))) (Lx.x))))) x) (Lx.(Ly.x))) y) z)"
							  "))) x) (Lz.((z x) y))) (Lz.((z x) y))))))";

	using stringPair = std::pair<std::string, std::string>;
	std::vector<stringPair> m_lispToLambda;

public:
	prepostprocessor();

	void preprocess(std::string& inputStr);
	void postprocess(std::string& inputStr);
	void replaceAll(std::string &s, const std::string &search, const std::string &replace);
};

#endif // PREPOSTPROCESSOR_H
