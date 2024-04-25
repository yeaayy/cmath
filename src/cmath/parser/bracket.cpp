#include "cmath/parser/bracket.hpp"

#include <iostream>

#include "cmath/bracket.hpp"
#include "cmath/parser/expr.hpp"
#include "cmath/parser/whitespace.hpp"
#include "parser/parser.hpp"

namespace CMath::Parser {

XBracket::XBracket(ErrorHandler_t handler)
    : Parser(handler)
{}

std::shared_ptr<XBracket> XBracket::create(
	PWhitespace_t whitespace,
	PExpression_t expr,
	ErrorHandler_t handler
) {
	std::shared_ptr<XBracket> result;
	result.reset(new XBracket(handler));
	result->whitespace = whitespace ? whitespace : std::make_shared<XWhitespace>(result->getErrorHandler());
	if(expr) {
		result->expr = expr;
	}
	return result;
}

bool XBracket::exec(stream &stream, Object_t &result)
{
	auto start = stream.tellg();
	char pair = stream.get();
	if(pair == '(') {
		pair = ')';
	} else if(pair == '{') {
		pair = '}';
	} else {
		// loge("Error: This code should be unreachable");
		return false;
	}
	whitespace->parse(stream);
    Object_t value;
	auto expr = this->expr.lock();
	if(expr == nullptr) {
		std::cerr << "Internal Error: expr parser is null inside bracket parser.\n";
		return false;
	}
	expr->beginParse(stream, value);
	if(stream.peek() != pair) {
		// if(stream.get(-1) == '\n') stream.seek(-1);
		return error(stream, 0, 1, "Missing '%c'", pair);
	}
	if(value == nullptr) {
		return error(start, stream.tellg() + 1, "Expecting expression inside %s bracket", (pair == ')' ? "round" : "curly"));
	}
	stream.seek();
	if(pair == ')') {
		result.reset(new CMath::Bracket(value));
	} else {
		result = value;
	}
    return true;
}

bool XBracket::canParse(stream &stream)
{
	int ch = stream.peek();
	return ch == '(' || ch == '{';
}

void XBracket::setExpressionParser(PExpression_t expr)
{
	this->expr = expr;
}

} // namespace CMath::Parser
