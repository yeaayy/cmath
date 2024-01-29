
#include <gtest/gtest.h>

#include "cmath/parser/number.hpp"
#include "cmath/number.hpp"

using CMath::Parser::XNumber;

TEST(number, can_parse_number) {
    Parser::stream inp("9876543210");
    XNumber parser;

    for(int i = 0; i < 10; i++) {
        ASSERT_TRUE(parser.canParse(inp));
        inp.start(i);
    }
}

TEST(number, cant_parse_other) {
    Parser::stream inp(" ");
    XNumber parser;

    for(int i = 0; !inp.eof(); i++) {
        ASSERT_FALSE(parser.canParse(inp));
        inp.seek(i);
    }
}

TEST(number, parse_number) {
    int value = 1987654320;
    char *strValue = nullptr;
    asprintf(&strValue, "%d", value);

    Parser::stream inp(strValue);
    XNumber parser;

    CMath::Object_t result;
    parser.beginParse(inp, result);

    ASSERT_EQ(inp.peek(), -1);

    ASSERT_EQ(result->getType(), CMath::Type::NUMBER);
    auto num = std::static_pointer_cast<CMath::Number>(result);

    ASSERT_EQ(num->getValueSigned(), value);
    free(strValue);
}

TEST(number, not_parse) {
    Parser::stream inp(" ");
    XNumber parser;

    CMath::Object_t result;
    parser.beginParse(inp, result);

    ASSERT_EQ(result, nullptr);
}
