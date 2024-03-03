#ifndef CMATH_VISITOR_HPP
#define CMATH_VISITOR_HPP

#include "cmath/object.hpp"

namespace CMath {

class Visitor
{
public:
	virtual intptr_t onVisit(Number_t f);
	virtual intptr_t onVisit(Variable_t a);
	virtual intptr_t onVisit(Function_t f);
	virtual intptr_t onVisit(Addition_t a);
	virtual intptr_t onVisit(Power_t p);
	virtual intptr_t onVisit(Multiplication_t m);
	virtual intptr_t onVisit(Fraction_t f);
	virtual intptr_t onVisit(Bracket_t b);
	virtual intptr_t onVisit(Relation_t r);
	virtual intptr_t onVisit(Derrivative_t d);
	intptr_t visit(Object_t o);
};

} // namespace CMath

#endif /* CMATH_VISITOR_HPP */
