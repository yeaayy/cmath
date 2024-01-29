#ifndef CMATH_BINARY_EVALUATOR_HPP
#define CMATH_BINARY_EVALUATOR_HPP

#include <cmath/object.hpp>

namespace CMath {

class BinaryEvaluator
{
public:
    BinaryEvaluator(bool reverseSign, intptr_t defaultReturn);
	virtual intptr_t eval1(Number_t a, Number_t b);

	virtual intptr_t eval0(Variable_t a, Number_t b);
	virtual intptr_t eval1(Variable_t a, Variable_t b);

	virtual intptr_t eval0(Addition_t a, Number_t b);
	virtual intptr_t eval0(Addition_t a, Variable_t b);
	virtual intptr_t eval1(Addition_t a, Addition_t b);

	virtual intptr_t eval0(Multiplication_t a, Number_t b);
	virtual intptr_t eval0(Multiplication_t a, Variable_t b);
	virtual intptr_t eval0(Multiplication_t a, Addition_t b);
	virtual intptr_t eval1(Multiplication_t a, Multiplication_t b);

	virtual intptr_t eval0(Fraction_t a, Number_t b);
	virtual intptr_t eval0(Fraction_t a, Variable_t b);
	virtual intptr_t eval0(Fraction_t a, Addition_t b);
	virtual intptr_t eval0(Fraction_t a, Multiplication_t b);
	virtual intptr_t eval1(Fraction_t a, Fraction_t b);

	virtual intptr_t eval0(Power_t a, Number_t b);
	virtual intptr_t eval0(Power_t a, Variable_t b);
	virtual intptr_t eval0(Power_t a, Addition_t b);
	virtual intptr_t eval0(Power_t a, Multiplication_t b);
	virtual intptr_t eval0(Power_t a, Fraction_t b);
	virtual intptr_t eval1(Power_t a, Power_t b);

	virtual intptr_t eval0(Bracket_t a, Number_t b);
	virtual intptr_t eval0(Bracket_t a, Variable_t b);
	virtual intptr_t eval0(Bracket_t a, Addition_t b);
	virtual intptr_t eval0(Bracket_t a, Multiplication_t b);
	virtual intptr_t eval0(Bracket_t a, Fraction_t b);
	virtual intptr_t eval0(Bracket_t a, Power_t b);
	virtual intptr_t eval1(Bracket_t a, Bracket_t b);

	virtual intptr_t eval0(Function_t a, Number_t b);
	virtual intptr_t eval0(Function_t a, Variable_t b);
	virtual intptr_t eval0(Function_t a, Addition_t b);
	virtual intptr_t eval0(Function_t a, Multiplication_t b);
	virtual intptr_t eval0(Function_t a, Fraction_t b);
	virtual intptr_t eval0(Function_t a, Power_t b);
	virtual intptr_t eval0(Function_t a, Bracket_t b);
	virtual intptr_t eval1(Function_t a, Function_t b);

	virtual intptr_t eval0(Relation_t a, Number_t b);
	virtual intptr_t eval0(Relation_t a, Variable_t b);
	virtual intptr_t eval0(Relation_t a, Addition_t b);
	virtual intptr_t eval0(Relation_t a, Multiplication_t b);
	virtual intptr_t eval0(Relation_t a, Fraction_t b);
	virtual intptr_t eval0(Relation_t a, Power_t b);
	virtual intptr_t eval0(Relation_t a, Bracket_t b);
	virtual intptr_t eval0(Relation_t a, Function_t b);
	virtual intptr_t eval1(Relation_t a, Relation_t b);

	virtual intptr_t eval0(Derrivative_t a, Number_t b);
	virtual intptr_t eval0(Derrivative_t a, Variable_t b);
	virtual intptr_t eval0(Derrivative_t a, Addition_t b);
	virtual intptr_t eval0(Derrivative_t a, Multiplication_t b);
	virtual intptr_t eval0(Derrivative_t a, Fraction_t b);
	virtual intptr_t eval0(Derrivative_t a, Power_t b);
	virtual intptr_t eval0(Derrivative_t a, Bracket_t b);
	virtual intptr_t eval0(Derrivative_t a, Function_t b);
	virtual intptr_t eval0(Derrivative_t a, Relation_t b);
	virtual intptr_t eval1(Derrivative_t a, Derrivative_t b);

	intptr_t eval(Object_t a, Object_t b);
	intptr_t operator() (Object_t a, Object_t b);

protected:
	const bool reverseSign;
    const intptr_t defaultReturn;
};

} // namespace C

#endif /* CMATH_BINARY_EVALUATOR_HPP */
