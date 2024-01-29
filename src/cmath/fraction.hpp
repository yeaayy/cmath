#ifndef CMATH_FRACTION_HPP
#define CMATH_FRACTION_HPP

#include "cmath/operator.hpp"

namespace CMath {

class Fraction : public Operator
{
public:
	Fraction(Object_t a, Object_t b, bool isNegative = false);
	void visitChild(Visitor_t mv) override;
	bool childIs(int index, Type type) override;
	bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB) override;
	Object_t copy(bool deep = true) override;
	Object_t getA();
	Object_t getB();
	void setA(Object_t a);
	void setB(Object_t b);

private:
	Object_t _a;
	Object_t _b;
};

} // namespace C

#endif /* CMATH_FRACTION_HPP */
