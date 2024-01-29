#include "cmath/parser/variable.hpp"

#include "cmath/variable.hpp"

namespace CMath::Parser {

XVariable::XVariable(PWhitespace_t ws, ErrorHandler_t handler)
    : Parser(handler)
    , ws(ws)
{
	if(this->ws == nullptr) {
		this->ws.reset(new XWhitespace(getErrorHandler()));
	}
	begin = makeTable([] (int ch) {
        return (ch >= 'a' && ch <= 'z') ||
               (ch >= 'A' && ch <= 'Z') ||
               ch == '\\';
    });
	middle = makeTable([] (int ch) {
        return (ch >= 'a' && ch <= 'z') ||
               (ch >= 'A' && ch <= 'Z') ||
               (ch >= '0' && ch <= '9') ||
               ch == '_';
    });
}

XVariable::~XVariable()
{
    deleteTable(begin);
    deleteTable(middle);
}

bool XVariable::canParse(stream &stream)
{
	return begin[stream.peek()];
}

bool XVariable::exec(stream &stream, Object_t &result)
{
    auto start = stream.tellg();
    if(begin[stream.peek()]) {
        stream.seek();
        while(middle[stream.peek()]) {
            stream.seek();
        }
    }
    int len = stream.tellg() - start;
	if(len == 0) {
		return false;
	}
	char name[len + 1];
    stream.start(start);
    stream.read(name, len);
	name[len] = '\0';
	result.reset(new CMath::Variable(name));
	return true;
}

} // namespace CMath::Parser
