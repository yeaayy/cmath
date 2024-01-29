#include "cmath/binary_evaluator.hpp"

#include <cmath/all>

namespace CMath {

BinaryEvaluator::BinaryEvaluator(bool reverseSign, intptr_t defaultReturn)
    : reverseSign(reverseSign)
    , defaultReturn(defaultReturn)
{
}

intptr_t BinaryEvaluator::eval1(Number_t a, Number_t b)
{
    return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Variable_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Variable_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Addition_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Addition_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Addition_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Multiplication_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Multiplication_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Multiplication_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Multiplication_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Fraction_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Fraction_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Fraction_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Fraction_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Fraction_t a, Fraction_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Power_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Power_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Power_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Power_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Power_t a, Fraction_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Power_t a, Power_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Bracket_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Bracket_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Bracket_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Bracket_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Bracket_t a, Fraction_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Bracket_t a, Power_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Bracket_t a, Bracket_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Fraction_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Power_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Function_t a, Bracket_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Function_t a, Function_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Fraction_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Power_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Bracket_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Relation_t a, Function_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Relation_t a, Relation_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Number_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Variable_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Addition_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Multiplication_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Fraction_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Power_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Bracket_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Function_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval0(Derrivative_t a, Relation_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval1(Derrivative_t a, Derrivative_t b)
{
	return defaultReturn;
}

intptr_t BinaryEvaluator::eval(Object_t a, Object_t b)
{
    intptr_t sign = reverseSign ? -1 : 1;
	switch(a->getType()) {
		case Type::NUMBER:
		switch(b->getType()) {
			case Type::NUMBER: return eval1(std::static_pointer_cast<Number>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return sign *  eval0(std::static_pointer_cast<Variable>(b), std::static_pointer_cast<Number>(a));
			case Type::ADDITION: return sign *  eval0(std::static_pointer_cast<Addition>(b), std::static_pointer_cast<Number>(a));
			case Type::MULTIPLICATION: return sign *  eval0(std::static_pointer_cast<Multiplication>(b), std::static_pointer_cast<Number>(a));
			case Type::FRACTION: return sign *  eval0(std::static_pointer_cast<Fraction>(b), std::static_pointer_cast<Number>(a));
			case Type::POWER: return sign *  eval0(std::static_pointer_cast<Power>(b), std::static_pointer_cast<Number>(a));
			case Type::BRACKET: return sign *  eval0(std::static_pointer_cast<Bracket>(b), std::static_pointer_cast<Number>(a));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Number>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Number>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Number>(a));
            default: break;
		}
		break;
		case Type::VARIABLE:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Variable>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval1(std::static_pointer_cast<Variable>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return sign *  eval0(std::static_pointer_cast<Addition>(b), std::static_pointer_cast<Variable>(a));
			case Type::MULTIPLICATION: return sign *  eval0(std::static_pointer_cast<Multiplication>(b), std::static_pointer_cast<Variable>(a));
			case Type::FRACTION: return sign *  eval0(std::static_pointer_cast<Fraction>(b), std::static_pointer_cast<Variable>(a));
			case Type::POWER: return sign *  eval0(std::static_pointer_cast<Power>(b), std::static_pointer_cast<Variable>(a));
			case Type::BRACKET: return sign *  eval0(std::static_pointer_cast<Bracket>(b), std::static_pointer_cast<Variable>(a));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Variable>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Variable>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Variable>(a));
            default: break;
		}
		break;
		case Type::ADDITION:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Addition>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Addition>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval1(std::static_pointer_cast<Addition>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return sign *  eval0(std::static_pointer_cast<Multiplication>(b), std::static_pointer_cast<Addition>(a));
			case Type::FRACTION: return sign *  eval0(std::static_pointer_cast<Fraction>(b), std::static_pointer_cast<Addition>(a));
			case Type::POWER: return sign *  eval0(std::static_pointer_cast<Power>(b), std::static_pointer_cast<Addition>(a));
			case Type::BRACKET: return sign *  eval0(std::static_pointer_cast<Bracket>(b), std::static_pointer_cast<Addition>(a));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Addition>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Addition>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Addition>(a));
            default: break;
		}
		break;
		case Type::MULTIPLICATION:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Multiplication>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Multiplication>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Multiplication>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval1(std::static_pointer_cast<Multiplication>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return sign *  eval0(std::static_pointer_cast<Fraction>(b), std::static_pointer_cast<Multiplication>(a));
			case Type::POWER: return sign *  eval0(std::static_pointer_cast<Power>(b), std::static_pointer_cast<Multiplication>(a));
			case Type::BRACKET: return sign *  eval0(std::static_pointer_cast<Bracket>(b), std::static_pointer_cast<Multiplication>(a));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Multiplication>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Multiplication>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Multiplication>(a));
            default: break;
		}
		break;
		case Type::FRACTION:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Fraction>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Fraction>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Fraction>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval0(std::static_pointer_cast<Fraction>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return eval1(std::static_pointer_cast<Fraction>(a), std::static_pointer_cast<Fraction>(b));
			case Type::POWER: return sign *  eval0(std::static_pointer_cast<Power>(b), std::static_pointer_cast<Fraction>(a));
			case Type::BRACKET: return sign *  eval0(std::static_pointer_cast<Bracket>(b), std::static_pointer_cast<Fraction>(a));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Fraction>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Fraction>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Fraction>(a));
            default: break;
		}
		break;
		case Type::POWER:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Power>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Power>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Power>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval0(std::static_pointer_cast<Power>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return eval0(std::static_pointer_cast<Power>(a), std::static_pointer_cast<Fraction>(b));
			case Type::POWER: return eval1(std::static_pointer_cast<Power>(a), std::static_pointer_cast<Power>(b));
			case Type::BRACKET: return sign *  eval0(std::static_pointer_cast<Bracket>(b), std::static_pointer_cast<Power>(a));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Power>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Power>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Power>(a));
            default: break;
		}
		break;
		case Type::BRACKET:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval0(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return eval0(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Fraction>(b));
			case Type::POWER: return eval0(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Power>(b));
			case Type::BRACKET: return eval1(std::static_pointer_cast<Bracket>(a), std::static_pointer_cast<Bracket>(b));
			case Type::FUNCTION: return sign *  eval0(std::static_pointer_cast<Function>(b), std::static_pointer_cast<Bracket>(a));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Bracket>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Bracket>(a));
            default: break;
		}
		break;
		case Type::FUNCTION:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Fraction>(b));
			case Type::POWER: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Power>(b));
			case Type::BRACKET: return eval0(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Bracket>(b));
			case Type::FUNCTION: return eval1(std::static_pointer_cast<Function>(a), std::static_pointer_cast<Function>(b));
			case Type::RELATION: return sign *  eval0(std::static_pointer_cast<Relation>(b), std::static_pointer_cast<Function>(a));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Function>(a));
            default: break;
		}
		break;
		case Type::RELATION:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Fraction>(b));
			case Type::POWER: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Power>(b));
			case Type::BRACKET: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Bracket>(b));
			case Type::FUNCTION: return eval0(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Function>(b));
			case Type::RELATION: return eval1(std::static_pointer_cast<Relation>(a), std::static_pointer_cast<Relation>(b));
			case Type::DERRIVATIVE: return sign *  eval0(std::static_pointer_cast<Derrivative>(b), std::static_pointer_cast<Relation>(b));
            default: break;
		}
		break;
		case Type::DERRIVATIVE:
		switch(b->getType()) {
			case Type::NUMBER: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Number>(b));
			case Type::VARIABLE: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Variable>(b));
			case Type::ADDITION: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Addition>(b));
			case Type::MULTIPLICATION: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Multiplication>(b));
			case Type::FRACTION: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Fraction>(b));
			case Type::POWER: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Power>(b));
			case Type::BRACKET: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Bracket>(b));
			case Type::FUNCTION: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Function>(b));
			case Type::RELATION: return eval0(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Relation>(b));
			case Type::DERRIVATIVE: return eval1(std::static_pointer_cast<Derrivative>(a), std::static_pointer_cast<Derrivative>(b));
            default: break;
		}
		break;
	}
	return defaultReturn;
}

intptr_t BinaryEvaluator::operator() (Object_t a, Object_t b)
{
	return eval(a, b);
}

} // namespace C
