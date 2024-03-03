#ifndef CMATH_UTIL_TREE_PRINT_HPP
#define CMATH_UTIL_TREE_PRINT_HPP

#include <stdio.h>

#include <vector>

#include <cmath/visitor.hpp>

namespace CMath {

class TreePrint : public Visitor
{
public:
	TreePrint(FILE *dst = nullptr);

	intptr_t onVisit(Number_t n) override;
	intptr_t onVisit(Variable_t v) override;
	intptr_t onVisit(Function_t f) override;
	intptr_t onVisit(Addition_t a) override;
	intptr_t onVisit(Power_t p) override;
	intptr_t onVisit(Multiplication_t m) override;
	intptr_t onVisit(Fraction_t f)  override;
	intptr_t onVisit(Bracket_t b) override;
	intptr_t onVisit(Derrivative_t d) override;

private:
	void begin(Object_t, const char*, bool);
	void end(Object_t);
	std::vector<int> marker;
	FILE *dst;
};

} // namespace CMath

#endif /* CMATH_UTIL_TREE_PRINT_HPP */
