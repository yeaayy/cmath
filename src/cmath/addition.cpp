#include "cmath/addition.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Addition::Addition()
	: CommutateOp(Type::ADDITION, false)
{
}

Object_t Addition::copy(bool deep)
{
	Addition_t result = std::make_shared<Addition>();
	for(auto child : childrens) {
		if(deep) {
			result->add(child->copy(deep));
		} else {
			result->add(child);
		}
	}
	result->setIsNegative(isNegative());
	return result;
}
} // namespace CMath


