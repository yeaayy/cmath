
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "./object.cc"

#include "cmath/object.hpp"
#include "cmath/parser/expr.hpp"

class ExpressionMock : public CMath::Parser::PExpression
{
	testing::internal::TypedExpectation<bool (::Parser::stream &, CMath::Object_t &)> *__exec = nullptr;
	testing::internal::TypedExpectation<bool (::Parser::stream &)> *__canParse = nullptr;

public:
    MOCK_METHOD(bool, exec, (::Parser::stream &stream, CMath::Object_t &result), (override));
    MOCK_METHOD(bool, canParse, (::Parser::stream &stream), (override));

	auto _canParse() {
		if(__canParse == nullptr) {
			__canParse = &EXPECT_CALL(*this, canParse(_));
		}
		return __canParse;
	}

	auto _exec() {
		if(__exec == nullptr) {
			__exec = &EXPECT_CALL(*this, exec(_, _));
		}
		return __exec;
	}

	ObjectMock_t willParseMock() {
		auto value = std::make_shared<ObjectMock>();
		_exec()->WillOnce(DoAll(
			WithArgs<0, 1>(Invoke([value] (::Parser::stream &stream, CMath::Object_t &result) {
				EXPECT_EQ(stream.get(), '@') << "Expecting mock object here";
				result = std::static_pointer_cast<CMath::Object>(value);
			})),
			Return(true)
		));
		return value;
	}

	void canParseTrue() {
		_canParse()->WillOnce(Return(true));
	}

	void canParseFalse() {
		_canParse()->WillOnce(Return(false));
	}

	void neverParse() {
		_exec()->WillRepeatedly(Return(false));
		_canParse()->WillRepeatedly(Return(false));
	}
};
