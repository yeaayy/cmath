#include "cmath/bracket.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Bracket::Bracket(Object_t value, bool isNegative)
	: Operator(Type::BRACKET, isNegative)
    , _value(value)
{
	if(_value != nullptr) _value->setParent(this);
}

void Bracket::visitChild(Visitor_t mv)
{
	mv->onVisit(_value);
}

Object_t Bracket::copy(bool deep)
{
	Bracket_t result;
	if(deep) {
		result.reset(new Bracket(_value->copy(deep)));
	} else {
		result.reset(new Bracket(_value));
	}
	result->setIsNegative(isNegative());
	return result;
}

bool Bracket::childIs(int index, Type type)
{
	if(index == 0) return _value->is(type);
	return false;
}

bool Bracket::replace(Object_t old, Object_t _new, Sign sign)
{
	if(_value == old) {
		_value = _new;
		return Operator::replace(old, _new, sign);
	}
	return false;
}

Object_t Bracket::getValue()
{
	return _value;
}

void Bracket::setValue(Object_t value)
{
	_value = value;
	if(value != nullptr) {
		value->setParent(this);
	}
}

} // namespace C


