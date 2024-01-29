
#include <gtest/gtest.h>

#include "cmath/parser/whitespace.hpp"

using CMath::Parser::XWhitespace;

TEST(whitespace, can_parse_space) {
    Parser::stream inp(" ");
    XWhitespace parser;

    ASSERT_TRUE(parser.canParse(inp));
}

TEST(whitespace, can_parse_tab) {
    Parser::stream inp("\t");
    XWhitespace parser;

    ASSERT_TRUE(parser.canParse(inp));
}

TEST(whitespace, can_parse_new_line) {
    Parser::stream inp("\n");
    XWhitespace parser;

    ASSERT_TRUE(parser.canParse(inp));
}

TEST(whitespace, can_parse_comment) {
    Parser::stream inp("# comment");
    XWhitespace parser;

    ASSERT_TRUE(parser.canParse(inp));
}

TEST(whitespace, cant_parse_letter) {
    Parser::stream inp("x");
    XWhitespace parser;

    ASSERT_FALSE(parser.canParse(inp));
}

TEST(whitespace, cant_parse_empty) {
    Parser::stream inp("");
    XWhitespace parser;

    EXPECT_FALSE(parser.canParse(inp));
}

TEST(whitespace, parse) {
    Parser::stream inp(" \t\n# comment\nx");
    XWhitespace parser;

    parser.parse(inp);
    ASSERT_EQ(inp.peek(), 'x');
}

TEST(whitespace, not_parse) {
    Parser::stream inp("x");
    XWhitespace parser;

    parser.parse(inp);
    ASSERT_EQ(inp.peek(), 'x');
}
