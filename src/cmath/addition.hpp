#ifndef CMATH_ADDITION_HPP
#define CMATH_ADDITION_HPP

#include <cmath/commutate_op.hpp>

namespace CMath {

class Addition : public CommutateOp
{
public:
	Addition();
	Object_t copy(bool deep = true) override;
};

} // namespace CMath

#endif /* CMATH_ADDITION_HPP */
