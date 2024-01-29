#ifndef CMATH_PARSER_EXPR_HPP
#define CMATH_PARSER_EXPR_HPP

#include "cmath/object.hpp"
#include "parser/parser.hpp"

namespace CMath::Parser {

using namespace ::Parser;
typedef ::Parser::Parser<Object_t> PExpression;
typedef std::shared_ptr<PExpression> PExpression_t;

} // namespace CMath::Parser

#include "cmath/parser/number.hpp"
#include "cmath/parser/variable.hpp"
#include "cmath/parser/whitespace.hpp"
#include "cmath/parser/bracket.hpp"

namespace CMath::Parser {

enum class Precedence {
	POWER,
	FRACTION,
	MULTIPLY,
	ADD,
	SUBRACT = ADD,
	HIGHEST
};

class XExpression : public PExpression
{
private:
	XExpression(ErrorHandler_t handler);

protected:
	bool exec(stream &stream, Object_t &result) override;

	Precedence getPrecedence(char v);

	bool parseOne(stream &stream, Object_t &result);
	bool beginParse(Precedence precedence, stream &stream, Object_t &result);

public:
	static std::shared_ptr<XExpression> create(
		PWhitespace_t whitespace = nullptr,
		PNumber_t number = nullptr,
		PVariable_t variable = nullptr,
		PBracket_t bracket = nullptr,
		ErrorHandler_t handler = nullptr);
	~XExpression();
	bool parse(stream &stream, Object_t &);
	bool canParseOne(stream &stream);

private:
	PWhitespace_t whitespace;
	PNumber_t number;
	PVariable_t variable;
	PBracket_t bracket;
	Precedence lastPrecedence;
	CharTable op;
	CharTable relation;
	int _openBracket;
};

std::ostream &operator<<(std::ostream &os, Precedence precedence);

} // namespace CMath::Parser

#endif /* CMATH_PARSER_EXPR_HPP */
