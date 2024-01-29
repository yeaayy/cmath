
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cmath/object.hpp"

class ObjectMock : public CMath::Object
{
public:
	ObjectMock(): Object((CMath::Type) -1, false)
	{}

	CMath::Object_t copy(bool deep = true) {
		ADD_FAILURE() << "Mock object doesn't support copying";
		return nullptr;
	}
};

typedef std::shared_ptr<ObjectMock> ObjectMock_t;
