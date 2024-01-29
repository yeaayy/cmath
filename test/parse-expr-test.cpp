
#include <gtest/gtest.h>
#include <cstdarg>

#include "cmath/all"
#include "cmath/parser/expr.hpp"
#include "cmath/parser/bracket.hpp"
#include "cmath/multiplication.hpp"

#include "mock/error_handler.cc"
#include "mock/parser_expr.cc"

using namespace CMath;
using ::Parser::stream;
using ::CMath::Parser::XExpression;

TEST(expr, parse_negative) {
    stream inp("-@");

    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    auto a = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));

    ASSERT_EQ(result, a);
    EXPECT_TRUE(result->isNegative());
}

TEST(expr, parse_double_negative) {
    stream inp("--@");

    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    auto a = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));

    ASSERT_EQ(result, a);
    EXPECT_FALSE(result->isNegative());
}

TEST(expr, parse_implicit_multiplication) {
    stream inp("@ @");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::MULTIPLICATION);

    auto mult = std::static_pointer_cast<Multiplication>(result);
    EXPECT_EQ(mult->getChildCount(), 2);
    EXPECT_EQ(mult->get(0), a);
    EXPECT_EQ(mult->get(1), b);
}

TEST(expr, parse_multiplication) {
    stream inp("@*@");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::MULTIPLICATION);

    auto mult = std::static_pointer_cast<Multiplication>(result);
    EXPECT_EQ(mult->getChildCount(), 2);
    EXPECT_EQ(mult->get(0), a);
    EXPECT_EQ(mult->get(1), b);
}

TEST(expr, parse_a_plus_b) {
    stream inp("@+@");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::ADDITION);

    auto add = std::static_pointer_cast<Addition>(result);
    EXPECT_EQ(add->getChildCount(), 2);
    EXPECT_EQ(add->get(0), a);
    EXPECT_EQ(add->get(1), b);
}

TEST(expr, parse_a_sub_b) {
    stream inp("@-@");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::ADDITION);

    auto add = std::static_pointer_cast<Addition>(result);
    EXPECT_EQ(add->getChildCount(), 2);
    EXPECT_EQ(add->get(0), a);
    EXPECT_EQ(add->get(1), b);
    EXPECT_FALSE(add->isNegative());
    EXPECT_FALSE(a->isNegative());
    EXPECT_TRUE(b->isNegative());
}

TEST(expr, parse_a_mul_neg_b) {
    stream inp("@*-@");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    EXPECT_TRUE(result->isNegative());
    ASSERT_EQ(result->getType(), Type::MULTIPLICATION);

    auto mult = std::static_pointer_cast<Multiplication>(result);
    EXPECT_EQ(mult->getChildCount(), 2);
    EXPECT_EQ(mult->get(0), a);
    EXPECT_EQ(mult->get(1), b);
    EXPECT_FALSE(a->isNegative());
    EXPECT_FALSE(b->isNegative());
}

TEST(expr, parse_neg_a_mul_b) {
    stream inp("-@*@");
    auto var = std::make_shared<ExpressionMock>();
    ErrorHandlerMock handler;
    auto parser = XExpression::create(nullptr, nullptr, var);

    handler.EXPECT_NO_ERROR(parser->getErrorHandler());
    var->canParseTrue();
    var->canParseTrue();
    auto a = var->willParseMock();
    auto b = var->willParseMock();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    EXPECT_TRUE(result->isNegative());
    ASSERT_EQ(result->getType(), Type::MULTIPLICATION);

    auto mult = std::static_pointer_cast<Multiplication>(result);
    EXPECT_EQ(mult->getChildCount(), 2);
    EXPECT_EQ(mult->get(0), a);
    EXPECT_EQ(mult->get(1), b);
    EXPECT_FALSE(a->isNegative());
    EXPECT_FALSE(b->isNegative());
}

TEST(expr, parse_bracket) {
    stream inp("(@)");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto var = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, nullptr, var, nullptr, errorHandler);

    mockHandler.EXPECT_NO_ERROR(errorHandler);
    var->canParseFalse();
    var->canParseTrue();
    auto a = var->willParseMock();
    var->canParseFalse();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::BRACKET);

    EXPECT_EQ(std::static_pointer_cast<Bracket>(result)->getValue(), a);
}

TEST(expr, parse_double_bracket) {
    stream inp("((@))");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto var = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, nullptr, var, nullptr, errorHandler);

    mockHandler.EXPECT_NO_ERROR(errorHandler);
    var->canParseFalse();
    var->canParseFalse();
    var->canParseTrue();
    auto a = var->willParseMock();
    var->canParseFalse();
    var->canParseFalse();

    Object_t result;
    ASSERT_TRUE(parser->parse(inp, result));
    ASSERT_EQ(result->getType(), Type::BRACKET);

    Object_t value = std::static_pointer_cast<Bracket>(result)->getValue();
    ASSERT_EQ(value->getType(), Type::BRACKET);

    EXPECT_EQ(std::static_pointer_cast<Bracket>(value)->getValue(), a);
}

TEST(expr, parse_unknown) {
    stream inp("|");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto number = std::make_shared<ExpressionMock>();
    auto var = std::make_shared<ExpressionMock>();
    auto bracket = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, number, var, bracket, errorHandler);

    mockHandler.EXPECT_ERROR(errorHandler, "Unexpected character '|'");
    number->neverParse();
    var->neverParse();
    bracket->neverParse();

    Object_t result;
    EXPECT_FALSE(parser->parse(inp, result));
    EXPECT_EQ(result, nullptr);
}

TEST(expr, parse_neg_unknown) {
    stream inp("-|");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto number = std::make_shared<ExpressionMock>();
    auto var = std::make_shared<ExpressionMock>();
    auto bracket = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, number, var, bracket, errorHandler);

    mockHandler.EXPECT_ERROR(errorHandler, "Unexpected character '|'");
    number->neverParse();
    var->neverParse();
    bracket->neverParse();

    Object_t result;
    EXPECT_FALSE(parser->parse(inp, result));
    EXPECT_EQ(result, nullptr);

}

TEST(expr, parse_a_unknown) {
    stream inp("@|");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto number = std::make_shared<ExpressionMock>();
    auto var = std::make_shared<ExpressionMock>();
    auto bracket = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, number, var, bracket, errorHandler);

    mockHandler.EXPECT_ERROR(errorHandler, "Unexpected character '|'");
    number->neverParse();
    var->willParseMock();
    var->canParseTrue();
    var->canParseFalse();
    bracket->neverParse();

    Object_t result;
    EXPECT_FALSE(parser->parse(inp, result));
    EXPECT_EQ(result, nullptr);

}

TEST(expr, parse_a_plus_unknown) {
    stream inp("@+|");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto number = std::make_shared<ExpressionMock>();
    auto var = std::make_shared<ExpressionMock>();
    auto bracket = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, number, var, bracket, errorHandler);

    mockHandler.EXPECT_ERROR(errorHandler, "Unexpected character '|'");
    number->neverParse();
    var->willParseMock();
    var->canParseTrue();
    var->canParseFalse();
    bracket->neverParse();

    Object_t result;
    EXPECT_FALSE(parser->parse(inp, result));
    EXPECT_EQ(result, nullptr);

}

TEST(expr, parse_empty) {
    stream inp("");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto number = std::make_shared<ExpressionMock>();
    auto var = std::make_shared<ExpressionMock>();
    auto bracket = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, number, var, bracket, errorHandler);

    mockHandler.EXPECT_ERROR(errorHandler, "Unexpected EOF");
    number->neverParse();
    var->neverParse();
    bracket->neverParse();

    Object_t result;
    EXPECT_FALSE(parser->parse(inp, result));
    EXPECT_EQ(result, nullptr);

}

TEST(expr, parse_a_plus_empty) {
    stream inp("@+");
    ErrorHandlerMock mockHandler;
    auto errorHandler = std::make_shared<CMath::Parser::ErrorHandler>();
    auto number = std::make_shared<ExpressionMock>();
    auto var = std::make_shared<ExpressionMock>();
    auto bracket = std::make_shared<ExpressionMock>();
    auto parser = XExpression::create(nullptr, number, var, bracket, errorHandler);

    mockHandler.EXPECT_ERROR(errorHandler, "Expecting expression after '+' operator");
    number->neverParse();
    var->willParseMock();
    var->canParseTrue();
    bracket->neverParse();

    Object_t result;
    EXPECT_FALSE(parser->parse(inp, result));
    EXPECT_EQ(result, nullptr);

}
