#include "cmath/multiplication.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Multiplication::Multiplication()
	: CommutateOp(Type::MULTIPLICATION, true)
{}

Object_t Multiplication::copy(bool deep)
{
	auto result = std::make_shared<Multiplication>();
	for(std::size_t i = 0; i < getChildCount(); i++) {
		if(deep) {
			result->add(get(i)->copy(deep));
		} else {
			result->add(get(i));
		}
	}
	result->setIsNegative(isNegative());
	return result;
}
} // namespace C


