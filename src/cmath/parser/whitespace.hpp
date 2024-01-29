#ifndef CMATH_PARSER_WHITESPACE_HPP
#define CMATH_PARSER_WHITESPACE_HPP

#include "parser/parser.hpp"

namespace CMath::Parser {

using namespace ::Parser;

class XWhitespace : public Parser<void*>
{
protected:
	bool exec(stream &stream, void *&result) override;

public:
	XWhitespace(ErrorHandler_t handler = nullptr);
	~XWhitespace();
	bool canParse(stream &stream) override;

private:
	CharTable whitespace;
};

typedef ::Parser::Parser<void*> PWhitespace;
typedef std::shared_ptr<PWhitespace> PWhitespace_t;

} // namespace CMath::Parser

#endif /* CMATH_PARSER_WHITESPACE_HPP */
