#include "cmath/parser/one_expr.hpp"

namespace CMath::Parser {

XOneExpression::XOneExpression(
    PWhitespace_t ws,
    PNumber_t number,
    PVariable_t variable,
    PBracket_t bracket,
    ErrorHandler_t handler)
    : Parser(handler)
    , ws(ws)
    , number(number)
    , variable(variable)
    , bracket(bracket)
{
	if(this->ws == nullptr) {
		this->ws = std::make_shared<XWhitespace>(handler);
	}
	if(this->number == nullptr) {
		this->number = std::make_shared<XNumber>(handler);
	}
	if(this->variable == nullptr) {
		this->variable = std::make_shared<XVariable>(this->ws, handler);
	}
	if(this->bracket == nullptr) {
		this->bracket = std::make_shared<XBracket>();
	}
}
bool XOneExpression::exec(stream &stream, Object_t &result)
{
    bool isNegative = false;
    bool returnValue = false;
    while(stream.peek() == '-') {
        stream.seek();
        isNegative = !isNegative;
        ws->parse(stream);
    }
	if(variable->canParse(stream)) {
		returnValue = variable->beginParse(stream, result);
	} else if(number->canParse(stream)) {
		returnValue = number->beginParse(stream, result);
	} else if(bracket->canParse(stream)) {
		returnValue = bracket->beginParse(stream, result);
	} else {
        // TODO: add error message
        return false;
    }
    result->toggleIsNegative(isNegative);
	return returnValue;
}

bool XOneExpression::canParse(stream &stream)
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

} // namespace CMath::Parser
