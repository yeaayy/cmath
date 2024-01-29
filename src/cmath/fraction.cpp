#include "cmath/fraction.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Fraction::Fraction(Object_t a, Object_t b, bool isNegative)
	: Operator(Type::FRACTION, isNegative)
    , _a(a)
    , _b(b)
{
	a->setParent(this);
	b->setParent(this);
}

void Fraction::visitChild(Visitor_t mv)
{
	mv->onVisit(_a);
	mv->onVisit(_b);
}

bool Fraction::childIs(int index, Type type)
{
	if(index == 0) return _a->is(type);
	if(index == 1) return _b->is(type);
	return false;
}

bool Fraction::replace(Object_t old, Object_t _new, Sign sign)
{
	if(old == _a) {
		_a = _new;
	} else if(old == _b) {
		_b = _new;
	} else {
		return false;
	}
	return Operator::replace(old, _new, sign);
}

Object_t Fraction::copy(bool deep)
{
	Fraction_t result;
	if(deep) {
		result.reset(new Fraction(_a->copy(deep), _b->copy(deep)));
	} else {
		result.reset(new Fraction(_a, _b));
	}
	result->setIsNegative(isNegative());
	return result;
}

Object_t Fraction::getA()
{
	return _a;
}

Object_t Fraction::getB()
{
	return _b;
}

void Fraction::setA(Object_t a)
{
	_a = a;
	a->setParent(this);
}

void Fraction::setB(Object_t b)
{
	_b = b;
	b->setParent(this);
}
} // namespace C


