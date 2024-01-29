#ifndef CMATH_BRACKET_HPP
#define CMATH_BRACKET_HPP

#include "cmath/operator.hpp"

namespace CMath {

class Bracket : public Operator
{
public:
	Bracket(Object_t value = nullptr, bool isNegative = false);
	void visitChild(Visitor_t mv) override;
	Object_t copy(bool deep = true) override;
	bool childIs(int index, Type type) override;
	bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB) override;
	Object_t getValue();
	void setValue(Object_t value);

private:
	Object_t _value;
};

} // namespace CMath

#endif /* CMATH_BRACKET_HPP */
