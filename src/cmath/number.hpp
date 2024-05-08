#ifndef CMATH_NUMBER_HPP
#define CMATH_NUMBER_HPP

#include "cmath/object.hpp"

namespace CMath {

class Number : public Object
{
public:
	Number(uint32_t value, bool isNegative = false);

	Object_t copy(bool deep = false) override;
	void setValue(uint32_t value);
	void setValueSigned(int value);
	uint32_t getValue();
	int getValueSigned();

private:
	uint32_t _value;
};

} // namespace CMath

#endif /* CMATH_NUMBER_HPP */
