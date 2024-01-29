#ifndef CMATH_PARSER_BRACKET_HPP
#define CMATH_PARSER_BRACKET_HPP

#include "cmath/object.hpp"
#include "parser/parser.hpp"

namespace CMath::Parser {

using namespace ::Parser;
typedef ::Parser::Parser<Object_t> PBracket;
typedef std::shared_ptr<PBracket> PBracket_t;

}  // namespace CMath::Parser

#include "cmath/parser/whitespace.hpp"
#include "cmath/parser/expr.hpp"

namespace CMath::Parser {

class XBracket : public PBracket
{
private:
	XBracket(ErrorHandler_t handler);

protected:
	bool exec(stream &stream, Object_t &result) override;

public:
	static std::shared_ptr<XBracket> create(
		PWhitespace_t whitespace = nullptr,
		PNumber_t number = nullptr,
		PVariable_t variable = nullptr,
		PExpression_t expr = nullptr,
		ErrorHandler_t handler = nullptr);
	bool canParse(stream &stream) override;

private:
    std::weak_ptr<PExpression> expr;
	PWhitespace_t whitespace;
};

} // namespace CMath::Parser

#endif /* CMATH_PARSER_BRACKET_HPP */
