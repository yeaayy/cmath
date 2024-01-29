#ifndef CMATH_RELATION_HPP
#define CMATH_RELATION_HPP

#include "cmath/operator.hpp"

namespace CMath {

class Relation : public Operator
{
public:
	enum class Type {
		EQUAL,
		NOT_EQUAL,
		LESS_THAN,
		GREATER_THAN,
		LESS_THAN_OR_EQUAL,
		GREATER_THAN_OR_EQUAL,
	};

	Relation(Object_t a, Object_t b, Type type);
	void visitChild(Visitor_t mv) override;
	bool childIs(int index, CMath::Type type) override;
	Object_t copy(bool deep = true) override;
	Object_t getA();
	Object_t getB();
	void setA(Object_t a);
	void setB(Object_t b);
	Type getRelationType();
	void setRelationType(Type type);

private:
	Object_t _a;
	Object_t _b;
	Type _type;
};

} // namespace C

#endif /* CMATH_RELATION_HPP */
