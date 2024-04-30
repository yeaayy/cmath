
#include <gtest/gtest.h>
#include <cstdarg>

#include "cmath/all"
#include "cmath/parser/variable.hpp"

#include "mock/error_handler.cc"
#include "mock/parser_expr.cc"

using namespace CMath;
using ::Parser::stream;
using ::CMath::Parser::XVariable;

// class MockSample {
// public:
//     MOCK_METHOD(int, something, (int &result));
// };

TEST(basic, expr_mock) {
    stream inp("x");
    auto varMock = std::make_shared<ExpressionMock>();
    auto varReal = std::make_shared<XVariable>();

    Object_t a = nullptr;
    Object_t result = nullptr;

    varMock->willUse(varReal, a);
    ASSERT_TRUE(varMock->beginParse(inp, result));

    ASSERT_NE(a, nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(a->is(Type::VARIABLE));
    ASSERT_TRUE(result->is(Type::VARIABLE));
    ASSERT_EQ(
        std::dynamic_pointer_cast<Variable>(a)->getName(),
        std::dynamic_pointer_cast<Variable>(result)->getName()
    );
}
