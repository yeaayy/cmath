#include "cmath/operator.hpp"

namespace CMath {

Operator::Operator(Type type, bool isNegative)
    : Object(type, isNegative)
{}

bool Operator::replace(Object_t old, Object_t _new, Sign sign)
{
	switch(sign) {
	case Sign::ABSORB: _new->aborbSignFrom(old); break;
	case Sign::TAKE: _new->takeSignFrom(old); break;
	case Sign::COPY: _new->copySignFrom(old); break;
	case Sign::SWAP: _new->swapSignWith(old); break;
	}
    _new->setParent(this);
	old->setParent(nullptr);
	return true;
}

} // namespace CMath


