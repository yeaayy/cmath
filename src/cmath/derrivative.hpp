#ifndef CMATH_DERRIVATIVE_HPP
#define CMATH_DERRIVATIVE_HPP

#include "cmath/operator.hpp"

namespace CMath {

class Derrivative : public Operator
{
public:
    Derrivative(Object_t a, Object_t b, int order = 1);
	Object_t copy(bool deep = true) override;
	void visitChild(Visitor_t mv) override;
	bool childIs(int index, Type type) override;
	bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB) override;

    Object_t getA();
    Object_t getB();
    void setA(Object_t a);
    void setB(Object_t b);
    int getOrder();
    void setOrder(int order);
private:
    Object_t a;
    Object_t b;
    int order;
};

} // namespace C

#endif /* CMATH_DERRIVATIVE_HPP */
