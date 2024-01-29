#ifndef CMATH_PARSER_ONE_EXPR_HPP
#define CMATH_PARSER_ONE_EXPR_HPP

#include "cmath/object.hpp"
#include "cmath/parser/number.hpp"
#include "cmath/parser/variable.hpp"
#include "cmath/parser/bracket.hpp"
#include "parser/parser.hpp"

namespace CMath::Parser {

using namespace ::Parser;

class XOneExpression : public Parser<Object_t>
{
protected:
	bool exec(stream &stream, Object_t &result) override;

public:
	XOneExpression(
		PWhitespace_t ws = nullptr,
		PNumber_t number = nullptr,
		PVariable_t variable = nullptr,
		PBracket_t bracket = nullptr,
		ErrorHandler_t handler = nullptr);
	bool canParse(stream &stream) override;

private:
	PWhitespace_t ws;
	PNumber_t number;
	PVariable_t variable;
	PBracket_t bracket;
};

typedef ::Parser::Parser<Object_t> POneExpression;
typedef std::shared_ptr<POneExpression> POneExpression_t;

} // namespace CMath::Parser

#endif /* CMATH_PARSER_ONE_EXPR_HPP */
