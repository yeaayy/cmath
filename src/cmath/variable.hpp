#ifndef CMATH_VARIABLE_HPP
#define CMATH_VARIABLE_HPP

#include <string>

#include "cmath/object.hpp"

namespace CMath {

class Variable : public Object
{
public:
	Variable(std::string name, bool isNegative = false);
	~Variable() override;

	Object_t copy(bool deep = false) override;
	void setName(const char *name);
	std::string &getName();

private:
	std::string _name;
};

} // namespace CMath

#endif /* CMATH_VARIABLE_HPP */
