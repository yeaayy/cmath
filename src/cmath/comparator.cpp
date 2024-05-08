#include "cmath/comparator.hpp"

#include <cstring>
#include <cmath/all>

namespace CMath {

Comparator *Comparator::instance = new Comparator();

Comparator::Comparator()
	: BinaryEvaluator(true, 1)
{}

intptr_t Comparator::test(Object_t a, Object_t b)
{
	intptr_t result = eval(a, b);
	if(!result) return a->isNegative() - b->isNegative();
	return result;
}

intptr_t Comparator::testUnsigned(Object_t a, Object_t b)
{
	return eval(a, b);
}

Comparator *Comparator::getDefault()
{
    return instance;
}

intptr_t Comparator::eval1(Number_t a, Number_t b)
{
	return a->getValue() - b->getValue();
}

intptr_t Comparator::eval1(Variable_t a, Variable_t b)
{
	return a->getName().compare(b->getName());
}

intptr_t Comparator::eval1(Addition_t a, Addition_t b)
{
	if(a->getChildCount() != b->getChildCount()) {
		return a->getChildCount() - b->getChildCount();
	}
	for(std::size_t i=0; i<a->getChildCount(); i++) {
		auto r = test(a->get(i), b->get(i));
		if(r !=0) {
			return r;
		}
	}
	return 0;
}

intptr_t Comparator::eval1(Multiplication_t a, Multiplication_t b)
{
	if(a->getChildCount() != b->getChildCount()) {
		return a->getChildCount() - b->getChildCount();
	}
	for(std::size_t i=0; i<a->getChildCount(); i++) {
		auto r = operator() (a->get(i), b->get(i));
		if(r != 0) {
			return r;
		}
	}
	return 0;
}

intptr_t Comparator::eval1(Fraction_t a, Fraction_t b)
{
	intptr_t result = test(a->getA(), b->getA());
	if(result) return result;
	return test(a->getB(), b->getB());
}

intptr_t Comparator::eval1(Power_t a, Power_t b)
{
	intptr_t result = test(a->getBase(), b->getBase());
	if(result != 0) return result;
	return test(a->getExponent(), b->getExponent());
}

intptr_t Comparator::eval1(Bracket_t a, Bracket_t b)
{
	return test(a->getValue(), b->getValue());
}

intptr_t Comparator::eval1(Function_t a, Function_t b)
{
	int dist = a->getName().compare(b->getName());
	if(dist != 0) {
		return dist;
	}
	if(a->getArgumentCount() != b->getArgumentCount()) {
		return a->getArgumentCount() - b->getArgumentCount();
	}
	for(std::size_t i=0; i<a->getArgumentCount(); i++) {
		auto r = test (a->getArgument(i), b->getArgument(i));
		if(r !=0) {
			return r;
		}
	}
	return 0;
}

intptr_t Comparator::eval1(Relation_t a, Relation_t b)
{
	// loge("TODO: Implement Comparator::eval1(Relation_t a, Relation_t b)");
	return 0;
}

intptr_t Comparator::eval1(Derrivative_t a, Derrivative_t b)
{
	intptr_t result = test(a->getA(), b->getA());
	if(result) return result;
	result = test(a->getB(), b->getB());
	if(result) return result;
	return a->getOrder() - b->getOrder();
}

} // namespace C
