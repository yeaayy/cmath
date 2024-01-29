#ifndef CMATH_PARSER_VARIABLE_HPP
#define CMATH_PARSER_VARIABLE_HPP

#include "cmath/object.hpp"
#include "cmath/parser/whitespace.hpp"
#include "parser/parser.hpp"

namespace CMath::Parser {

using namespace ::Parser;

class XVariable : public Parser<Object_t>
{
protected:
	bool exec(stream &stream, Object_t &result) override;

public:
    XVariable(std::shared_ptr<PWhitespace> ws = nullptr, ErrorHandler_t handler = nullptr);
    ~XVariable();
	bool canParse(stream &stream) override;

private:
	CharTable begin;
	CharTable middle;
    std::shared_ptr<PWhitespace> ws;
};

typedef ::Parser::Parser<Object_t> PVariable;
typedef std::shared_ptr<PVariable> PVariable_t;

} // namespace CMath::Parser

#endif /* CMATH_PARSER_VARIABLE_HPP */
