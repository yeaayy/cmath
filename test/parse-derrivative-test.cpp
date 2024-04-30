
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

TEST(derr, parse_order_1) {
    stream inp("\\df {@} {@}");
    auto varMock = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto errHandler = std::make_shared<::Parser::ErrorHandler>();
    auto varReal = std::make_shared<XVariable>(nullptr, errHandler);
    auto parser = XExpression::create(nullptr, nullptr, varMock, nullptr, errHandler);

    Object_t df;
    handler.EXPECT_NO_ERROR(errHandler);
    varMock->_canParse()->WillRepeatedly(Invoke([varReal](stream &inp) -> bool {
        if(inp.peek() == '@') {
            return true;
        }
        return varReal->canParse(inp);
    }));
    varMock->willUse(varReal, df);
    auto a = varMock->willParseMock();
    auto b = varMock->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::DERRIVATIVE);

    auto derr = std::static_pointer_cast<Derrivative>(result);
    EXPECT_EQ(derr->getOrder(), 1);
    EXPECT_EQ(derr->getA(), a);
    EXPECT_EQ(derr->getB(), b);
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(a));
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(b));
}

TEST(derr, parse_order_n) {
    stream inp("\\df [9] {@} {@}");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto errHandler = std::make_shared<::Parser::ErrorHandler>();
    auto varReal = std::make_shared<XVariable>(nullptr, errHandler);
    auto parser = XExpression::create(nullptr, nullptr, var, nullptr, errHandler);

    handler.EXPECT_NO_ERROR(errHandler);
    var->_canParse()->WillRepeatedly(Invoke([varReal](stream &inp) -> bool {
        if(inp.peek() == '@') {
            return true;
        }
        return varReal->canParse(inp);
    }));
    Object_t df;
    var->willUse(varReal, df);
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::DERRIVATIVE);

    auto derr = std::static_pointer_cast<Derrivative>(result);
    EXPECT_EQ(derr->getOrder(), 9);
    EXPECT_EQ(derr->getA(), a);
    EXPECT_EQ(derr->getB(), b);
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(a));
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(b));
}

TEST(derr, parse_order_n_condensed) {
    stream inp("\\df[9]@@");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto errHandler = std::make_shared<::Parser::ErrorHandler>();
    auto varReal = std::make_shared<XVariable>(nullptr, errHandler);
    auto parser = XExpression::create(nullptr, nullptr, var, nullptr, errHandler);

    handler.EXPECT_NO_ERROR(errHandler);
    var->_canParse()->WillRepeatedly(Invoke([varReal](stream &inp) -> bool {
        if(inp.peek() == '@') {
            return true;
        }
        return varReal->canParse(inp);
    }));
    Object_t df;
    var->willUse(varReal, df);
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::DERRIVATIVE);

    auto derr = std::static_pointer_cast<Derrivative>(result);
    EXPECT_EQ(derr->getOrder(), 9);
    EXPECT_EQ(derr->getA(), a);
    EXPECT_EQ(derr->getB(), b);
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(a));
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(b));
}
