
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "parser/error_handler.hpp"
#include "parser/parser.hpp"

using namespace testing;

class ErrorHandlerMock
{
public:
    MOCK_METHOD(void, call, (::Parser::ErrorHandler*), (const));
    void EXPECT_NO_ERROR(::Parser::ErrorHandler_t errHandler) {
        EXPECT_CALL(*this, call).Times(0);
        errHandler->addOnError([this](::Parser::ErrorHandler *e) {
            GTEST_NONFATAL_FAILURE_("Unexpected error from handler") << e->getMessage();
            this->call(e);
        });
    }
    void EXPECT_ERROR(::Parser::ErrorHandler_t errHandler, const char *msg) {
        EXPECT_CALL(*this, call);
            errHandler->addOnError([this, msg](::Parser::ErrorHandler *e) {
                this->call(e);
                EXPECT_STREQ(e->getMessage(), msg);
            });
    }
};
