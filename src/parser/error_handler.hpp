#ifndef PARSER_ERROR_HANDLER_HPP
#define PARSER_ERROR_HANDLER_HPP

#include <functional>
#include <list>
#include <memory>
#include <sstream>
#include <string>

namespace Parser {

class ErrorHandler;

typedef std::function<void(ErrorHandler*)> OnError;

class ErrorHandler
{
public:
    ErrorHandler();
    ~ErrorHandler();
    void clearOnError();
    void addOnError(OnError onError);
    int getMessageId();
    const char *getMessage();
    std::streampos getErrorStart();
    std::streampos getErrorEnd();
    std::string format(std::stringstream &stream, bool color = false);

    void reportError(std::streampos start, std::streampos end, const char *msgFmt, va_list messageData);

private:
    std::streampos start;
    std::streampos end;
    char *message;
    std::list<OnError> onErrors;
};

typedef std::shared_ptr<ErrorHandler> ErrorHandler_t;

} // namespace Parser

#endif /* PARSER_ERROR_HANDLER_HPP */
