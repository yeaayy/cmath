#include "cmath/parser/whitespace.hpp"

namespace CMath::Parser {

XWhitespace::XWhitespace(ErrorHandler_t handler)
	: Parser(handler)
{
	whitespace = makeTable([] (int ch) {
        return ch == ' ' ||
			   ch == '\t' ||
			   ch == '\r' ||
			   ch == '\n';
	});
}

XWhitespace::~XWhitespace()
{
	deleteTable(whitespace);
}

bool XWhitespace::exec(stream &stream, void *&result)
{
	while(true){
		while(whitespace[stream.peek()]) {
			stream.seek();
		}
		if(stream.peek() != '#') {
			break;
		}
		while(stream.peek() != '\n' && !stream.eof()) {
			stream.seek();
		}
	}
	return true;
}

bool XWhitespace::canParse(stream &stream)
{
	int ch = stream.peek();
	return whitespace[ch] || ch == '#';
}

} // namespace CMath::Parser
