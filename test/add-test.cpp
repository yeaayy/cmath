
#include <gtest/gtest.h>

#include "cmath/addition.hpp"
#include "cmath/bracket.hpp"
#include "cmath/multiplication.hpp"
#include "cmath/number.hpp"
#include "cmath/util/add-term.hpp"
#include "cmath/util/tree-print.hpp" // TODO: Remove after debugging

#include "mock/comparator.cc"
#include "util/test-sign.cc"

using namespace CMath;

TEST(add, a_plus_a) {
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto addition = std::make_shared<Addition>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        ComparatorMock cmp;
        addition->clearChild();
        addition->add(a1, a2);
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        if(sign[0] == sign[1]) {
            ASSERT_EQ(container->getValue()->getType(), Type::MULTIPLICATION);
            auto result = std::dynamic_pointer_cast<Multiplication>(container->getValue());
            ASSERT_EQ(result->getChildCount(), 2);
            EXPECT_TRUE(a1 == result->get(1));

            ASSERT_TRUE(result->childIs(0, Type::NUMBER));
            auto num = std::static_pointer_cast<Number>(result->get(0));
            EXPECT_EQ(num->getValueSigned(), 2);
            EXPECT_SIGN(result, sign[0]);
        } else {
            ASSERT_TRUE(container->getValue()->is(Type::NUMBER));
            EXPECT_EQ(std::static_pointer_cast<Number>(container->getValue())->getValueSigned(), 0);
        }
    };
    test_sign_full({a1, a2}, func);
}

TEST(add, a_plus_b_plus_b) {
    auto a = std::make_shared<ObjectMock>();
    auto b1 = std::make_shared<ObjectMock>();
    auto b2 = b1->copy();
    auto addition = std::make_shared<Addition>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        ComparatorMock cmp;
        addition->clearChild();
        addition->add(a, b1, b2);
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        if(sign[0] == sign[1]) {
            ASSERT_EQ(container->getValue()->getType(), Type::ADDITION);
            auto resultAdd = std::dynamic_pointer_cast<Addition>(container->getValue());
            EXPECT_TRUE(a == resultAdd->get(0));

            ASSERT_TRUE(resultAdd->childIs(1, Type::MULTIPLICATION));
            auto resultMult = std::dynamic_pointer_cast<Multiplication>(resultAdd->get(1));
            ASSERT_EQ(resultMult->getChildCount(), 2);
            EXPECT_TRUE(b1 == resultMult->get(1));

            ASSERT_TRUE(resultMult->childIs(0, Type::NUMBER));
            auto num = std::static_pointer_cast<Number>(resultMult->get(0));
            EXPECT_EQ(num->getValueSigned(), 2);
            EXPECT_SIGN(resultMult, sign[0]);
        } else {
            EXPECT_TRUE(a == container->getValue());
        }
    };
    test_sign_full({b1, b2}, func);
}

TEST(add, a_b_plus_a_b) {
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto b1 = std::make_shared<ObjectMock>();
    auto b2 = b1->copy();
    auto addition = std::make_shared<Addition>();
    auto m1 = std::make_shared<Multiplication>();
    auto m2 = std::make_shared<Multiplication>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        ComparatorMock cmp;
        addition->clearChild();
        m1->clearChild();
        m2->clearChild();
        m1->add(a1, b1);
        m2->add(a2, b2);
        addition->add(m1, m2);
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        if(sign[0] == sign[1]) {
            ASSERT_EQ(container->getValue()->getType(), Type::MULTIPLICATION);
            auto result = std::dynamic_pointer_cast<Multiplication>(container->getValue());
            ASSERT_EQ(result->getChildCount(), 3);
            EXPECT_TRUE(a1 == result->get(1));
            EXPECT_TRUE(b1 == result->get(2));

            ASSERT_TRUE(result->childIs(0, Type::NUMBER));
            auto num = std::static_pointer_cast<Number>(result->get(0));
            EXPECT_EQ(num->getValueSigned(), 2);
            EXPECT_SIGN(result, sign[0]);
        } else {
            ASSERT_TRUE(container->getValue()->is(Type::NUMBER));
            EXPECT_EQ(std::static_pointer_cast<Number>(container->getValue())->getValueSigned(), 0);
        }
    };
    test_sign_full({m1, m2}, func);
}

TEST(add, n_a_b_plus_a_b) {
    auto n = std::make_shared<Number>(0);
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto b1 = std::make_shared<ObjectMock>();
    auto b2 = b1->copy();
    auto addition = std::make_shared<Addition>();
    auto m1 = std::make_shared<Multiplication>();
    auto m2 = std::make_shared<Multiplication>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        constexpr int NUMBER = 5;
        ComparatorMock cmp;
        addition->clearChild();
        m1->clearChild();
        m2->clearChild();
        n->setValueSigned(NUMBER);
        m1->add(n, a1, b1);
        m2->add(a2, b2);
        addition->add(m1, m2);
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        ASSERT_EQ(container->getValue()->getType(), Type::MULTIPLICATION);
        auto result = std::dynamic_pointer_cast<Multiplication>(container->getValue());
        ASSERT_EQ(result->getChildCount(), 3);
        EXPECT_TRUE(a1 == result->get(1));
        EXPECT_TRUE(b1 == result->get(2));

        ASSERT_TRUE(result->childIs(0, Type::NUMBER));
        auto num = std::static_pointer_cast<Number>(result->get(0));
        int expected = NUMBER * sign[0] + sign[1];
        EXPECT_EQ(num->getValueSigned(), std::abs(expected));
        EXPECT_SIGN(result, expected);
    };
    test_sign_full({m1, m2}, func);
}

TEST(add, n_a_plus_a) {
    auto n = std::make_shared<Number>(0);
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto addition = std::make_shared<Addition>();
    auto m = std::make_shared<Multiplication>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        constexpr int NUMBER = 5;
        ComparatorMock cmp;
        addition->clearChild();
        m->clearChild();
        n->setValueSigned(NUMBER);
        m->add(n, a1);
        addition->add(m, a2);
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        ASSERT_EQ(container->getValue()->getType(), Type::MULTIPLICATION);
        auto result = std::dynamic_pointer_cast<Multiplication>(container->getValue());
        ASSERT_EQ(result->getChildCount(), 2);
        EXPECT_TRUE(a1 == result->get(1));

        ASSERT_TRUE(result->childIs(0, Type::NUMBER));
        auto num = std::static_pointer_cast<Number>(result->get(0));
        int expected = NUMBER * sign[0] + sign[1];
        EXPECT_EQ(num->getValueSigned(), std::abs(expected));
        EXPECT_SIGN(result, expected);
    };
    test_sign_full({m, a2}, func);
}

TEST(add, n_a_plus_m_a) {
    auto n1 = std::make_shared<Number>(0);
    auto n2 = std::make_shared<Number>(0);
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto addition = std::make_shared<Addition>();
    auto m1 = std::make_shared<Multiplication>();
    auto m2 = std::make_shared<Multiplication>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        constexpr int N1 = 5, N2 = 2;
        ComparatorMock cmp;
        addition->clearChild();
        m1->clearChild();
        m2->clearChild();
        n1->setValueSigned(N1);
        n2->setValueSigned(N2);
        m1->add(n1, a1);
        m2->add(n2, a2);
        addition->add(m1, m2);
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        ASSERT_EQ(container->getValue()->getType(), Type::MULTIPLICATION);
        auto result = std::dynamic_pointer_cast<Multiplication>(container->getValue());
        ASSERT_EQ(result->getChildCount(), 2);
        EXPECT_TRUE(a1 == result->get(1));

        ASSERT_TRUE(result->childIs(0, Type::NUMBER));
        auto num = std::static_pointer_cast<Number>(result->get(0));
        int expected = N1 * sign[0] + N2 * sign[1];
        EXPECT_EQ(num->getValueSigned(), std::abs(expected));
        EXPECT_SIGN(result, expected);
    };
    test_sign_full({m1, m2}, func);
}

TEST(add, two_a_min_a) {
    auto n = std::make_shared<Number>(0);
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto addition = std::make_shared<Addition>();
    auto m = std::make_shared<Multiplication>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        ComparatorMock cmp;
        addition->clearChild();
        m->clearChild();
        n->setValueSigned(2);
        m->add(n, a1);
        addition->add(m, a2);
        a2->setIsNegative(!m->isNegative());
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        ASSERT_TRUE(a1 == container->getValue());
    };
    test_sign_full({m}, func);
}

TEST(add, two_a_min_two_a) {
    auto n1 = std::make_shared<Number>(0);
    auto n2 = std::make_shared<Number>(0);
    auto a1 = std::make_shared<ObjectMock>();
    auto a2 = a1->copy();
    auto addition = std::make_shared<Addition>();
    auto m1 = std::make_shared<Multiplication>();
    auto m2 = std::make_shared<Multiplication>();
    auto container = std::make_shared<Bracket>();

    auto func = [=](std::vector<int> sign) {
        ComparatorMock cmp;
        addition->clearChild();
        m1->clearChild();
        m2->clearChild();
        n1->setValueSigned(2);
        n2->setValueSigned(2);
        m1->add(n1, a1);
        m2->add(n2, a2);
        addition->add(m1, m2);
        m2->setIsNegative(!m1->isNegative());
        container->setValue(addition);
        AddTerm add(&cmp);
        add.visit(addition);

        ASSERT_EQ(container->getValue()->getType(), Type::NUMBER);
        ASSERT_EQ(std::static_pointer_cast<Number>(container->getValue())->getValueSigned(), 0);
    };
    test_sign_full({m1}, func);
}
