
#include <gtest/gtest.h>
#include <cstdarg>

#include "cmath/all"
#include "cmath/parser/variable.hpp"

#include "mock/error_handler.cc"
#include "mock/parser_expr.cc"

#include "util/test-sign.cc"

using namespace CMath;
using ::Parser::stream;
using ::CMath::Parser::XVariable;

TEST(basic, copy_mock) {
    auto a = std::make_shared<ObjectMock>();
    auto b = std::make_shared<ObjectMock>();
    auto c = a->copy();
    auto d = a->copy();
    auto e = b->copy();
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(std::dynamic_pointer_cast<ObjectMock>(c) == d);
    EXPECT_TRUE(b == e);
    EXPECT_FALSE(std::dynamic_pointer_cast<ObjectMock>(d) == e);
}

TEST(basic, copy_mult) {
    auto a = std::make_shared<ObjectMock>();
    auto b = std::make_shared<ObjectMock>();
    auto c = std::make_shared<Multiplication>();
    c->add(a, b);
    auto copy = c->copy();
    ASSERT_TRUE(copy->is(Type::MULTIPLICATION));
    auto multCopy = std::dynamic_pointer_cast<Multiplication>(copy);
    EXPECT_TRUE(a == multCopy->get(0));
    EXPECT_TRUE(b == multCopy->get(1));
}

TEST(basic, copy_num) {
    auto a = std::make_shared<Number>(10, true);
    auto b = std::dynamic_pointer_cast<Number>(a->copy());
    EXPECT_EQ(a->getValueSigned(), b->getValueSigned());
}

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

TEST(basic, replace_addition_add_sign) {
    ObjectMock_t a = std::make_shared<ObjectMock>(),
        b = std::make_shared<ObjectMock>();
    auto add = std::make_shared<Addition>();
    Object_t inp[3] = {add, a, b};
    auto func = [=]() -> void {
        add->add(a, b);
        add->clearChild();
    };
    test_sign(3, inp, {1, 1, 1}, {1, 1, 1}, func);
    test_sign(3, inp, {-1, 1, 1}, {-1, 1, 1}, func);
    test_sign(3, inp, {1, -1, 1}, {1, -1, 1}, func);
    test_sign(3, inp, {1, -1, -1}, {1, -1, -1}, func);
}

TEST(basic, replace_multp_add_sign) {
    ObjectMock_t
        a = std::make_shared<ObjectMock>(),
        b = std::make_shared<ObjectMock>();
    auto mul = std::make_shared<Multiplication>();
    Object_t inp[3] = {mul, a, b};
    auto func = [=]() -> void {
        mul->add(a, b);
        mul->clearChild();
    };
    test_sign(3, inp, {1, 1, 1}, {1, 1, 1}, func);
    test_sign(3, inp, {1, -1, 1}, {-1, 1, 1}, func);
    test_sign(3, inp, {1, 1, -1}, {-1, 1, 1}, func);
    test_sign(3, inp, {1, -1, -1}, {1, 1, 1}, func);
    test_sign(3, inp, {-1, 1, 1}, {-1, 1, 1}, func);
    test_sign(3, inp, {-1, -1, 1}, {1, 1, 1}, func);
    test_sign(3, inp, {-1, 1, -1}, {1, 1, 1}, func);
    test_sign(3, inp, {-1, -1, -1}, {-1, 1, 1}, func);
}

TEST(basic, replace_addition_sign) {
    ObjectMock_t
        a = std::make_shared<ObjectMock>(),
        b = std::make_shared<ObjectMock>(),
        c = std::make_shared<ObjectMock>(),
        d = std::make_shared<ObjectMock>();
    auto add = std::make_shared<Addition>();
    Object_t inp[5] = {a, b, add, c, d};
    auto func = [=]() -> void {
        auto add2 = std::make_shared<Addition>();
        add->add(c, d);
        add2->add(a, b);
        add2->replace(b, add);
        add->clearChild();
    };
    test_sign(5, inp, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, func);
    test_sign(5, inp, {1, 1, -1, 1, 1}, {1, 1, 1, -1, -1}, func);
    test_sign(5, inp, {1, -1, 1, 1, 1}, {1, 1, 1, -1, -1}, func);
    test_sign(5, inp, {1, -1, -1, 1, 1}, {1, 1, 1, 1, 1}, func);
    test_sign(5, inp, {1, 1, 1, -1, 1}, {1, 1, 1, -1, 1}, func);
    test_sign(5, inp, {1, 1, -1, -1, 1}, {1, 1, 1, 1, -1}, func);
}

TEST(basic, test_sign_full) {
    auto a = std::make_shared<ObjectMock>();
    for(int i = 0; i < 10; i++) {
        int count = 0;
        auto func = [&](std::vector<int> sign) {
            count++;
        };
        std::vector<CMath::Object_t> inp;
        for(int j = 0; j <= i; j++) {
            inp.push_back(a->copy());
        }
        test_sign_full(inp, func);
        EXPECT_EQ(count, 1 << (i + 1));
    }
}
