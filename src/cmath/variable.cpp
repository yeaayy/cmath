#include "cmath/variable.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Variable::Variable(std::string name, bool isNegative)
	: Object(Type::VARIABLE, isNegative)
    , _name(name)
{
}

Variable::~Variable()
{
}

Object_t Variable::copy(bool deep)
{
	return std::make_shared<Variable>(_name, isNegative());
}

void Variable::setName(const char *name)
{
    _name = name;
}

std::string &Variable::getName()
{
	return _name;
}

} // namespace C


