#include "cmath/power.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Power::Power(Object_t base, Object_t exp, bool isNegative)
	: Operator(Type::POWER, isNegative)
    , _base(base)
    , _exp(exp)
{
	if(base != nullptr) base->setParent(this);
	if(exp != nullptr) exp->setParent(this);
}

void Power::visitChild(Visitor_t mv)
{
	mv->onVisit(_base);
	mv->onVisit(_exp);
}

bool Power::childIs(int index, Type type)
{
	if(index == 0) return _base->is(type);
	if(index == 1) return _exp->is(type);
	return false;
}

bool Power::replace(Object_t old, Object_t _new, Sign sign)
{
	if(old == _exp) {
		_exp = _new;
	} else if(old == _base) {
		_base = _new;
	} else {
		return false;
	}
	return Operator::replace(old, _new, sign);
}

Object_t Power::copy(bool deep)
{
	Power_t result;
	if(deep) {
		result.reset(new Power(_base->copy(deep), _exp->copy(deep)));
	} else {
		result.reset(new Power(_base, _exp));
	}
	result->setIsNegative(isNegative());
	return result;
}

Object_t Power::getBase()
{
	return _base;
}

void Power::setBase(Object_t base)
{
	_base = base;
	base->setParent(this);
}

Object_t Power::getExponent()
{
	return _exp;
}

void Power::setExponent(Object_t exp)
{
	_exp = exp;
	exp->setParent(this);
}

} // namespace C


