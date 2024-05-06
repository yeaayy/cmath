
#include <gtest/gtest.h>

#include "cmath/addition.hpp"
#include "cmath/bracket.hpp"
#include "cmath/multiplication.hpp"
#include "cmath/object.hpp"
#include "cmath/util/expand-bracket.hpp"

#include "mock/object.cc"
#include "util/test-sign.cc"

using namespace CMath;

TEST(expand_bracket, no_bracket) {
    auto m = std::make_shared<Multiplication>();
    auto a1 = std::make_shared<Addition>();
    auto a = std::make_shared<ObjectMock>();
    auto b = std::make_shared<ObjectMock>();
    auto c = std::make_shared<ObjectMock>();
    auto func = [=](std::vector<int> sign) {
        ExpandBracket ex;
        auto container = std::make_shared<Bracket>();
        m->clearChild();
        a1->clearChild();

        a1->add(b, c);
        m->add(a, a1);
        container->setValue(m);
        ex.expand(m, 1);
        auto val = std::dynamic_pointer_cast<Addition>(container->getValue());
        auto c1 = std::dynamic_pointer_cast<Multiplication>(val->get(0));
        auto c2 = std::dynamic_pointer_cast<Multiplication>(val->get(1));
        EXPECT_SIGN(val, 1);
        EXPECT_SIGN(c1, sign[0] * sign[1] * sign[2] * sign[3]);
        EXPECT_SIGN(c2, sign[0] * sign[1] * sign[2] * sign[4]);
        EXPECT_TRUE(a == c1->get(0));
        EXPECT_TRUE(b == c1->get(1));
        EXPECT_TRUE(a == c2->get(0));
        EXPECT_TRUE(c == c2->get(1));
        EXPECT_SIGN(c1->get(0), 1);
        EXPECT_SIGN(c1->get(1), 1);
        EXPECT_SIGN(c2->get(0), 1);
        EXPECT_SIGN(c2->get(1), 1);
    };
    test_sign_full({m, a, a1, b, c}, func);
}

TEST(expand_bracket, normal) {
    auto m = std::make_shared<Multiplication>();
    auto br = std::make_shared<Bracket>();
    auto a1 = std::make_shared<Addition>();
    auto a = std::make_shared<ObjectMock>();
    auto b = std::make_shared<ObjectMock>();
    auto c = std::make_shared<ObjectMock>();
    auto func = [=](std::vector<int> sign) {
        ExpandBracket ex;
        auto container = std::make_shared<Bracket>();
        m->clearChild();
        a1->clearChild();

        a1->add(b, c);
        br->setValue(a1);
        m->add(a, br);
        container->setValue(m);
        ex.visit(m);
        auto val = std::dynamic_pointer_cast<Addition>(container->getValue());
        auto c1 = std::dynamic_pointer_cast<Multiplication>(val->get(0));
        auto c2 = std::dynamic_pointer_cast<Multiplication>(val->get(1));
        EXPECT_SIGN(val, 1);
        EXPECT_SIGN(c1, sign[0] * sign[1] * sign[2] * sign[3] * sign[4]);
        EXPECT_SIGN(c2, sign[0] * sign[1] * sign[2] * sign[3] * sign[5]);
        EXPECT_TRUE(a == c1->get(0));
        EXPECT_TRUE(b == c1->get(1));
        EXPECT_TRUE(a == c2->get(0));
        EXPECT_TRUE(c == c2->get(1));
        EXPECT_SIGN(c1->get(0), 1);
        EXPECT_SIGN(c1->get(1), 1);
        EXPECT_SIGN(c2->get(0), 1);
        EXPECT_SIGN(c2->get(1), 1);
    };
    test_sign_full({m, a, a1, br, b, c}, func);
}

TEST(expand_bracket, double_no_bracket) {
    auto m = std::make_shared<Multiplication>();
    auto a1 = std::make_shared<Addition>();
    auto a2 = std::make_shared<Addition>();
    auto a = std::make_shared<ObjectMock>();
    auto b = std::make_shared<ObjectMock>();
    auto c = std::make_shared<ObjectMock>();
    auto d = std::make_shared<ObjectMock>();
    auto container = std::make_shared<Bracket>();
    ExpandBracket ex;

    a1->add(a, b);
    a2->add(c, d);
    m->add(a1, a2);
    container->setValue(m);
    ex.visit(m);
    auto val = std::dynamic_pointer_cast<Addition>(container->getValue());
    ASSERT_EQ(val->getChildCount(), 4);
    auto c1 = std::dynamic_pointer_cast<Multiplication>(val->get(0));
    auto c2 = std::dynamic_pointer_cast<Multiplication>(val->get(1));
    auto c3 = std::dynamic_pointer_cast<Multiplication>(val->get(2));
    auto c4 = std::dynamic_pointer_cast<Multiplication>(val->get(3));
    EXPECT_TRUE(a == c1->get(0));
    EXPECT_TRUE(a == c2->get(0));
    EXPECT_TRUE(b == c3->get(0));
    EXPECT_TRUE(b == c4->get(0));
    EXPECT_TRUE(c == c1->get(1));
    EXPECT_TRUE(d == c2->get(1));
    EXPECT_TRUE(c == c3->get(1));
    EXPECT_TRUE(d == c4->get(1));
}
