#ifndef CMATH_PARSER_NUMBER_HPP
#define CMATH_PARSER_NUMBER_HPP

#include "cmath/object.hpp"
#include "parser/parser.hpp"

namespace CMath::Parser {

using namespace ::Parser;

class XNumber : public Parser<Object_t>
{
protected:
	bool exec(stream &stream, Object_t &result) override;

public:
	XNumber(ErrorHandler_t handler = nullptr);
	~XNumber();
	bool canParse(stream &stream) override;

private:
	CharTable number;
};

typedef ::Parser::Parser<Object_t> PNumber;
typedef std::shared_ptr<PNumber> PNumber_t;

} // namespace CMath::Parser

#endif /* CMATH_PARSER_NUMBER_HPP */
