#include "cmath/util/add-term.hpp"

#include "cmath/addition.hpp"
#include "cmath/comparator.hpp"
#include "cmath/number.hpp"
#include "cmath/multiplication.hpp"
#include "cmath/visitor.hpp"

namespace CMath {

AddTerm::AddTerm(Comparator *cmp)
    : cmp(cmp)
{
    if(cmp == nullptr) {
        this->cmp = Comparator::getDefault();
    }
}

bool AddTerm::add(Number_t a, Number_t b)
{
	a->setValueSigned(a->getValueSigned() + b->getValueSigned());
    b->getParent()->replace(b, nullptr);
	return true;
}

void AddTerm::checkNumber(Multiplication_t m, bool *paired, int *index)
{
	for(size_t i = 0; i < m->getChildCount(); i++) {
		if(!m->childIs(i, Type::NUMBER)) {
			paired[i] = false;
		} else if(*index == -1) {
			paired[i] = true;
			*index = i;
		} else {
			// Just multiply them
			auto a = std::dynamic_pointer_cast<Number>(m->get(*index));
			auto b = std::dynamic_pointer_cast<Number>(m->get(i));
			a->setValue(a->getValueSigned() * b->getValueSigned());
			m->remove(i);
			i--;
		}
	}
}

// Assume only contain one number in multiplication side.
bool AddTerm::add(Multiplication_t a, Object_t b)
{
	if(a->getChildCount() != 2) return 0;
	Number_t num = nullptr;
	for(size_t i = 0; i < a->getChildCount(); i++) {
		if(a->childIs(i, Type::NUMBER)) {
			num = std::dynamic_pointer_cast<Number>(a->get(i));
		} else if(cmp->testUnsigned(a->get(i), b)) {
            return 0;
		}
	}
	if(num == nullptr) return 0;
    num->aborbSignFrom(a);
	num->setValueSigned(num->getValueSigned() + (b->isNegative()  ? -1 : 1));
    a->aborbSignFrom(num);
	if(num->getValue() == 1) {
		a->replace(num, nullptr);
	}

    b->getParent()->replace(b, nullptr);
	if(a->getChildCount() == 1) {
		a->getParent()->replace(a, a->get(0));
	}
	return 1;
}

bool AddTerm::add(Multiplication_t a, Multiplication_t b)
{
	bool apaired[a->getChildCount()];
	bool bpaired[b->getChildCount()];
	int aindex = - 1, bindex = -1;
	checkNumber(a, apaired, &aindex);
	checkNumber(b, bpaired, &bindex);
	for(size_t i = 0; i < a->getChildCount(); i++) {
		if(apaired[i]) continue;
		for(size_t j = 0; j < b->getChildCount(); j++) {
			if(bpaired[j]) continue;
			if(!cmp->testUnsigned(a->get(i), b->get(j))) {
				apaired[i] = true;
				bpaired[j] = true;
				break;
			}
		}
		if(!apaired[i]) {
			return 0;
		}
	}
	for(size_t j = 0; j < b->getChildCount(); j++) {
		if(!bpaired[j]) {
			return 0;
		}
	}
	if(aindex == -1 && bindex == -1) {
		if(a->isNegative() != b->isNegative()) {
            a->getParent()->replace(a, std::make_shared<Number>(0));
		} else {
            a->insert(0, std::make_shared<Number>(2));
		}
        b->getParent()->replace(b, nullptr);
	} else if(aindex == -1 || bindex == -1) {
		if(aindex == -1) {
            a.swap(b);
			aindex = bindex;
		}
		auto num = std::dynamic_pointer_cast<Number>(a->get(aindex));
        num->aborbSignFrom(a);
		num->setValueSigned(num->getValueSigned() + (b->isNegative() ? -1 : 1));
        a->aborbSignFrom(num);
		if(num->getValue() == 1) {
            num->getParent()->replace(num, nullptr);
		}
        b->getParent()->replace(b, nullptr);
	} else {
		auto num1 = std::dynamic_pointer_cast<Number>(a->get(aindex));
		auto num2 = std::dynamic_pointer_cast<Number>(b->get(bindex));
        num1->aborbSignFrom(a);
        num2->aborbSignFrom(b);
		num1->setValueSigned(num1->getValueSigned() + num2->getValueSigned());
		if(num1->getValue() == 0) {
			a->getParent()->replace(a, nullptr);
		} else if(num1->getValue() == 1) {
			a->replace(num1, nullptr);
		}
        a->aborbSignFrom(num1);
		b->getParent()->replace(b, nullptr);
	}
	if(a != nullptr) {
		if(a->getChildCount() == 1) {
            a->getParent()->replace(a, a->get(0));
		}
	}
	return 1;
}

bool AddTerm::add(Object_t a, Object_t b)
{
	if(!a->is(b->getType())) {
        if(a->is(Type::MULTIPLICATION)) {
            return add(std::dynamic_pointer_cast<Multiplication>(a), b);
        } else if(b->is(Type::MULTIPLICATION)) {
            return add(std::dynamic_pointer_cast<Multiplication>(b), a);
        } else {
            return false;
        }
	}

    // a and b has the same type
    switch(a->getType()){
        case Type::NUMBER: return add(std::dynamic_pointer_cast<Number>(a), std::dynamic_pointer_cast<Number>(b));
        case Type::MULTIPLICATION: return add(std::dynamic_pointer_cast<Multiplication>(a), std::dynamic_pointer_cast<Multiplication>(b));
        default: break;
    }
    // Finish if a and b aren't equal
    if(cmp->testUnsigned(a, b)) return false;
    if(a->isNegative() != b->isNegative()) {
        // a and b equal and has different sign, remove both
        a->getParent()->replace(a, std::make_shared<Number>(0));
        b->getParent()->replace(b, nullptr);
        return true;
    }
    // remove b then replace a with 2*a
    b->getParent()->replace(b, nullptr);
    auto result = std::make_shared<Multiplication>();
    a->getParent()->replace(a, result);
    result->add(std::make_shared<Number>(2));
    result->add(a);
    return true;
}

intptr_t AddTerm::onVisit(Addition_t a)
{
    Visitor::onVisit(a);
	for(size_t i = 0; i < a->getChildCount(); i++) {
		for(size_t j = i + 1; j < a->getChildCount(); j++) {
			if(add(a->get(i), a->get(j))) {
				j--;
			}
		}
		// if the result is zero and there is other child remove it
		if(a->childIs(i, Type::NUMBER) && a->getChildCount() > 1) {
			auto num = std::dynamic_pointer_cast<Number>(a->get(i));
			if(num->getValue() == 0) {
				a->remove(i);
				i--;
			}
		}
	}
	// If the result single object replace the addtion with it
	if(a->getChildCount() == 1) {
        a->getParent()->replace(a, a->get(0));
	} else if(a->getChildCount() == 0) {
		a->getParent()->replace(a, std::make_shared<Number>(0));
	}
	return 0;
}

} // namespace CMath


