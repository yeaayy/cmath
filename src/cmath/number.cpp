#include "cmath/number.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Number::Number(uint32_t value, bool isNegative)
	: Object(Type::NUMBER, isNegative)
    , _value(value)
{
}

Object_t Number::copy(bool deep)
{
	return std::make_shared<Number>(_value, _isNegative);
}

void Number::setValue(uint32_t value)
{
	_value = value;
}

void Number::setValueSigned(int value)
{
	_isNegative = value < 0;
	_value = _isNegative ? -value : value;
}

uint32_t Number::getValue()
{
	return _value;
}

int Number::getValueSigned()
{
	return isNegative() ? -_value : _value;
}

} // namespace CMath
