#include "cmath/relation.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Relation::Relation(Object_t a, Object_t b, Relation::Type type)
	: Operator(CMath::Type::RELATION, false)
    , _a(a)
    , _b(b)
    , _type(type)
{
	a->setParent(this);
	b->setParent(this);
}

void Relation::visitChild(Visitor_t v)
{
	v->visit(_a);
	v->visit(_b);
}

Object_t Relation::copy(bool deep)
{
    Relation_t result;
	if(deep) {
		result.reset(new Relation(_a->copy(deep), _b->copy(deep), _type));
	} else {
		result.reset(new Relation(_a, _b, _type));
	}
    return result;
}

bool Relation::childIs(int index, CMath::Type type)
{
	if(index == 0) return _a->is(type);
	if(index == 1) return _b->is(type);
	return false;
}

Object_t Relation::getA()
{
	return _a;
}

Object_t Relation::getB()
{
	return _b;
}

void Relation::setA(Object_t a)
{
	_a = a;
	a->setParent(this);
}

void Relation::setB(Object_t b)
{
	_b = b;
	b->setParent(this);
}

Relation::Type Relation::getRelationType()
{
	return _type;
}

void Relation::setRelationType(Relation::Type type)
{
	_type = type;
}

} // namespace C
