#ifndef CMATH_OPERATOR_HPP
#define CMATH_OPERATOR_HPP

#include "cmath/object.hpp"

namespace CMath {

class Operator : public Object
{
public:
	Operator(Type type, bool isNegative);
	virtual void visitChild(Visitor_t mv) = 0;
	virtual bool childIs(int index, Type type) = 0;
	virtual bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB);
};

} // namespace CMath

#endif /* CMATH_OPERATOR_HPP */
