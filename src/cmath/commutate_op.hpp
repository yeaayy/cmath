#ifndef CMATH_COMMUTATE_OP_HPP
#define CMATH_COMMUTATE_OP_HPP

#include <vector>
#include <cmath/operator.hpp>

namespace CMath {

class Comparator;

class CommutateOp : public Operator
{
public:
	CommutateOp(Type type, bool absorbSign);

	void visitChild(Visitor_t mv) override;
	bool childIs(int index, Type type) override;
	bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB) override;
	std::size_t getChildCount();
	bool remove(int index);
	bool remove(Object *o);
	Object_t &get(int index);
	void add(Object_t o);
	int indexOf(Object_t &obj);
	void insert(int index, Object_t &o);

	template<typename... Args>
	void add(Object_t o, Args... args)
	{ add(o); add(args...); }

protected:
	const bool absorbSign;
	std::vector<Object_t > childrens;
};

} // namespace C

#endif /* CMATH_COMMUTATE_OP_HPP */
