#include "cmath/parser/expr.hpp"

#include <iostream>

#include "config.hpp"
#include "cmath/addition.hpp"
#include "cmath/bracket.hpp"
#include "cmath/derrivative.hpp"
#include "cmath/multiplication.hpp"
#include "cmath/number.hpp"
#include "cmath/fraction.hpp"
#include "cmath/power.hpp"
#include "cmath/relation.hpp"
#include "cmath/variable.hpp"

namespace CMath::Parser {

XExpression::XExpression(ErrorHandler_t handler)
	: Parser(handler)
{
    op = makeTable([] (int ch) {
        return ch == '+' ||
               ch == '-' ||
               ch == '*' ||
               ch == '/' ||
               ch == '^';
    });
    relation = makeTable([] (int ch) {
        return ch == '=' ||
               ch == '<' ||
               ch == '>';
    });
}

std::shared_ptr<XExpression> XExpression::create(
	PWhitespace_t whitespace,
	PNumber_t number,
	PVariable_t variable,
	PBracket_t bracket,
	ErrorHandler_t handler
) {
	std::shared_ptr<XExpression> result;
	result.reset(new XExpression(handler));
	result->whitespace = whitespace ? whitespace : std::make_shared<XWhitespace>(result->getErrorHandler());
	result->number = number ? number : std::make_shared<XNumber>(result->getErrorHandler());
	result->variable = variable ? variable : std::make_shared<XVariable>(result->whitespace, result->getErrorHandler());
	result->bracket = bracket ? bracket : XBracket::create(result->whitespace, result, result->getErrorHandler());
	return result;
}

XExpression::~XExpression()
{
    deleteTable(op);
    deleteTable(relation);
}

bool XExpression::parse(stream &stream, Object_t &result)
{
	_openBracket = 0;
    if(!beginParse(Precedence::HIGHEST, stream, result)) {
		return false;
	}
	return true;
}

Precedence XExpression::getPrecedence(char v)
{
	switch(v) {
		case '^': return Precedence::POWER;
		case '/': return Precedence::FRACTION;
		case '*': return Precedence::MULTIPLY;
		case '+': return Precedence::ADD;
		case '-': return Precedence::SUBRACT;
		default:  return Precedence::HIGHEST;
	}
}

bool XExpression::parseOne(stream &stream, Object_t &result)
{
	if(variable->canParse(stream)) {
		auto rtn = variable->beginParse(stream, result);
		if(auto var = std::dynamic_pointer_cast<Variable>(result)) {
			auto name = var->getName();
			if(name == "\\df") return parseDerrivative(stream, result);
		}
		return rtn;
	} else if(number->canParse(stream)) {
		return number->beginParse(stream, result);
	} else if(bracket->canParse(stream)) {
		lastPrecedence = Precedence::HIGHEST; // Bracket parser will using this object, set precedence to highest
		return bracket->beginParse(stream, result);
	}
	return false;
}

bool XExpression::canParseOne(stream &stream)
{
	if(stream.peek() == '-') {
		return true;
	}else if(variable->canParse(stream)) {
		return true;
	} else if(number->canParse(stream)) {
		return true;
	} else if(bracket->canParse(stream)) {
		return true;
	}
	return false;
}

bool XExpression::beginParse(Precedence precedence, stream &stream, Object_t &result)
{
	lastPrecedence = precedence;
	return Parser::beginParse(stream, result);
}

bool XExpression::exec(stream &stream, Object_t &result)
{
	Precedence lastPrecedence = this->lastPrecedence;
	Precedence precedence;
	bool returnResult = true;
	bool isNegative = false;
	int op = 0;
	// Mark begining of operator
	std::streampos marker;
	Object_t first = nullptr;
	Object_t second = nullptr;

sign:
	whitespace->parse(stream);
	if(stream.peek() == '-') {
		stream.seek();
		isNegative = !isNegative;
		goto sign;
	} else if(!parseOne(stream, first)) {
		if(stream.eof()) {
			return error(stream, 0, 1, _("Unexpected EOF"));
		} else if(stream.peek() == ')' || stream.peek() == '}') {
			returnResult = true;
			goto cancel;
		} else {
			return error(stream, 0, 1, _("Unexpected character '%c'"), stream.peek());
		}
	}

loop:
	whitespace->parse(stream);
	if(stream.eof()) {
		returnResult = true;
		goto cancel;
	}
	marker = stream.tellg();
	op = stream.get();
	if(op == '!') {
		// Must be '!=' or error
		int x = stream.get();
		if(x != '=') {
			return error(stream, -1, 0, _("Expecting '=' after '!'"));
		}
		op = 256 * op + x;
	} else if(this->relation[op]) {
		int x = stream.peek();
		// Match for <=, >=, <>, and ><. If not it mean either =, <, or >
		if(op != '=' && this->relation[x] && x != op) {
			stream.seek();
			op = 256 * op + x;
		}
	} else if(!this->op[op]) {
		// Implicit multiplication
        stream.seek(-1);
		op = '*';
	}

	precedence = getPrecedence(op);
	if(lastPrecedence < precedence) {
		// Higher order operator, stop parse
		goto cancelAndSeek;
	}
	whitespace->parse(stream);
	if(stream.eof()) {
		return error(stream, -1, 0, _("Expecting expression after '%c' operator"), op);
	}
	// For lower or equal order operator, do recursive
	if(!beginParse(precedence, stream, second)) {
		return false;
	}
	// When result is null (which only happen when trying to read close bracket) return first as result
	if(second == nullptr) {
		returnResult = true;
		goto cancel;
	}

	if(op != '^' && op != '/') {
		first->toggleIsNegative(isNegative);
		isNegative = false;
	}
	switch(op) {
	case '^': 
		first.reset(new Power(first, second));
		break;
	case '/': 
		first.reset(new Fraction(first, second));
		break;
	case '-':
		if(second->is(Type::ADDITION)) {
			std::static_pointer_cast<Addition>(second)->get(0)->toggleIsNegative(true);
		} else {
			second->toggleIsNegative(true);
		}
		// no break
	case '+':
	{
		std::shared_ptr<Addition> tmp;
		if(second->is(Type::ADDITION)) {
			tmp = std::static_pointer_cast<Addition>(second);
			tmp->insert(0, first);
		} else {
			tmp.reset(new Addition());
			tmp->add(first);
			tmp->add(second);
		}
		first = tmp;
		break;}
	case '*':
	{
		Multiplication_t tmp;
		if(second->is(Type::MULTIPLICATION)) {
			tmp = std::static_pointer_cast<Multiplication>(second);
			tmp->insert(0, first);
		} else {
			tmp = std::make_shared<Multiplication>();
			tmp->add(first);
			tmp->add(second);
			tmp->toggleIsNegative(second->isNegative());
			second->setIsNegative(false);
		}
		tmp->toggleIsNegative(first->isNegative());
		first->setIsNegative(false);
		first = tmp;
		break;}
	case '>':
		first = std::make_shared<Relation>(first, second, Relation::Type::GREATER_THAN);
		break;
	case '<':
		first = std::make_shared<Relation>(first, second, Relation::Type::LESS_THAN);
		break;
	case '=':
		first = std::make_shared<Relation>(first, second, Relation::Type::EQUAL);
		break;
	case '>' * 256 + '=':
		first = std::make_shared<Relation>(first, second, Relation::Type::GREATER_THAN_OR_EQUAL);
		break;
	case '<' * 256 + '=':
		first = std::make_shared<Relation>(first, second, Relation::Type::LESS_THAN_OR_EQUAL);
		break;
	case '!' * 256 + '=':
	case '>' * 256 + '<':
	case '<' * 256 + '>':
		first = std::make_shared<Relation>(first, second, Relation::Type::NOT_EQUAL);
		break;
	}
	second = nullptr;
	goto loop;

cancelAndSeek:
	stream.start(marker);

cancel:

	if(returnResult) {
		first->toggleIsNegative(isNegative);
		result = first;
	}
	return returnResult;
}

bool XExpression::parseDerrivative(stream &stream, Object_t &result)
{
	int start = stream.tellg();
	int order = 1;
	whitespace->parse(stream);
	if(stream.peek() == '[') {
		stream.seek();
		whitespace->parse(stream);
		int orderOffsetStart = stream.tellg();
		Object_t orderObj;
		if(!number->beginParse(stream, orderObj)) {
			return error(orderOffsetStart, orderOffsetStart + 1, _("Derrivative order must be a number"));
		}
		order = std::static_pointer_cast<Number>(orderObj)->getValueSigned();
		whitespace->parse(stream);
		if(stream.get() != ']') {
			return error(stream.tellg(), stream.tellg() + 1, _("Missing ']' after derrivative order"));
		}
		stream.seek();
		whitespace->parse(stream);
	}
	Object_t a, b;
	if(stream.peek() == '-') {
		return error(stream.tellg(), stream.tellg() + 1, _("Unexpected negative sign, expecting single positive expression here. Wrap the expression with bracket if you still want negative expression."));
	}
	if(canParseOne(stream)) {
		if(!parseOne(stream, a)) {
			return false;
		}
	} else {
		return error(start, stream.tellg(), _("Expecting expression after derrivative operator"));
	}
	whitespace->parse(stream);
	if(stream.peek() == '-') {
		return error(stream.tellg(), stream.tellg() + 1, _("Unexpected negative sign, expecting single positive expression here. Wrap the expression with bracket if you still want negative expression."));
	}
	if(canParseOne(stream)) {
		if(!parseOne(stream, b)) {
			return false;
		}
	} else {
		return error(start, stream.tellg(), _("Expecting other expression after \\df"));
	}
	if(b->is(Type::BRACKET)) {
		Object_t bracket = b;
		b = std::static_pointer_cast<Bracket>(b)->getValue();
	}
	result = std::make_shared<Derrivative>(a, b, order);
	return true;
}

std::ostream &operator<<(std::ostream &os, Precedence precedence)
{
	switch(precedence) {
		case Precedence::POWER: return os << "CMath::Parser::Precedence::POWER";
		case Precedence::FRACTION: return os << "CMath::Parser::Precedence::FRACTION";
		case Precedence::MULTIPLY: return os << "CMath::Parser::Precedence::MULTIPLY";
		case Precedence::ADD: return os << "CMath::Parser::Precedence::ADD_OR_SUBSTRACT";
		case Precedence::HIGHEST: return os << "CMath::Parser::Precedence::HIGHEST";
		default: return os << "CMath::Parser::Precedence::UNKNOWN("<<((int)precedence)<<")";
	}
}

} // namespace CMath::Parser
