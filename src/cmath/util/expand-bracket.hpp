#ifndef CMATH_UTIL_EXPAND_BRACKET_HPP
#define CMATH_UTIL_EXPAND_BRACKET_HPP

#include "cmath/visitor.hpp"

namespace CMath {

class ExpandBracket : public Visitor
{
public:
	ExpandBracket(bool recursive = true);
	intptr_t onVisit(Multiplication_t m) override;
	void expand(Multiplication_t m, size_t childIndex);
	bool isRecursive();
	void setRecursive(bool);

private:
	bool recursive;
};

} // namespace CMath

#endif /* CMATH_UTIL_EXPAND_BRACKET_HPP */
