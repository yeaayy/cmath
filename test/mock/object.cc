#ifndef MOCK_OBJECT_CC
#define MOCK_OBJECT_CC

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cmath/object.hpp"

class ObjectMock;
typedef std::shared_ptr<ObjectMock> ObjectMock_t;

class ObjectMock : public CMath::Object
{
public:
	ObjectMock(): Object((CMath::Type) -1, false)
	{
		static int counter = 0;
		this->uid = counter++;
	}

	CMath::Object_t copy(bool deep = true) {
		std::shared_ptr<ObjectMock> result;
		result.reset(new ObjectMock(this->uid));
		return result;
	}
	friend bool operator==(ObjectMock_t a, CMath::Object_t b);

private:
	ObjectMock(int uid): Object((CMath::Type) -1, false)
	{
		this->uid = uid;
	}
	int uid;
};

bool operator==(ObjectMock_t a, CMath::Object_t b)
{
	if(auto o = std::dynamic_pointer_cast<ObjectMock>(b)) {
		return a->uid == o->uid;
	}
	return false;
}

#endif /* MOCK_OBJECT_CC */
