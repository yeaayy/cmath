
#include <gtest/gtest.h>
#include <cstdarg>

#include "cmath/all"
#include "cmath/parser/expr.hpp"
#include "cmath/parser/bracket.hpp"
#include "cmath/parser/variable.hpp"
#include "cmath/derrivative.hpp"

#include "mock/error_handler.cc"
#include "mock/parser_expr.cc"

using namespace CMath;
using ::Parser::stream;
using ::CMath::Parser::XExpression;
using ::CMath::Parser::XBracket;
using ::CMath::Parser::XVariable;

TEST(derr, parse_odrer_1) {
    stream inp("\\df {@} {@}");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto errHandler = std::make_shared<::Parser::ErrorHandler>();
    auto modExprParser = XExpression::create(nullptr, nullptr, var, nullptr, errHandler);
    auto bracket = XBracket::create(nullptr, modExprParser, errHandler);
    auto parser = XExpression::create(nullptr, nullptr, nullptr, bracket, errHandler);

    handler.EXPECT_NO_ERROR(errHandler);
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::DERRIVATIVE);

    auto derr = std::static_pointer_cast<Derrivative>(result);
    EXPECT_EQ(derr->getOrder(), 1);
    EXPECT_EQ(derr->getA(), a);
    EXPECT_EQ(derr->getB(), b);
}

TEST(derr, parse_odrer_n) {
    stream inp("\\df [9] {@} {@}");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto errHandler = std::make_shared<::Parser::ErrorHandler>();
    auto modExprParser = XExpression::create(nullptr, nullptr, var, nullptr, errHandler);
    auto bracket = XBracket::create(nullptr, modExprParser, errHandler);
    auto parser = XExpression::create(nullptr, nullptr, nullptr, bracket, errHandler);

    handler.EXPECT_NO_ERROR(errHandler);
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::DERRIVATIVE);

    auto derr = std::static_pointer_cast<Derrivative>(result);
    EXPECT_EQ(derr->getOrder(), 9);
    EXPECT_EQ(derr->getA(), a);
    EXPECT_EQ(derr->getB(), b);
}
