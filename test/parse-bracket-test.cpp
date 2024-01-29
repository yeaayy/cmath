
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cmath/parser/bracket.hpp"
#include "cmath/parser/expr.hpp"

#include "cmath/number.hpp"
#include "cmath/bracket.hpp"

#include "mock/error_handler.cc"
#include "mock/parser_expr.cc"

using CMath::Parser::XExpression;
using CMath::Parser::XBracket;
using namespace ::testing;

TEST(bracket, can_parse) {
    Parser::stream inp(" ({");

    auto parser = XBracket::create();

    EXPECT_FALSE(parser->canParse(inp));

    inp.seek();
    EXPECT_TRUE(parser->canParse(inp));

    inp.seek();
    EXPECT_TRUE(parser->canParse(inp));
}

TEST(bracket, parse_normal_bracket) {
    Parser::stream inp("(@)");

    auto errorHandler = std::make_shared<Parser::ErrorHandler>();
    auto expr = std::make_shared<ExpressionMock>();
    auto parser = XBracket::create(nullptr, nullptr, nullptr, expr, errorHandler);
    ErrorHandlerMock errHandlerMock;

    errHandlerMock.EXPECT_NO_ERROR(errorHandler);
    auto inner = expr->willParseMock();

    CMath::Object_t result;
    EXPECT_TRUE(parser->beginParse(inp, result));
    ASSERT_NE(result, nullptr) << "result is null";
    ASSERT_TRUE(result->is(CMath::Type::BRACKET));
    ASSERT_EQ(std::static_pointer_cast<CMath::Bracket>(result)->getValue(), inner);
}

TEST(bracket, parse_curly_bracket) {
    Parser::stream inp("{@}");

    auto errorHandler = std::make_shared<Parser::ErrorHandler>();
    auto expr = std::make_shared<ExpressionMock>();
    auto parser = XBracket::create(nullptr, nullptr, nullptr, expr, errorHandler);
    ErrorHandlerMock errHandlerMock;

    errHandlerMock.EXPECT_NO_ERROR(errorHandler);
    auto inner = expr->willParseMock();

    CMath::Object_t result;
    EXPECT_TRUE(parser->beginParse(inp, result));
    ASSERT_NE(result, nullptr) << "result is null";
    ASSERT_EQ(result, inner);
}

TEST(bracket, parse_missing_close_normal_bracket) {
    Parser::stream inp("(@");
    ErrorHandlerMock mockObject;
    auto handler = std::make_shared<Parser::ErrorHandler>();
    auto expr = std::make_shared<ExpressionMock>();
    auto parser = XBracket::create(nullptr, nullptr, nullptr, expr, handler);

    mockObject.EXPECT_ERROR(handler, "Missing ')'");
    auto inner = expr->willParseMock();

    CMath::Object_t result;
    EXPECT_FALSE(parser->beginParse(inp, result));
}

TEST(bracket, parse_missing_close_curly_bracket) {
    Parser::stream inp("{@");
    ErrorHandlerMock mockObject;
    auto handler = std::make_shared<Parser::ErrorHandler>();
    auto expr = std::make_shared<ExpressionMock>();
    auto parser = XBracket::create(nullptr, nullptr, nullptr, expr, handler);

    mockObject.EXPECT_ERROR(handler, "Missing '}'");
    auto inner = expr->willParseMock();

    CMath::Object_t result;
    EXPECT_FALSE(parser->beginParse(inp, result));
}
