#include "cmath/object.hpp"

#ifdef TRACE_OBJECT
#include <iostream>
#endif /* TRACE_OBJECT */

#include <ostream>

#include "cmath/operator.hpp"

namespace CMath {

namespace {
int count = 0;
int activeCount = 0;
} // namespace

int Object::getObjectCount()
{
	return activeCount;
}

Object::Object(Type type, bool isNegative)
	: _type(type)
    , _isNegative(isNegative)
{
	_id = count++;
	activeCount++;

#ifdef TRACE_OBJECT
	std::cout << "CMath::Object(" << _id << ")\n";
#endif /* TRACE_OBJECT */
}

Object::~Object()
{
#ifdef TRACE_OBJECT
	std::cout << "CMath::~Object(" << _id << ")\n";
#endif /* TRACE_OBJECT */
	_id = -1;
	activeCount--;
}

int Object::getId()
{
	return _id;
}

Type Object::getType()
{
	return _type;
}

bool Object::is(Type type)
{
	return _type == type;
}

void Object::setIsNegative(bool isNegative)
{
	_isNegative = isNegative;
}

bool Object::isNegative()
{
	return _isNegative;
}

void Object::toggleIsNegative(bool toggle)
{
	if(toggle) {
		_isNegative = !_isNegative;
	}
}

void Object::takeSignFrom(Object_t src) {
	this->_isNegative = src->_isNegative;
	src->_isNegative = false;
}

void Object::aborbSignFrom(Object_t src) {
	toggleIsNegative(src->_isNegative);
	src->_isNegative = false;
}

void Object::copySignFrom(Object_t src) {
	this->_isNegative = src->_isNegative;
}

void Object::swapSignWith(Object_t o) {
	bool c = o->_isNegative;
	o->_isNegative = this->_isNegative;
	this->_isNegative = c;
}


Operator *Object::getParent()
{
	return _parent;
}

void Object::setParent(Operator *parent)
{
    _parent = parent;
}

std::ostream &operator<<(std::ostream& os, Type type) {
    switch(type) {
        case Type::ADDITION: return os << "CMath::Type::ADDITION";
        case Type::MULTIPLICATION: return os << "CMath::Type::MULTIPLICATION";
        case Type::FRACTION: return os << "CMath::Type::FRACTION";
        case Type::POWER: return os << "CMath::Type::POWER";
        case Type::BRACKET: return os << "CMath::Type::BRACKET";
        case Type::RELATION: return os << "CMath::Type::RELATION";
        case Type::NUMBER: return os << "CMath::Type::NUMBER";
        case Type::VARIABLE: return os << "CMath::Type::VARIABLE";
        case Type::FUNCTION: return os << "CMath::Type::FUNCTION";
        case Type::DERRIVATIVE: return os << "CMath::Type::DERRIVATIVE";
        default: return os << "CMath::Type::UNKNOWN(" << ((int) type) << ")";
    }
}

} // namespace CMath
