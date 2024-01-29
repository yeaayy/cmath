#include "parser/error_handler.hpp"

namespace Parser {

ErrorHandler::ErrorHandler()
{
    this->message = nullptr;
}

ErrorHandler::~ErrorHandler()
{
    if(message != nullptr) {
        free(message);
    }
}

void ErrorHandler::reportError(std::streampos start, std::streampos end, const char *msgFmt, va_list messageData)
{
    this->start = start;
    this->end = end;
    if(message != nullptr) {
        free(message);
    }
    vasprintf(&message, msgFmt, messageData);
    for(auto handler : onErrors) {
        handler(this);
    }
}

void ErrorHandler::clearOnError()
{
    onErrors.clear();
}

void ErrorHandler::addOnError(OnError handler)
{
    onErrors.push_back(handler);
}

std::streampos ErrorHandler::getErrorStart()
{
    return start;
}

std::streampos ErrorHandler::getErrorEnd()
{
    return end;
}

const char *ErrorHandler::getMessage()
{
    return message;
}


std::string ErrorHandler::format(std::stringstream &stream, bool color)
{
    std::stringstream result;
    
    stream.seekg(0, std::ios::end);
    std::streampos length = stream.tellg();

    std::streampos start = this->start, end = this->end;
    std::streampos left = start, right = end;
    stream.seekg(left, std::ios::beg);
    while(left > 0 && stream.peek() != '\n') {
        left -= 1;
        stream.seekg(left, std::ios::beg);
    }

    stream.seekg(right, std::ios::beg);
    while(right < length && stream.good() && stream.peek() != '\n') {
        right += 1;
        stream.seekg(right, std::ios::beg);
    }
    
    {
        stream.seekg(left, std::ios::beg);
        int size = right - left;
        char tmp[size];
        stream.read(tmp, size);
        result << tmp;
    }

    int space = start - left;
    int marker = end -  start;
    while(space--) result << ' ';
    while(marker--) result << '^';
    result << '\n';
    return result.str();
}

} // namespace Parser
