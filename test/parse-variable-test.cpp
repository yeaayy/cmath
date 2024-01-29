
#include <gtest/gtest.h>

#include "cmath/object.hpp"
#include "cmath/variable.hpp"
#include "cmath/parser/variable.hpp"

using CMath::Parser::XVariable;

TEST(variable, cant_parse) {
    auto str = "9876543210_ ";
    Parser::stream inp(str);
    XVariable parser;

    for(std::size_t i = 0; str[i]; i++) {
        EXPECT_FALSE(parser.canParse(inp));
        inp.start(i);
    }
}

TEST(variable, can_parse) {
    auto str = "abcABC\\";
    Parser::stream inp(str);
    XVariable parser;

    for(std::size_t i = 0; str[i]; i++) {
        EXPECT_TRUE(parser.canParse(inp)) << "cursor at " << i << ", parse: '" << (char) inp.peek() << "'";
        inp.start(i);
    }
}

TEST(variable, parse_special) {
    std::string str1 = "\\c_m_d";
    std::string str2 = "\\two";
    auto str = str1 + str2;
    Parser::stream inp(str.c_str());
    XVariable parser;

    CMath::Object_t result;
    parser.beginParse(inp, result);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(result->is(CMath::Type::VARIABLE));

    auto var = std::static_pointer_cast<CMath::Variable>(result);
    EXPECT_EQ(str1, var->getName());
}
