#ifndef CMATH_MULTIPLICATION_HPP
#define CMATH_MULTIPLICATION_HPP

#include "cmath/commutate_op.hpp"

namespace CMath {

class Multiplication : public CommutateOp
{
public:
	Multiplication();
	Object_t copy(bool deep = true) override;
};

} // namespace C

#endif /* CMATH_MULTIPLICATION_HPP */
