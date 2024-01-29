#ifndef CMATH_POWER_HPP
#define CMATH_POWER_HPP

#include "cmath/operator.hpp"

namespace CMath {

class Power : public Operator
{
public:
	Power(Object_t base = nullptr, Object_t exp = nullptr, bool isNegative = false);
	void visitChild(Visitor_t mv) override;
	bool childIs(int index, Type type) override;
	bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB) override;
	Object_t copy(bool deep = true) override;
	Object_t getBase();
	void setBase(Object_t base);
	Object_t getExponent();
	void setExponent(Object_t exp);

private:
	Object_t _base;
	Object_t _exp;
};

} // namespace C

#endif /* CMATH_POWER_HPP */
