#ifndef CMATH_COMPARATOR_HPP
#define CMATH_COMPARATOR_HPP

#include "cmath/binary_evaluator.hpp"

namespace CMath {

class Comparator : protected BinaryEvaluator
{
public:
	static intptr_t test(Object_t a, Object_t b);
	static intptr_t testUnsigned(Object_t a, Object_t b);
    static Comparator &get();

protected:
	intptr_t eval1(Number_t a, Number_t b) override;
	intptr_t eval1(Variable_t a, Variable_t b) override;
	intptr_t eval1(Addition_t a, Addition_t b) override;
	intptr_t eval1(Multiplication_t a, Multiplication_t b) override;
	intptr_t eval1(Fraction_t a, Fraction_t b) override;
	intptr_t eval1(Power_t a, Power_t b) override;
	intptr_t eval1(Bracket_t a, Bracket_t b) override;
	intptr_t eval1(Function_t a, Function_t b) override;
	intptr_t eval1(Relation_t a, Relation_t b) override;
	intptr_t eval1(Derrivative_t a, Derrivative_t b) override;

private:
	Comparator();
    static Comparator *instance;
};

} // namespace C

#endif /* CMATH_COMPARATOR_HPP */
