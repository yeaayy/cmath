#ifndef MOCK_COMPARATOR_CC
#define MOCK_COMPARATOR_CC

#include "cmath/comparator.hpp"
#include "./object.cc"

class ComparatorMock : public CMath::Comparator
{
    intptr_t eval(CMath::Object_t a, CMath::Object_t b)
    {
        if(a->is(b->getType())) {
            if(auto mock = std::dynamic_pointer_cast<ObjectMock>(a)) {
                return mock == b ? 0 : 1;
            }
            return 1;
        }
        return CMath::Comparator::eval(a, b);
    }
};

#endif /* MOCK_COMPARATOR_CC */
