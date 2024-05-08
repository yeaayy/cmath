#include "cmath/commutate_op.hpp"

#include <cassert>

#include "cmath/visitor.hpp"

namespace CMath {

CommutateOp::CommutateOp(Type type, bool absorbSign)
	: Operator(type, false)
    , absorbSign(absorbSign)
{
}

bool CommutateOp::childIs(int index, Type type)
{
	return childrens[index]->is(type);
}

void CommutateOp::visitChild(Visitor_t v)
{
	// Do not use iterator, child node might change during visit
	for(size_t i = 0; i < childrens.size(); i++) {
		v->visit(childrens[i]);
	}
}

int CommutateOp::indexOf(Object_t &obj)
{
	for(std::size_t i=0; i<childrens.size(); i++) {
		if(childrens[i] == obj) {
			return i;
		}
	}
	return -1;
}

bool CommutateOp::replace(Object_t old, Object_t _new, Sign sign)
{
	int index = indexOf(old);
	if(index == -1) return false;
	if(_new == nullptr) {
		remove(index);
		old->setParent(nullptr);
		return true;
	}
	if(!_new->is(_type)) {
		childrens[index] = _new;
		return Operator::replace(old, _new, sign);
	}
	auto child = std::static_pointer_cast<CommutateOp>(_new);
	child->aborbSignFrom(old);
	remove(index);
	for(int i = child->childrens.size() - 1; i >= 0; i--) {
		if(!absorbSign) child->childrens[i]->toggleIsNegative(child->isNegative());
		insert(index, child->childrens[i]);
	}
	child->setIsNegative(false);
	return true;
}

std::size_t CommutateOp::getChildCount()
{
	return childrens.size();
}

bool CommutateOp::remove(int index)
{
    childrens.erase(childrens.begin() + index);
	return true;
}

void CommutateOp::clearChild()
{
	childrens.clear();
}

Object_t &CommutateOp::get(int index)
{
	return childrens[index];
}

void CommutateOp::add(Object_t o)
{
	if(o == nullptr) return;
	if(o->is(_type)) {
		auto obj = std::static_pointer_cast<CommutateOp>(o);
		for(auto &child : obj->childrens) {
			childrens.push_back(child);
			child->setParent(this);
			if(absorbSign) this->aborbSignFrom(child);
		}
		if(absorbSign) this->aborbSignFrom(o);
	} else {
		childrens.push_back(o);
		o->setParent(this);
		if(absorbSign) this->aborbSignFrom(o);
	}
}

void CommutateOp::insert(size_t index, Object_t o)
{
	assert(index <= getChildCount());
	if(o->is(_type)) {
		auto obj = std::static_pointer_cast<CommutateOp>(o);
		auto target = childrens.begin() + index;
		for(auto &child : obj->childrens) {
			childrens.insert(target, child);
			child->setParent(this);
			if(absorbSign) this->aborbSignFrom(child);
			target++;
		}
	} else {
		childrens.insert(childrens.begin() + index, o);
		o->setParent(this);
		if(absorbSign) this->aborbSignFrom(o);
	}
}

} // namespace C
