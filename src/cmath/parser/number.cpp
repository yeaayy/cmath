#include "cmath/parser/number.hpp"

#include "cmath/number.hpp"

namespace CMath {

namespace Parser {

XNumber::XNumber(ErrorHandler_t handler)
    : Parser(handler)
{
	number = makeTable([](int ch) {
        return ch >= '0' && ch <= '9';
    });
}

XNumber::~XNumber()
{
    deleteTable(number);
}

bool XNumber::exec(stream &stream, Object_t &result)
{
    auto start = stream.tellg();
    while(number[stream.peek()]) {
        stream.seek();
    }
    int length = stream.tellg() - start;
    if(length == 0) {
        return false;
    }
	char tmp[length + 1];
    stream.start(start);
    stream.read(tmp, length);
    tmp[length] = '\0';
    result.reset(new CMath::Number(atoi(tmp)));
    return true;
}

bool XNumber::canParse(stream &stream)
{
	return number[stream.peek()];
}

} // namespace Parser

} // namespace CMath


