#ifndef CMATH_OBJECT_HPP
#define CMATH_OBJECT_HPP

#include <memory>

namespace CMath {

class Object;
class Operator;
class Visitor;
class Number;
class Variable;
class Addition;
class Multiplication;
class Fraction;
class Power;
class Bracket;
class Function;
class Derrivative;
class Relation;

typedef std::shared_ptr<Object> Object_t;
typedef std::shared_ptr<Operator> Operator_t;
typedef std::shared_ptr<Number> Number_t;
typedef std::shared_ptr<Variable> Variable_t;
typedef std::shared_ptr<Addition> Addition_t;
typedef std::shared_ptr<Multiplication> Multiplication_t;
typedef std::shared_ptr<Fraction> Fraction_t;
typedef std::shared_ptr<Power> Power_t;
typedef std::shared_ptr<Bracket> Bracket_t;
typedef std::shared_ptr<Function> Function_t;
typedef std::shared_ptr<Derrivative> Derrivative_t;
typedef std::shared_ptr<Relation> Relation_t;
typedef Visitor *Visitor_t;

enum class Type {
	ADDITION,
	MULTIPLICATION,
	FRACTION,
	POWER,
	BRACKET,
	RELATION,
	NUMBER,
	VARIABLE,
	FUNCTION,
	DERRIVATIVE,
};

enum class Sign {
	TAKE,
	ABSORB,
	COPY,
	SWAP,
};

class Object
{
public:
	Object(Type type, bool isNegative);
	virtual ~Object();

	Type getType();
	bool is(Type type);

	int getId();
	void setIsNegative(bool isNegative);
	bool isNegative();
	void toggleIsNegative(bool toggle = true);
	// Take sign from src and make src positive
	void takeSignFrom(Object_t src);
	// Toggle this object sign and make src positive
	void aborbSignFrom(Object_t src);
	// Copy sign from src, keeping src sign
	void copySignFrom(Object_t src);
	// Swap the sign with o
	void swapSignWith(Object_t o);

	Operator* getParent();
	void setParent(Operator *parent);
	virtual Object_t copy(bool deep = true) = 0;

	static int getObjectCount();

protected:
	const Type _type;
	bool _isNegative;
	int _id;
	Operator* _parent;
};

std::ostream &operator<<(std::ostream &os, Type type);

} // namespace CMath

#endif /* CMATH_OBJECT_HPP */
