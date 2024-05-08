#ifndef CMATH_UTIL_ADD_TERM_HPP
#define CMATH_UTIL_ADD_TERM_HPP

#include "cmath/comparator.hpp"
#include "cmath/object.hpp"
#include "cmath/visitor.hpp"

namespace CMath {

class AddTerm : public Visitor
{
public:
    AddTerm(Comparator *cmp = nullptr);
	intptr_t onVisit(Addition_t a) override;
	bool add(Multiplication_t a, Object_t b);
	bool add(Number_t a, Number_t b);
	bool add(Multiplication_t a, Multiplication_t b);
	bool add(Object_t a, Object_t b);

private:
	void checkNumber(Multiplication_t m, bool *paired, int *index);

    Comparator *cmp;
};

} // namespace CMath

#endif /* CMATH_UTIL_ADD_TERM_HPP */
