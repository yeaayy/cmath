#include "cmath/function.hpp"

#include "cmath/visitor.hpp"

namespace CMath {

Function::Function(std::string &name, std::vector<Object_t> *args, bool copy, bool deep)
	: Operator(Type::FUNCTION, false)
{
	_name = name;
	for(std::size_t i=0; i<args->size(); i++) {
		if(copy) {
			_args.push_back(args->at(i)->copy(deep));
		} else {
			_args.push_back(args->at(i));
		}
		_args[i]->setParent(this);
	}
}

Function::~Function()
{
}

void Function::visitChild(Visitor_t mv)
{
	for(std::size_t i=0; i<_args.size(); i++) {
		mv->onVisit(_args[i]);
	}
}

bool Function::childIs(int index, Type type)
{
	return _args[index]->is(type);
}

Object_t Function::copy(bool deep)
{
	auto result = std::make_shared<Function>(_name, &_args, true);
	result->setIsNegative(isNegative());
	return result;
}

bool Function::replace(Object_t old, Object_t _new, Sign sign)
{
	for(std::size_t i=0; i<_args.size(); i++) {
		if(_args[i] == old) {
			if(_new == nullptr) {
				_args.erase(_args.begin() + i);
				old->setParent(nullptr);
				return true;
			} else {
				_args[i] = _new;
				return Operator::replace(old, _new, sign);
			}
		}
	}
	return false;
}

void Function::setName(std::string &name)
{
	_name = name;
}

std::string &Function::getName()
{
	return _name;
}

std::size_t Function::getArgumentCount()
{
	return _args.size();
}

void Function::setArgument(int index, Object_t arg)
{
	_args[index] = arg;
}

Object_t Function::getArgument(int index)
{
	return _args[index];
}

} // namespace C
