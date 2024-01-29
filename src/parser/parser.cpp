#include "parser/parser.hpp"

#include <cstdarg>
#include <vector>

namespace Parser {

BaseParser::BaseParser(ErrorHandler_t errorHandler)
{
    if(!errorHandler) {
        this->errorHandler = std::make_shared<ErrorHandler>();
    } else {
        this->errorHandler = errorHandler;
    }
}

BaseParser::~BaseParser()
{
}

bool BaseParser::error(int start, int end, const char *msgFmt, va_list args)
{
    errorHandler->reportError(start, end, msgFmt, args);
    return false;
}

bool BaseParser::error(int start, int end, const char *msgFmt, ...)
{
    va_list args;
    va_start(args, msgFmt);
    return error(start, end, msgFmt, args);
}

bool BaseParser::error(stream &stream, int start, int end, const char *msgFmt, va_list args)
{
    auto pos = stream.tellg();
    return error(pos + start, pos + end, msgFmt, args);
}

bool BaseParser::error(stream &stream, int start, int end, const char *msgFmt, ...)
{
    va_list args;
    va_start(args, msgFmt);
    return error(start, end, msgFmt, args);
}

ErrorHandler_t &BaseParser::getErrorHandler()
{
    return errorHandler;
}

bool BaseParser::canParse(stream &stream)
{
    return false;
}

CharTable makeTable(bool (*cond)(int))
{
    bool *result = new bool[258];
    result[0] = false;
    for(int i=0; i<256; i++) {
        result[i + 1] = cond(i);
    }
    result[257] = false;
    return result + 1;
}

void deleteTable(CharTable table)
{
    delete[] (table - 1);
}

} // namespace Parser
