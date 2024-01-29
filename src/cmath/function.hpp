#ifndef CMATH_FUNCTION_HPP
#define CMATH_FUNCTION_HPP

#include <vector>
#include <string>

#include <cmath/operator.hpp>

namespace CMath {

class Function : public Operator
{
public:
	Function(std::string &name, std::vector<Object_t> *args, bool copy = false, bool deep = true);
	~Function();
	void visitChild(Visitor_t mv) override;
	bool childIs(int index, Type type) override;
	bool replace(Object_t old, Object_t _new, Sign sign = Sign::ABSORB) override;
	Object_t copy(bool deep = true) override;
	void setName(std::string &name);
	std::string &getName();
	std::size_t getArgumentCount();
	void setArgument(int index, Object_t arg);
	Object_t getArgument(int index);

private:
	std::string _name;
	std::vector<Object_t> _args;
};

} // namespace C

#endif /* CMATH_FUNCTION_HPP */
