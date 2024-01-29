#include "cmath/derrivative.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Derrivative::Derrivative(Object_t a, Object_t b, int order)
    : Operator(Type::DERRIVATIVE, false)
{
    this->a = a;
    this->b = b;
    this->order = order;
    if(a != nullptr) a->setParent(this);
    if(b != nullptr) b->setParent(this);
}

Object_t Derrivative::copy(bool deep)
{
    auto result = std::make_shared<Derrivative>(a->copy(), b->copy());
    result->toggleIsNegative(isNegative());
    return result;
}

void Derrivative::visitChild(Visitor_t mv)
{
	mv->onVisit(a);
	mv->onVisit(b);
}

bool Derrivative::childIs(int index, Type type)
{
	if(index == 0) return a->is(type);
	if(index == 1) return b->is(type);
	return false;
}

bool Derrivative::replace(Object_t old, Object_t _new, Sign sign)
{
	if(old == a) {
		a = _new;
	} else if(old == b) {
		b = _new;
	} else {
		return false;
	}
	return Operator::replace(old, _new, sign);
}

Object_t Derrivative::getA()
{
    return a;
}

Object_t Derrivative::getB()
{
    return b;
}

void Derrivative::setA(Object_t a)
{
    this->a = a;
    if(a != nullptr) a->setParent(this);
}

void Derrivative::setB(Object_t b)
{
    this->b = b;
    if(b != nullptr) b->setParent(this);
}

int Derrivative::getOrder()
{
    return order;
}

void Derrivative::setOrder(int order)
{
    this->order = order;
}
} // namespace C
